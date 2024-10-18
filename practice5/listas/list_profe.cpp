#include <iostream>

class Nodo {
private:
  int valor;
  Nodo *sig;

public:
  Nodo(int, Nodo * = NULL);

  friend class Lista;
};

Nodo::Nodo(int v, Nodo *s) {
  valor = v;
  sig = s;
}

class Lista {
private:
  Nodo *_cabeza;

public:
  Lista();
  ~Lista();
  void insertarPrimero(int);
  void imprimir();
  void borrarPrimero();
};
Lista::Lista() { _cabeza = NULL; }

Lista::~Lista() {
  Nodo *temp = _cabeza;
  Nodo *borrar;
  while (temp != NULL) {
    borrar = temp;
    temp = temp->sig;
    delete borrar;
  }
}
void Lista::insertarPrimero(int v) {
  Nodo *nuevo = new Nodo(v);
  if (_cabeza == NULL) {
    nuevo->sig = NULL;
    _cabeza = nuevo;
  } else {
    nuevo->sig = _cabeza;
    _cabeza = nuevo;
  }
}

void Lista::imprimir() {
  Nodo *temp = _cabeza;
  while (temp != NULL) {
    std::cout << temp->valor << " - ";
    temp = temp->sig;
  }
  std::cout << "\n";
}

void Lista::borrarPrimero() {
  if (_cabeza != NULL) {
    int dato = _cabeza->valor;
    Nodo *temp = _cabeza;
    _cabeza = _cabeza->sig;
    delete temp;
    std::cout << "Nodo borrado: " << dato << std::endl;
  } else {
    std::cout << "La lista esta vacia: " << std::endl;
  }
}

int main(int argc, char *argv[]) {

  Lista *listaA;
  listaA = new Lista();

  listaA->insertarPrimero(5);
  listaA->insertarPrimero(8);
  listaA->insertarPrimero(9);
  listaA->imprimir();

  listaA->borrarPrimero();
  listaA->borrarPrimero();
  listaA->borrarPrimero();
  listaA->borrarPrimero();

  delete listaA;
  return 0;

  return 0;
}
