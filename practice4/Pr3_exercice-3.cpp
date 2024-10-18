#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

std::string MSG;

std::pair<int, int> readLength(std::ifstream &file);
std::vector<std::string> getLabels(std::ifstream &file);
int **readMatrix(std::ifstream &file, int nodes, int edges);
void printMatrix(int **matrix, int nodes, int edges);
void freeMatrix(int **matrix, int nodes);
std::pair<int, int> getNodes(int **matrix, int lenNodes, int edge);
std::vector<int> isolatedNodesList(int **matrix, int lenNodes, int lenEdges);
void modifyMatrix(int **matrix, int nodes, int edges);
void saveMatrix(int **matrix, int nodes, int edges, bool &modified);
void generateFileGraph(int **matrix, int rows, int cols,
                       std::vector<std::string> labels,
                       std::vector<int> isolatedNodes, std::string fileDotName);
void compileAndShowGraph(const std::string &dotFilename,
                         const std::string &outputImage);

int main() {
  int optUser;
  int **matrix;
  int rowsNodes, colsEdges;
  bool modified = false;
  std::string fileDotName;
  std::string fileOutName;
  std::vector<std::string> labels;
  std::vector<int> isolatedNodes;
  std::ifstream file("./../incidencia.txt");
  if (!file) {
    std::cerr << "No se pudo abrir el archivo." << std::endl;
    return 1;
  }

  std::cout << "--- MENU ---\n";
  std::cout << "1. Leer matriz desde el archivo\n";
  std::cout << "2. Imprimir la matriz\n";
  std::cout << "3. Modificar la matriz\n";
  std::cout << "4. Guardar la matriz\n";
  std::cout << "5. Generar y visualizar grafo\n";
  std::cout << "0. Salir\n";
  do {

    std::cout << "--- \\_._/ ---\n";
    std::cout << "Indicar la operacion que desea realizar: ";
    std::cin >> optUser;

    switch (optUser) {
    case 1:
      std::tie(rowsNodes, colsEdges) = readLength(file);
      labels = getLabels(file);
      matrix = readMatrix(file, rowsNodes, colsEdges);
      break;
    case 2:
      printMatrix(matrix, rowsNodes, colsEdges);
      isolatedNodes = isolatedNodesList(matrix, rowsNodes, colsEdges);
      break;
    case 3:
      modifyMatrix(matrix, rowsNodes, colsEdges);
      isolatedNodes = isolatedNodesList(matrix, rowsNodes, colsEdges);
      printMatrix(matrix, rowsNodes, colsEdges);
      modified = true;
      break;
    case 4:
      saveMatrix(matrix, rowsNodes, colsEdges, modified);
      std::cout << "Matriz guardada en el archivo." << std::endl;
      break;
    case 5:
      std::cout << "Indica el nombre del archivo dot donde se almacenara y del "
                   "archivo de salida: ";
      std::cin >> fileDotName >> fileOutName;
      generateFileGraph(matrix, rowsNodes, colsEdges, labels, isolatedNodes,
                        fileDotName);
      compileAndShowGraph(fileDotName, fileOutName);
      std::cout << "Graph dot generado." << std::endl;
      break;
    case 0:
      std::cout << "Saliendo del programa..." << std::endl;
      freeMatrix(matrix, rowsNodes);
      break;
    default:
      std::cout << "Opción no válida. Inténtalo de nuevo." << std::endl;
      break;
    };
  } while (optUser != 0);
  file.close();
  return 0;
}

std::pair<int, int> readLength(std::ifstream &file) {
  int rowsNodes, ColsEdges;
  file >> rowsNodes >> ColsEdges;
  file.ignore();
  return {rowsNodes, ColsEdges};
}

int **readMatrix(std::ifstream &file, int nodes, int edges) {
  int **matrix = new int *[nodes];
  for (int i = 0; i < nodes; ++i) {
    matrix[i] = new int[edges];
  }

  for (int i = 0; i < nodes; ++i) {
    for (int j = 0; j < edges; ++j) {
      file >> matrix[i][j];
    }
  }

  return matrix;
}

