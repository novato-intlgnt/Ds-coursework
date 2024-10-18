#include <iostream>
using namespace std;

// Clase Nodo que representa cada nodo de la lista enlazada
class Nodo {
public:
  int valor; // Valor que contiene el nodo
  Nodo *sig; // Puntero al siguiente nodo
  Nodo(int v)
      : valor(v), sig(NULL) {} // Constructor que inicializa el valor y el
                               // puntero al siguiente nodo en NULL
};

// Clase Lista que representa una lista enlazada
class Lista {
private:
  Nodo *cabeza; // Puntero al primer nodo de la lista

public:
  Lista();                         // Constructor por defecto
  ~Lista();                        // Destructor
  Lista(const Lista &);            // Constructor de copia
  Lista &operator=(const Lista &); // Operador de asignación
  void insertarPrimero(int);       // Inserta un nodo al principio de la lista
  void imprimir();                 // Imprime los elementos de la lista
  void borrarPrimero();            // Borra el primer nodo de la lista
  void elimina(int v);             // Elimina un nodo con un valor específico
};

// Implementación del constructor por defecto
Lista::Lista() {
  cabeza = NULL; // Inicializa la cabeza de la lista como NULL
}

// Implementación del destructor para liberar memoria
Lista::~Lista() {
  Nodo *temp = cabeza;
  Nodo *borrar;
  // Recorre toda la lista y borra cada nodo
  while (temp != NULL) {
    borrar = temp;
    temp = temp->sig;
    delete borrar; // Libera la memoria del nodo
  }
}

// Implementación del constructor de copia
Lista::Lista(const Lista &otra) : cabeza(NULL) {
  Nodo *tempOtra =
      otra.cabeza;   // Puntero temporal para recorrer la lista original
  Nodo *prev = NULL; // Puntero para el nodo previo en la nueva lista

  // Copia todos los nodos de la lista original
  while (tempOtra != NULL) {
    Nodo *nuevo =
        new Nodo(tempOtra->valor); // Crea un nuevo nodo con el mismo valor
    if (prev == NULL) {
      cabeza = nuevo; // Si es el primer nodo, se asigna a la cabeza
    } else {
      prev->sig = nuevo; // Si no, se enlaza el nodo anterior con el nuevo
    }
    prev = nuevo;             // Avanza el puntero previo
    tempOtra = tempOtra->sig; // Avanza en la lista original
  }
}

// Operador de asignación para copiar una lista en otra
Lista &Lista::operator=(const Lista &otra) {
  if (this != &otra) { // Evitar la autoasignación
    // Elimina todos los nodos actuales de la lista
    Nodo *temp = cabeza;
    while (temp != NULL) {
      Nodo *borrar = temp;
      temp = temp->sig;
      delete borrar; // Libera la memoria de cada nodo
    }

    // Copia los nodos de la lista "otra"
    cabeza = NULL;
    Nodo *tempOtra = otra.cabeza;
    Nodo *prev = NULL;
    while (tempOtra != NULL) {
      Nodo *nuevo = new Nodo(tempOtra->valor);
      if (prev == NULL) {
        cabeza = nuevo;
      } else {
        prev->sig = nuevo;
      }
      prev = nuevo;
      tempOtra = tempOtra->sig;
    }
  }
  return *this; // Devuelve la referencia al objeto actual
}

// Inserta un nodo al principio de la lista
void Lista::insertarPrimero(int v) {
  Nodo *nuevo = new Nodo(v); // Crea un nuevo nodo con el valor v
  nuevo->sig = cabeza;       // El nuevo nodo apunta al antiguo primer nodo
  cabeza = nuevo;            // La cabeza de la lista es ahora el nuevo nodo
}

// Elimina el nodo con el valor v
void Lista::elimina(int v) {
  Nodo *actual = cabeza;
  Nodo *anterior = NULL;

  // Recorre la lista hasta encontrar el valor o llegar al final
  while (actual != NULL && actual->valor != v) {
    anterior = actual;
    actual = actual->sig;
  }

  // Si se encontró el valor
  if (actual != NULL) {
    if (anterior == NULL) {
      cabeza = actual->sig; // Si es el primer nodo, mueve la cabeza
    } else {
      anterior->sig = actual->sig; // Si no, desconecta el nodo
    }
    delete actual; // Libera la memoria del nodo eliminado
  }
}

