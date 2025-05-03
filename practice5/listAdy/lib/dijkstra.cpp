#include "./../include/dijkstra.hpp"
#include <iostream>

void Dijkstra::shortestPath() {
  int startNode, endNode;
  std::cout << "Ingrese el nodo de inicio (índice): ";
  std::cin >> startNode;
  std::cout << "Ingrese el nodo de fin (índice): ";
  std::cin >> endNode;

  int numNodes = _graph.getNumNodes();
  std::vector<int> dist(numNodes, 999999);
  std::vector<bool> visited(numNodes, false); // Seguimiento de nodos visitados
  std::vector<int> previous(numNodes, -1);    // Para reconstruir el camino
  dist[startNode] = 0; // La distancia al nodo inicial es 0

  for (int i = 0; i < numNodes; i++) {
    // Obtener el nodo con la distancia mínima que aún no ha sido visitado
    int u = minDistance(dist, visited);
    if (u == -1)
      break; // Si no hay más nodos accesibles, salimos del bucle
    visited[u] = true;

    // Actualizar las distancias de los nodos adyacentes
    LinkedList &adjList = _graph.getListAdy()[u];
    Node *currentNode = adjList.getRoot();
    while (currentNode != nullptr) {
      int v = getNodeIndex(currentNode->value);
      if (!visited[v] && dist[u] != 999999 && dist[u] + 1 < dist[v]) {
        dist[v] = dist[u] +
                  1; // Suponemos que el peso es 1, ajusta según sea necesario
        previous[v] = u; // Guardamos el nodo previo para reconstruir el camino
      }
      currentNode = currentNode->next;
    }
  }

  // Imprimir resultado
  printSolution(startNode, endNode, dist, previous);
}

int Dijkstra::minDistance(const std::vector<int> &dist,
                          const std::vector<bool> &visited) {
  int min = 999999, minIndex = -1;

  for (int v = 0; v < dist.size(); v++) {
    if (!visited[v] && dist[v] <= min) {
      min = dist[v];
      minIndex = v;
    }
  }

  return minIndex;
}

int Dijkstra::getNodeIndex(const std::string &nodeName) {
  const std::vector<std::string> &labels = _graph.getLabels();
  for (int i = 0; i < labels.size(); i++) {
    if (labels[i] == nodeName) {
      return i;
    }
  }
  return -1;
}

void Dijkstra::printSolution(int startNode, int endNode,
                             const std::vector<int> &dist,
                             const std::vector<int> &previous) {
  std::cout << "Distancia mínima desde el nodo " << startNode
            << " hasta el nodo " << endNode << " es: " << dist[endNode] << "\n";

  // Reconstruir el camino desde el nodo final hasta el inicial
  std::vector<int> path;
  for (int at = endNode; at != -1; at = previous[at]) {
    path.push_back(at);
  }

  // Si el nodo final no es alcanzable
  if (path.back() != startNode) {
    std::cout << "No hay camino entre el nodo " << startNode << " y el nodo "
              << endNode << "\n";
  } else {
    // Imprimir el camino
    std::cout << "El camino más corto es: ";
    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i];
      if (i != 0)
        std::cout << " -> ";
    }
    std::cout << std::endl;
  }
}