void printMatrix(int **matrix, int nodes, int edges) {
  for (int i = 0; i < nodes; ++i) {
    for (int j = 0; j < edges; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void freeMatrix(int **matrix, int nodes) {
  for (int i = 0; i < nodes; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

std::vector<int> isolatedNodesList(int **matrix, int lenNodes, int lenEdges) {
  std::vector<int> isolatedNodes;
  for (int i = 0; i < lenNodes; ++i) {
    if (std::find(matrix[i], matrix[i] + lenEdges, 1) !=
        (matrix[i] + lenEdges)) {
      isolatedNodes.push_back(1);
    } else {
      isolatedNodes.push_back(0);
    }
  }
  return isolatedNodes;
}

std::pair<int, int> getNodes(int **matrix, int lenNodes, int edge) {
  int nodeInit = -1;
  int nodeEnd = -1;
  bool foundNode = false;

  for (int i = 0; i < lenNodes; i++) {
    if (matrix[i][edge] == 1) {
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

void modifyMatrix(int **matrix, int lenNodes, int lenEdges) {
  int modEdg;
  int newNodeI, newNodeE;

  std::cout << "Indique la arista que desea cambiar (entre 1 y " << lenEdges
            << "): ";
  std::cin >> modEdg;

  if (modEdg < 0 || modEdg > lenEdges) {
    std::cerr << "Arista no válida." << std::endl;
    return;
  }
  modEdg--;
  auto [nodeInit, nodeEnd] = getNodes(matrix, lenNodes, modEdg);
  std::cout << "La arista " << modEdg + 1 << " es incidente con los nodos "
            << nodeInit << " y " << nodeEnd << "\n";

  do {
    std::cout
        << "Indique a qué nodos desea que incida la arista ahora (entre 1 y "
        << lenNodes << "): ";
    std::cin >> newNodeI >> newNodeE;
  } while ((newNodeI < 1 || newNodeI > lenNodes || newNodeE < 1 ||
            newNodeE > lenNodes) ||
           (newNodeI == nodeInit && newNodeE == nodeEnd));

  for (int i = 0; i < lenNodes; ++i) {
    matrix[i][modEdg] = 0;
  }

  matrix[newNodeI - 1][modEdg] = 1;
  matrix[newNodeE - 1][modEdg] = 1;
}

void saveMatrix(int **matrix, int nodes, int edges, bool &modified) {
  std::ofstream saveFile("./../catch_incidence.txt", std::ios::app);

  if (!saveFile) {
    std::cerr << "Error al abrir el archivo, para guardar \n";
    return;
  }

  if (modified) {
    saveFile << "La matriz fue modificada, guardando en el archivo..." << "\n";
  }
  saveFile << "Matriz de incidencia (nodos: " << nodes << ", " << edges
           << ")\n";
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < edges; j++) {
      saveFile << matrix[i][j] << " ";
    }
    saveFile << "\n";
  };
  saveFile << "\n";
  modified = false;
}

std::vector<std::string> getLabels(std::ifstream &file) {
  std::vector<std::string> labels;
  std::string line;

  // Leer la línea con los labels
  if (getline(file, line)) {
    std::istringstream iss(line);
    std::string label;
    while (iss >> label) {
      labels.push_back(label); // Añadir el label al vector
    }
  }
  return labels;
}

void generateFileGraph(int **matrix, int rows, int cols,
                       std::vector<std::string> labels,
                       std::vector<int> isolatedNodes,
                       std::string fileDotName) {
  std::ofstream dotFile("./../" + fileDotName + ".dot");
  if (!dotFile) {
    std::cerr << "Hubo un problema al abrir el archivo";
  }

  dotFile << "graph G { \n";
  for (int j = 0; j < rows; j++) {
    if (isolatedNodes[j] == 0) {
      dotFile << "  " << labels[j] << ";\n";
    }
  }

  for (int i = 0; i < cols; i++) {
    auto [nodeInit, nodeEnd] = getNodes(matrix, rows, i);
    dotFile << "  " << labels[nodeInit - 1] << " -- " << labels[nodeEnd - 1]
            << " [label=\"" << i + 1 << "\"];" << std::endl;
  }

  dotFile << "}\n";
  std::cout << "Se creo correctamente el archivo";
}

void compileAndShowGraph(const std::string &dotFilename,
                         const std::string &outputImage) {
  // Compilar el archivo DOT a una imagen PNG
  std::string command =
      "cd .. && dot -Tpng " + dotFilename + ".dot -o " + outputImage + ".png";
  int result = system(command.c_str()); // Ejecuta el comando

  if (result == 0) {
    std::cout << "Imagen del grafo generada: " << outputImage << std::endl;

    // Comando para abrir la imagen (en Linux con xdg-open)
    std::string openCommand = "cd .. && xdg-open " + outputImage + ".png";
    system(openCommand.c_str()); // Ejecuta el comando para abrir la imagen
  } else {
    std::cerr << "Error al generar la imagen del grafo." << std::endl;
  }
}
