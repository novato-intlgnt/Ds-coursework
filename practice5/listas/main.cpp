#include <iostream>

struct Nodo {
  int valor;
  Nodo *siguiente;
};

class ListaEnlazada {
private:
  Nodo *_cabeza;

public:
  ListaEnlazada() {
    _cabeza = nullptr; // Inicialmente la lista está vacía
  }

  // Método para agregar un nodo al final
  void agregarNodo(int valor) {
    Nodo *nuevoNodo = new Nodo(); // Crear un nuevo nodo
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = nullptr; // El nuevo nodo será el último, por lo que
                                    // siguiente es nullptr

    if (_cabeza == nullptr) {
      // Si la lista está vacía, el nuevo nodo será la cabeza
      _cabeza = nuevoNodo;
    } else {
      // Si la lista ya tiene nodos, recorremos hasta el final y agregamos el
      // nuevo nodo
      Nodo *temp = _cabeza;
      while (temp->siguiente != nullptr) {
        temp = temp->siguiente;
      }
      temp->siguiente = nuevoNodo;
    }
  }

  // Método para eliminar un nodo con un valor específico
  void eliminarNodo(int valor) {
    if (_cabeza == nullptr) {
      std::cout << "La lista está vacía." << std::endl;
      return;
    }

    // Si el nodo a eliminar es la cabeza
    if (_cabeza->valor == valor) {
      Nodo *temp = _cabeza;
      _cabeza = _cabeza->siguiente;
      delete temp;
      return;
    }

    Nodo *temp = _cabeza;
    Nodo *previo = nullptr;

    while (temp != nullptr && temp->valor != valor) {
      previo = temp;
      temp = temp->siguiente;
    }

    if (temp == nullptr) {
      std::cout << "Valor no encontrado en la lista." << std::endl;
      return;
    }

    // Eliminar el nodo
    previo->siguiente = temp->siguiente;
    delete temp;
  }

  // Método para mostrar los elementos de la lista
  void mostrarLista() {
    Nodo *temp = _cabeza;
    while (temp != nullptr) {
      std::cout << temp->valor << " -> ";
      temp = temp->siguiente;
    }
    std::cout << "NULL" << std::endl;
  }
};

int main() {
  ListaEnlazada lista;
  lista.agregarNodo(10);
  lista.agregarNodo(20);
  lista.agregarNodo(30);

  std::cout << "Lista actual: ";
  lista.mostrarLista(); // Salida: 10 -> 20 -> 30 -> NULL

  lista.eliminarNodo(20);
  lista.eliminarNodo(50);

  std::cout << "Lista después de eliminar 20: ";
  lista.mostrarLista(); // Salida: 10 -> 30 -> NULL

  return 0;
}

/*
 Listas:
  primero
  ultimo
  cualquiera
  borrar
  añadir
*/
