#pragma once
#include "dijkstra.hpp" // Asegúrate de incluir la clase Dijkstra
#include "graph.hpp"
#include "graphMatrix.hpp"
#include "graphVisualizer.hpp"
#include <iostream>
#include <string>
#include <vector>

class GraphApp {
private:
  Graph *_currentGraph;

public:
  GraphApp() : _currentGraph(nullptr){};

  // Método que ejecuta el menú interactivo
  void run() {
    GraphMatrix graphFile;
    bool modified = false;
    std::string fileDotName;
    std::string fileOutName;
    int optUser;

    std::cout << "--- MENU ---\n";
    std::cout << "1. Leer matriz desde el archivo\n";
    std::cout << "2. Imprimir la matriz\n";
    std::cout << "3. Modificar la matriz\n";
    std::cout << "4. Guardar la matriz\n";
    std::cout << "5. Generar grafo de la matriz\n";
    std::cout << "6. Generar grafo propio\n";
    std::cout << "7. Generar grafo por defecto\n";
    std::cout << "8. Generar y visualizar grafo\n";
    std::cout << "9. Encontrar camino más corto con Dijkstra\n"; // Nueva opción
    std::cout << "0. Salir\n";

    do {
      std::cout << "--- \\_._/ ---\n";
      std::cout << "Indicar la operación que desea realizar: ";
      std::cin >> optUser;

      switch (optUser) {
      case 1: {
        int optMatrixType;
        std::string matrixType;
        std::string fileName;
        std::cout << "La matriz es de tipo: \n";
        std::cout << "  1. Incidencia\n";
        std::cout << "  2. Adyacencia\n";
        std::cout << "Escoja una opcion: ";
        std::cin >> optMatrixType;
        while (optMatrixType < 1 && optMatrixType > 2) {
          std::cout << "Opción incorrecta, vuelva a escojer: ";
          std::cin >> optMatrixType;
        }
        matrixType = optMatrixType == 1 ? "incidency" : "adjacency";
        std::cout << "Ingrese el nombre del archivo: ";
        std::cin >> fileName;

        graphFile.setMatrixType(matrixType);
        graphFile.readMatrixFromFile(fileName);
        modified = true;
        break;
      }
      case 2:
        graphFile.printMatrix();
        break;
      case 3:
        graphFile.modifyMatrix();
        modified = true;
        break;
      case 4:
        graphFile.saveMatrixToFile("./../catch_incidence.txt", modified);
        modified = false;
        break;
      case 5: {
        std::string resUser;
        bool isDirected;

        std::cout << "El grafo sera directo(responder con SI o NO): ";
        std::cin >> resUser;

        isDirected = resUser == "si" ? true : false;
        delete _currentGraph;
        _currentGraph = new Graph(graphFile.getNumNodes(),
                                  graphFile.getLabels(), isDirected);
        _currentGraph->buildMatrix(
            graphFile.getMatrix(), graphFile.getNumNodes(),
            graphFile.getNumEdges(), graphFile.getMatrixType());
        _currentGraph->showGraph();
        break;
      }
      case 6: {
        delete _currentGraph;
        int numNodes;
        std::string resUser;
        std::vector<std::string> labels;
        bool isDirected;

        std::cout << "El grafo sera directo(responder con SI o NO): ";
        std::cin >> resUser;
        std::cout << "Indica el número de nodos del grafo: ";
        std::cin >> numNodes;

        labels.resize(numNodes);
        for (int i = 0; i < numNodes; i++) {
          std::string nodeLabel;
          labels.push_back(nodeLabel);
        }

        isDirected = resUser == "si" ? true : false;
        _currentGraph = new Graph(numNodes, labels, isDirected);

        int numEdges;
        std::cout << "Indica el número de aristas a añadir: ";
        std::cin >> numEdges;

        for (int i = 0; i < numEdges; ++i) {
          int u, v, weightEdge;
          std::cout << "Indica los nodos de la arista (u v) y su peso: ";
          std::cin >> u >> v >> weightEdge;
          _currentGraph->addEdge(u, v, weightEdge);
        }

        _currentGraph->showGraph();
        break;
      }
      case 7: {
        std::string resUser;
        bool isDirected;

        std::cout << "El grafo sera directo(responder con SI o NO): ";
        std::cin >> resUser;

        isDirected = resUser == "si" ? true : false;

        delete _currentGraph;
        _currentGraph = new Graph(5, {"A", "B", "C", "D", "E"}, isDirected);
        _currentGraph->addEdge(0, 1, 12);
        _currentGraph->addEdge(0, 4, 8);
        _currentGraph->addEdge(1, 2, 2);
        _currentGraph->addEdge(1, 3, 10);
        _currentGraph->addEdge(1, 4, 4);
        _currentGraph->addEdge(2, 3, 5);
        _currentGraph->addEdge(3, 4, 3);
        _currentGraph->showGraph();
        break;
      }
      case 8: {
        if (_currentGraph == nullptr) {
          std::cout
              << "No se ha generado un grafo. Elige una opción para crear uno."
              << std::endl;
          break;
        }
        std::cout
            << "Indica el nombre del archivo dot y del archivo de salida: ";
        std::cin >> fileDotName >> fileOutName;

        GraphVisualizer visualizer(*_currentGraph);
        visualizer.generateFileGraph(fileDotName);
        visualizer.compileAndShowGraph(fileDotName, fileOutName);
        break;
      }
      case 9: {
        if (_currentGraph == nullptr) {
          std::cout
              << "No se ha generado un grafo. Elige una opción para crear uno."
              << std::endl;
          break;
        }

        int startNode;
        std::cout << "Indica el nodo inicial para Dijkstra: ";
        std::cin >> startNode;

        Dijkstra dijkstra(*_currentGraph);
        dijkstra.shortestPath();
        break;
      }
      case 0:
        std::cout << "Saliendo del programa..." << std::endl;
        break;
      default:
        std::cout << "Opción no válida. Inténtalo de nuevo." << std::endl;
        break;
      }
    } while (optUser != 0);
  }
};
