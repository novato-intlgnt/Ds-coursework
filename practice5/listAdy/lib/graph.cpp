#include "./../include/graph.hpp"
#include <iostream>

void Graph::showGraph() {
  for (int i = 0; i < _numNodes; i++) {
    std::cout << "Vertice " << i << ": ", _listAdy[i].showList();
  }
}
void Graph::addEdge(int v, int w) {
  _listAdy[v].addFisrtNode(w);
  _listAdy[w].addFisrtNode(v);
}

void Graph::deleteEdge(int v, int w) {
  _listAdy[v].deleteNode(w);
  _listAdy[w].deleteNode(v);
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
  for (int i = 0; i < _numNodes; i++) {
    if (i != v) {
      _listAdy[i].deleteNode(v);
    }
  }

  LinkedList *newList = new LinkedList[_numNodes - 1];
  for (int i = 0; i < _numNodes; i++) {
    if (i != v) {
      newList[i] = _listAdy[i];
    }
  }

  delete[] _listAdy;
  _listAdy = newList;

  _numNodes--;
};
