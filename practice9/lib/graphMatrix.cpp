#include "./../include/graphMatrix.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

GraphMatrix::~GraphMatrix() {
  for (int i = 0; i < _nodes; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void GraphMatrix::printMatrix() {
  for (int i = 0; i < _nodes; ++i) {
    for (int j = 0; j < _edges; ++j) {
      std::cout << _matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
void GraphMatrix::readMatrixFromFile(const std::string &filename) {
  openFile(filename);
  setNumNodesEdges();
  setLabels();
  createMatrix();

  if (_matrixType == "incidency") {
    readIncidenceMatrix();
  } else if (_matrixType == "adjacency") {
    readAdjacencyMatrix();
  }

  _file.close();
}

void GraphMatrix::createMatrix() {
  _matrix = new int *[_nodes];
  for (int i = 0; i < _nodes; ++i) {
    _matrix[i] = new int[_edges];
  }
}

void GraphMatrix::readIncidenceMatrix() {
  for (int i = 0; i < _nodes; ++i) {
    for (int j = 0; j < _edges; ++j) {
      _file >> _matrix[i][j];
    }
  }
}

void GraphMatrix::readAdjacencyMatrix() {
  for (int i = 0; i < _nodes; ++i) {
    for (int j = 0; j < _nodes; ++j) {
      _file >> _matrix[i][j];
    }
  }
}

void GraphMatrix::openFile(const std::string &filename) {
  if (_file.is_open()) {
    _file.close();
  }
  _file.open("./../" + filename);
  if (!_file) {
    std::cerr << "Error al abrir el archivo: " << filename << std::endl;
  }
}

void GraphMatrix::setNumNodesEdges() {
  _file >> _nodes;

  if (_file.peek() == '\n') {
    _edges = _nodes;
  } else {
    _file >> _edges;
  }
  // _file >> _nodes >> _edges;
  _file.ignore();
}

void GraphMatrix::setLabels() {
  std::string line;
  if (getline(_file, line)) {
    std::istringstream iss(line);
    std::string label;
    while (iss >> label) {
      _labels.push_back(label);
    }
  }
}

std::pair<int, int> GraphMatrix::getNodes(int edge) {
  int nodeInit = -1;
  int nodeEnd = -1;
  bool foundNode = false;

  for (int i = 0; i < _nodes; i++) {
    if (_matrix[i][edge] == 1) {
      if (!foundNode) {
        nodeInit = i + 1;
        nodeEnd = nodeInit;
        foundNode = true;
      } else {
        nodeEnd = i + 1;
        break;
      }
    }
  }
  return {nodeInit, nodeEnd};
}
void GraphMatrix::modifyMatrix() {
  if (_matrixType == "incidency") {
    modifyIncidenceMatrix();
  } else if (_matrixType == "adjacency") {
    modifyAdjacencyMatrix();
  }
}
void GraphMatrix::modifyIncidenceMatrix() {
  int modEdge, newNodeInit, newNodeEnd, newWeight;
  // for (int i = 0; i < _edges; i++) {
  //   std::cout << "Arista " << i << " - Peso: " << _weights[i] << ", ";
  // }
  std::cout << "Indique la arista que desea cambiar (entre 0 y " << _edges - 1
            << ") y su nuevo peso para modificar(o 0 para mantenerlo): ";
  std::cin >> modEdge >> newWeight;

  if (modEdge < 0 || modEdge >= _edges) {
    std::cerr << "Arista no válida." << std::endl;
    return;
  }

  auto [nodeInit, nodeEnd] = getNodes(modEdge);
  std::cout << "La arista " << modEdge << " es incidente con los nodos "
            << _labels[nodeInit] << " y " << _labels[nodeEnd] << "\n";

  std::cout << "Nodos disponibles";
  for (int i = 0; i < _nodes; i++) {
    std::cout << i << ": " << _labels[i] << ", ";
  }

  do {
    std::cout << "Indique los nodos que desea que sean incidentes con la "
                 "arista (entre 0 y "
              << _nodes - 1 << "): ";
    std::cin >> newNodeInit >> newNodeEnd;
  } while ((newNodeInit < 0 || newNodeInit >= _nodes || newNodeEnd < 0 ||
            newNodeEnd >= _nodes) ||
           (newNodeInit == nodeInit && newNodeEnd == nodeEnd));

  // Reiniciar la columna de la arista seleccionada a 0
  for (int i = 0; i < _nodes; ++i) {
    _matrix[i][modEdge] = 0;
  }

  // _weights[modEdge] = newWeight != 0 ? newWeight : _weights[modEdge];

  // Asignar nuevos nodos incidentes
  _matrix[newNodeInit][modEdge] = 1;
  _matrix[newNodeEnd][modEdge] = 1;
}

void GraphMatrix::modifyAdjacencyMatrix() {
  int node1, node2, weight;
  for (int i = 0; i < _nodes; i++) {
    std::cout << i << ": " << _labels[i] << ", ";
  }
  std::cout << "Indique el primer nodo para modificar la conexión (entre 0 y "
            << _nodes - 1 << ") y su peso -> n1 n2 w: ";
  std::cin >> node1 >> node2 >> weight;

  if (node1 < 0 || node1 >= _nodes || node2 < 0 || node2 >= _nodes) {
    std::cerr << "Nodo no válido." << std::endl;
    return;
  }

  if (_matrix[node1][node2] != 0) {
    std::cout << "Actualmente hay una conexión entre " << _labels[node1]
              << " y " << _labels[node2] << " con peso "
              << _matrix[node1][node2] << ".\n";
    std::cout << "Ingrese el nuevo peso para modificar la conexión (o 0 para "
                 "eliminarla): ";
  } else {
    std::cout << "No hay conexión entre " << _labels[node1] << " y "
              << _labels[node2] << ".\n";
    std::cout << "Ingrese el peso para crear la conexión (o 0 para mantenerla "
                 "desconectada): ";
  }
  std::cin >> weight;

  if (weight == 0) {
    _matrix[node1][node2] = 0;
    _matrix[node2][node1] = 0; // Si es grafo no dirigido
    std::cout << "Conexión eliminada entre " << node1 + 1 << " y " << node2 + 1
              << ".\n";
  } else {
    _matrix[node1][node2] = weight;
    _matrix[node2][node1] = weight; // Si es grafo no dirigido
    std::cout << "Conexión añadida/modificada entre " << node1 + 1 << " y "
              << node2 + 1 << " con peso " << weight << ".\n";
  }
}

void GraphMatrix::saveMatrixToFile(const std::string &filename, bool modified) {
  if (!modified) {
    std::cout << "No hay cambios en la matriz para guardar." << std::endl;
    return;
  }

  std::ofstream file("./../" + filename);
  if (!file) {
    std::cerr << "Error al guardar el archivo " << filename << std::endl;
    return;
  }

  // Guardar número de nodos y, si es matriz de incidencia, número de aristas
  file << "La matriz es de tipo: " << _matrixType;
  file << _nodes;
  if (_edges > 0) {
    file << " " << _edges;
  }
  file << std::endl;

  // Guardar etiquetas de nodos
  for (const auto &label : _labels) {
    file << label << " ";
  }
  file << std::endl;

  // Guardar la matriz
  for (int i = 0; i < _nodes; ++i) {
    for (int j = 0; j < (_edges > 0 ? _edges : _nodes); ++j) {
      file << _matrix[i][j] << " ";
    }
    file << std::endl;
  }

  file.close();
  std::cout << "Matriz guardada en " << filename << std::endl;
}