// Imprime todos los elementos de la lista
void Lista::imprimir() {
  Nodo *temp = cabeza;
  // Recorre la lista y muestra el valor de cada nodo
  while (temp != NULL) {
    cout << temp->valor << " - ";
    temp = temp->sig;
  }
  cout << "\n";
}

// Elimina el primer nodo de la lista
void Lista::borrarPrimero() {
  if (cabeza != NULL) {
    int dato = cabeza->valor;
    Nodo *temp = cabeza;
    cabeza = cabeza->sig; // Mueve la cabeza al siguiente nodo
    delete temp;          // Elimina el nodo anterior
    cout << "Nodo borrado: " << dato << endl;
  } else {
    cout << "La lista esta vacia." << endl;
  }
}

// Clase Grafo que representa un grafo no dirigido usando listas enlazadas
class Grafo {
private:
  int v; // Número de vértices en el grafo
  Lista *
      ady; // Arreglo dinámico de listas para almacenar las listas de adyacencia

public:
  Grafo(int v); // Constructor que recibe el número de vértices
  ~Grafo();     // Destructor
  void insertaArista(int v, int w); // Inserta una arista entre dos vértices
  void imprimir(); // Imprime las listas de adyacencia de cada vértice
  void eliminarArista(int v, int w); // Elimina la arista entre dos vértices
  void agregarvertice();             // Agrega un nuevo vértice al grafo
};

// Constructor que inicializa un grafo con v vértices
Grafo::Grafo(int v) {
  this->v = v; // Asigna el número de vértices
  ady =
      new Lista[v]; // Crea un arreglo de listas de adyacencia para cada vértice
}

// Destructor que libera la memoria asignada al arreglo de listas
Grafo::~Grafo() { delete[] ady; }

// Inserta una arista no dirigida entre los vértices v y w
void Grafo::insertaArista(int v, int w) {
  ady[v].insertarPrimero(w); // Inserta w en la lista de adyacencia de v
  ady[w].insertarPrimero(
      v); // Inserta v en la lista de adyacencia de w (arista no dirigida)
}

// Elimina la arista entre los vértices v y w
void Grafo::eliminarArista(int v, int w) {
  ady[v].elimina(w); // Elimina w de la lista de adyacencia de v
  ady[w].elimina(v); // Elimina v de la lista de adyacencia de w
}

// Imprime las listas de adyacencia de cada vértice
void Grafo::imprimir() {
  for (int i = 0; i < v; i++) {
    cout << "Vertice " << i << ": ";
    ady[i].imprimir(); // Imprime la lista de adyacencia del vértice i
  }
}

// Agrega un nuevo vértice al grafo
void Grafo::agregarvertice() {
  Lista *nueva_ady =
      new Lista[v + 1]; // Crea un nuevo arreglo de listas con un vértice extra
  for (int i = 0; i < v; i++) {
    nueva_ady[i] = ady[i]; // Copia las listas de adyacencia actuales
  }
  delete[] ady;    // Elimina el arreglo anterior
  ady = nueva_ady; // Asigna el nuevo arreglo
  v++;             // Incrementa el número de vértices
  cout << "Vertice " << v - 1 << " agregado.\n";
}

// Función principal para probar el grafo
int main() {
  Grafo g(5); // Crea un grafo con 5 vértices

  // Inserta aristas entre los vértices
  g.insertaArista(0, 1);
  g.insertaArista(0, 4);
  g.insertaArista(1, 2);
  g.insertaArista(1, 3);
  g.insertaArista(1, 4);
  g.insertaArista(2, 3);
  g.insertaArista(3, 4);

  g.eliminarArista(2, 3); // Elimina la arista entre 2 y 3
  g.imprimir();           // Imprime las listas de adyacencia

  g.agregarvertice(); // Ag
}
