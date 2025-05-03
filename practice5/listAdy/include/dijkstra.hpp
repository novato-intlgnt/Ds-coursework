#include "graph.hpp"
#include <string>
#include <vector>

class Dijkstra {
private:
  Graph &_graph;

public:
  Dijkstra(Graph &graph) : _graph(graph) {}

  void shortestPath();

  int minDistance(const std::vector<int> &dist,
                  const std::vector<bool> &visited);

  int getNodeIndex(const std::string &nodeName);

  void printSolution(int startNode, int endNode, const std::vector<int> &dist,
                     const std::vector<int> &previous);
};
