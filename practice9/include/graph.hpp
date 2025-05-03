#pragma once
#include "edge.hpp"
#include "list.hpp"
#include "unionFind.hpp"
#include <string>
#include <vector>

class Graph : public LinkedList {
private:
  int _numNodes;
  bool _isDirected;
  std::vector<std::string> _labels;
  LinkedList *_listAdy;

public:
  Graph(int numNodes, std::vector<std::string> labels, bool isDirected);
  inline ~Graph() { delete[] _listAdy; }

  void showGraph();

  void addEdge(int v, int w, int weight);
  void deleteEdge(int v, int w, int weight);

  void addNode();
  void deleteNode(int v);

  inline int getNumNodes() { return _numNodes; }
  inline std::vector<std::string> getLabels() { return _labels; }
  inline LinkedList *getListAdy() { return _listAdy; }
  inline bool getIsDirected() { return _isDirected; }

  std::vector<Edge> getEdges() const;
  void buildMatrix(int **matrix, int rows, int cols, std::string matrixType) {
    if (matrixType == "incidency") {
      buildFromIncidenceMatrix(matrix, rows, cols);
    } else {
      buildFromAdyacencyMatrix(matrix, rows, cols);
    }
  }
  void buildFromIncidenceMatrix(int **matrix, int rows, int cols);
  void buildFromAdyacencyMatrix(int **matrix, int rows, int cols);
  void buildRamdonGraph(int maxEdgesPerNode, int maxWeight);

  void kruskalMST();
};
