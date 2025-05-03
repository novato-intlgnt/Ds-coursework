#include "./../include/graphVisualizer.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

GraphVisualizer::GraphVisualizer(Graph &makeGraph) : _graph(makeGraph){};

void GraphVisualizer::generateFileGraph(const std::string &fileDotName) {
  LinkedList *adjacencyList = _graph.getListAdy();
  std::vector<std::string> labels = _graph.getLabels();
  std::set<std::pair<std::string, std::string>> edgesInserted;
  std::ofstream dotFile(fileDotName + ".dot");

  if (!dotFile) {
    std::cerr << "Error al crear el archivo DOT " << fileDotName << std::endl;
    return;
  }

  // Determina si el grafo es dirigido o no
  bool isDirected = _graph.getIsDirected();

  // Configura el tipo de grafo en el archivo DOT
  dotFile << (isDirected ? "digraph G {\n" : "graph G {\n");

  for (int i = 0; i < _graph.getNumNodes(); i++) {
    Node *currentNode = adjacencyList[i].getRoot();

    // Si el nodo no tiene conexiones, agrégalo como un nodo aislado
    if (currentNode == nullptr) {
      dotFile << "  " << labels[i] << ";\n";
      continue;
    }

    // Recorre la lista de adyacencia de cada nodo
    while (currentNode != nullptr) {
      std::string &neighborLabel = currentNode->value;

      // Solo verifica duplicados si el grafo no es dirigido
      if (edgesInserted.find({labels[i], neighborLabel}) ==
              edgesInserted.end() &&
          edgesInserted.find({neighborLabel, labels[i]}) ==
              edgesInserted.end()) {

        int weightEdge = currentNode->weight;
        dotFile << "  " << labels[i] << (isDirected ? " -> " : " -- ")
                << neighborLabel << "[label=\"" << weightEdge << "\"];\n";

        if (!isDirected) {
          edgesInserted.insert({labels[i], neighborLabel});
        }
      }

      currentNode = currentNode->next;
    }
  }

  dotFile << "}\n";
  dotFile.close();

  std::cout << "Archivo DOT generado: " << fileDotName << std::endl;
}

void GraphVisualizer::compileAndShowGraph(const std::string &fileDotName,
                                          const std::string &fileOutName) {
  std::string command =
      "dot -Tpng " + fileDotName + ".dot" + " -o " + fileOutName;
  int result = system(command.c_str());
  if (result == 0) {
    std::cout << "Grafo generado y guardado en " << fileOutName << std::endl;

#ifdef __linux__ // Para sistemas Linux
    std::string openCommand = "xdg-open " + fileOutName;
    system(openCommand.c_str());
#elif _WIN32    // Para Windows
    std::string openCommand = "start " + fileOutName;
    system(openCommand.c_str());
#elif __APPLE__ // Para macOS
    std::string openCommand = "open " + fileOutName;
    system(openCommand.c_str());
#endif
  } else {
    std::cerr << "Error al generar el grafo." << std::endl;
  }
}
