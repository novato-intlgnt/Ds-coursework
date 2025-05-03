#pragma once
#include "graph.hpp"
#include <string>

class GraphVisualizer {
private:
  Graph &_graph;

public:
  GraphVisualizer(Graph &makeGraph);
  void generateFileGraph(const std::string &fileDotName);

  void compileAndShowGraph(const std::string &fileDotName,
                           const std::string &fileOutName);
};
