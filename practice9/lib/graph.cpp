#include "./../include/graph.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

Graph::Graph(int numNodes, std::vector<std::string> labels, bool isDirected)
    : _numNodes(numNodes), _labels(labels), _isDirected(isDirected),
      _listAdy(new LinkedList[numNodes]){};

void Graph::showGraph() {
  for (int i = 0; i < _numNodes; i++) {
    std::cout << "Vertice " << _labels[i] << ": ", _listAdy[i].showList();
  }
}
void Graph::addEdge(int v, int w, int weight) {
  _listAdy[v].addFirstNode(_labels[w], weight);
  if (!_isDirected) {
    _listAdy[w].addFirstNode(_labels[v], weight);
  }
}

void Graph::deleteEdge(int v, int w, int weight) {
  _listAdy[v].deleteNode(_labels[w]);
  if (!_isDirected) {
    _listAdy[w].deleteNode(_labels[v]);
  }
}

void Graph::addNode() {
  LinkedList *newList = new LinkedList[_numNodes + 1];

  for (int i = 0; i < _numNodes; i++) {
    newList[i] = _listAdy[i];
  }

  delete[] _listAdy;
  _listAdy = newList;

  _numNodes++;

  std::cout << "Vertice " << _numNodes - 1 << " agregado.\n";
};

void Graph::deleteNode(int v) {
  for (int i = 1; i < _numNodes; i++) {
    if (i != v) {
      _listAdy[i].deleteNode(_labels[v]);
    }
  }

  LinkedList *newList = new LinkedList[_numNodes - 1];
  for (int i = 1; i < _numNodes; i++) {
    if (i != v) {
      newList[i] = _listAdy[i];
    }
  }

  delete[] _listAdy;
  _listAdy = newList;

  _numNodes--;
};

void Graph::buildFromIncidenceMatrix(int **matrix, int rows, int cols) {
  int nodeInit = -1;
  int nodeEnd = -1;
  int weight = 0;

  for (int j = 0; j < cols; ++j) {
    nodeInit = -1;
    nodeEnd = -1;
    weight = 0;

    for (int i = 0; i < rows; ++i) {
      if (matrix[i][j] > 0) {
        if (nodeInit == -1) {
          nodeInit = i;
          weight = matrix[i][j];
        } else {
          if (i == nodeInit) {
            nodeEnd = i;
            weight = matrix[i][j];
            break;
          }
        }
      } else if (matrix[i][j] < 0) {
        if (nodeEnd == -1) {
          nodeEnd = i;
          weight = -matrix[i][j];
        }
      }
    }

    if (nodeInit == nodeEnd && nodeInit != -1) {
      addEdge(nodeInit, nodeEnd, weight);
    } else if (nodeInit != -1 && nodeEnd != -1) {
      addEdge(nodeInit, nodeEnd, weight);
    }
  }
}

void Graph::buildFromAdyacencyMatrix(int **matrix, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = i; j < cols; ++j) {
      int weight = matrix[i][j];

      if (weight != 0) {
        if (i == j) {
          addEdge(i, j, abs(weight));
        } else {
          if (weight > 0) {
            addEdge(i, j, weight);
          } else if (weight < 0) {
            addEdge(j, i, -weight);
          }
        }
      }
    }
  }
}

void Graph::buildRamdonGraph(int maxEdgesPerNode, int maxWeight) {
  srand(time(0));

  for (int i = 0; i < _numNodes; ++i) {
    std::unordered_set<int> connectedNodes;

    int edges = rand() % (maxEdgesPerNode + 1);

    for (int j = 0; j < edges; ++j) {
      int targetNode;
      do {
        targetNode = rand() % _numNodes;
      } while (targetNode == i ||
               connectedNodes.find(targetNode) != connectedNodes.end());

      int weight = 1 + rand() % maxWeight;

      addEdge(i, targetNode, weight);
      connectedNodes.insert(targetNode);
    }
  }
}

std::vector<Edge> Graph::getEdges() const {
  std::vector<Edge> edges;
  for (int i = 0; i < _numNodes; ++i) {
    for (const auto &node : _listAdy[i].getNodes()) {

      if (_labels[i] == node.first) {
        edges.push_back({_labels[i], node.first, node.second});
      }
    }
  }
  return edges;
}

void Graph::kruskalMST() {
  std::vector<Edge> edges = getEdges();
  std::sort(edges.begin(), edges.end()); // Ordenar las aristas por peso

  UnionFind uf;
  std::vector<Edge> mstEdges; // Para almacenar las aristas del MST

  for (const auto &edge : edges) {
    if (uf.unionSets(edge.src, edge.dest)) { // Agregar arista si no forma ciclo
      mstEdges.push_back(edge);
      std::cout << "Arista añadida: " << edge.src << " - " << edge.dest
                << " con peso " << edge.weight << "\n";
      if (mstEdges.size() == _numNodes - 1)
        break; // MST completo
    }
  }

  // Comprobar si se ha formado un MST válido
  if (mstEdges.size() != _numNodes - 1) {
    std::cout << "El grafo no es conexo, no se puede formar un MST.\n";
  } else {
    std::cout << "El árbol de expansión mínima tiene las siguientes aristas:\n";
    for (const auto &edge : mstEdges) {
      std::cout << edge.src << " - " << edge.dest << " con peso " << edge.weight
                << "\n";
    }
  }
}
