#include "./include/graph.hpp"

int main(int argc, char *argv[]) {
  Graph myGraph(5);
  myGraph.addEdge(0, 1);
  myGraph.addEdge(0, 4);
  myGraph.addEdge(1, 2);
  myGraph.addEdge(1, 3);
  myGraph.addEdge(1, 4);
  myGraph.addEdge(2, 3);
  myGraph.addEdge(3, 4);

  myGraph.deleteEdge(2, 3); // Elimina la arista entre 2 y 3
  myGraph.showGraph();      // Imprime las listas de adyacencia
  myGraph.addNode();        // Ag
  myGraph.addEdge(5, 4);
  myGraph.addEdge(3, 5);
  myGraph.showGraph();   // Imprime las listas de adyacencia
  myGraph.deleteNode(5); // Ag
  myGraph.showGraph();   // Imprime las listas de adyacencia
  return 0;
}
