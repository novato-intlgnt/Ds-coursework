#include <iostream>

struct Node {
  int destination; // Nodo al que apunta la arista
  int weight; // Peso de la arista (opcional, se puede ignorar si el grafo no es
              // ponderado)
  Node *next; // Puntero al siguiente nodo en la lista

  Node(int dest, int w) : destination(dest), weight(w), next(nullptr) {}
};

// Estructura para representar el grafo
struct Graph {
  int vertices;   // Número de vértices en el grafo
  Node **adjList; // Array de punteros a la lista de adyacencia

  // Constructor para inicializar el grafo con el número de vértices
  Graph(int v) {
    vertices = v;
    adjList = new Node *[v]; // Crear un array de punteros de tamaño v
    for (int i = 0; i < v; i++) {
      adjList[i] = nullptr; // Inicializar cada lista como vacía
    }
  }

  // Función para agregar una arista al grafo (no dirigido)
  void addEdge(int src, int dest, int weight = 1) {
    // Agregar una arista desde src a dest
    Node *newNode = new Node(dest, weight);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    // Si el grafo es no dirigido, agregar también la arista inversa
    newNode = new Node(src, weight);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
  }

  // Función para imprimir la lista de adyacencia
  void printGraph() {
    for (int i = 0; i < vertices; i++) {
      Node *temp = adjList[i];
      std::cout << "Nodo " << i << " está conectado con:\n";
      while (temp) {
        std::cout << "  -> Nodo " << temp->destination << " con peso "
                  << temp->weight << std::endl;
        temp = temp->next;
      }
    }
  }

  // Destructor para liberar la memoria
  ~Graph() {
    for (int i = 0; i < vertices; i++) {
      Node *temp = adjList[i];
      while (temp) {
        Node *next = temp->next;
        delete temp;
        temp = next;
      }
    }
    delete[] adjList;
  }
};

int main() {
  // Crear un grafo de 5 vértices
  Graph g(5);

  // Agregar algunas aristas
  g.addEdge(0, 1, 2);
  g.addEdge(0, 4, 1);
  g.addEdge(1, 2, 3);
  g.addEdge(1, 3, 2);
  g.addEdge(1, 4, 4);
  g.addEdge(2, 3, 5);
  g.addEdge(3, 4, 1);

  // Imprimir la lista de adyacencia
  g.printGraph();

  return 0;
}
