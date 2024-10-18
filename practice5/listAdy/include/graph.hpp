#pragma once
#include "list.hpp"

class Graph : public LinkedList {
private:
  int _numNodes;
  LinkedList *_listAdy;

public:
  inline Graph(int numNodes)
      : _numNodes(numNodes), _listAdy(new LinkedList[numNodes]){};
  inline ~Graph() { delete[] _listAdy; }

  void showGraph();

  void addEdge(int v, int w);
  void deleteEdge(int v, int w);

  void addNode();
  void deleteNode(int v);
};
