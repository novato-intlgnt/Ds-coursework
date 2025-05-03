#include "./../include/list.hpp"
#include <iostream>
#include <ostream>
#include <string>

LinkedList::~LinkedList() {
  Node *temp = _root;
  Node *toDelete;

  while (temp != nullptr) {
    toDelete = temp;
    temp = temp->next;
    delete toDelete;
  }
};

LinkedList::LinkedList(const LinkedList &other) : _root(nullptr) {
  Node *tempOther = other._root;
  Node *prev = nullptr;

  while (tempOther != nullptr) {
    Node *newNode = new Node(tempOther->value, tempOther->weight);

    if (prev == nullptr) {
      _root = newNode;
    } else {
      prev->next = newNode;
    }
    prev = newNode;
    tempOther = tempOther->next;
  }
};

LinkedList &LinkedList::operator=(const LinkedList &other) {
  if (this != &other) {
    Node *temp = _root;

    while (temp != nullptr) {
      Node *toDelete = temp;
      temp = temp->next;
      delete toDelete;
    }

    _root = nullptr;
    Node *tempOther = other._root;
    Node *prev = nullptr;
    while (tempOther != nullptr) {
      Node *newNode = new Node(tempOther->value, tempOther->weight);
      if (prev == nullptr) {
        _root = newNode;
      } else {
        prev->next = newNode;
      }
      prev = newNode;
      tempOther = tempOther->next;
    }
  }
  return *this;
};

void LinkedList::addFirstNode(std::string value, int weight) {
  Node *newRootNode = new Node(value, weight);
  newRootNode->next = _root;
  _root = newRootNode;
}

void LinkedList::addNode(std::string value, int weight) {
  Node *newNode = new Node(value, weight);

  newNode->next = nullptr;

  if (_root == nullptr) {
    _root = newNode;
  } else {
    Node *temp = _root;

    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void LinkedList::deleteFirstNode() {
  if (_root == nullptr) {
    std::cout << "La lista esta vacia." << std::endl;
    return;
  }
  std::string dato = _root->value;
  Node *temp = _root;
  _root = _root->next;
  delete temp;
  std::cout << "Nodo borrado: " << dato << std::endl;
  return;
}

void LinkedList::deleteNode(std::string value) {
  if (_root == nullptr) {
    std::cout << "La lista está vacía" << std::endl;
    return;
  }

  // Caso especial: si el valor a eliminar es el de la cabeza
  if (_root->value == value) {
    Node *temp = _root;
    _root = temp->next;
    delete temp;
    return;
  }

  Node *temp = _root;
  Node *previous = nullptr;

  // Cambiamos la condición para verificar el valor también en el último nodo
  while (temp != nullptr && temp->value != value) {
    previous = temp;
    temp = temp->next;
  }

  // Si temp es nullptr, el valor no se encontró
  if (temp == nullptr) {
    std::cout << "Valor no encontrado en la lista." << std::endl;
    return;
  }

  // Si el nodo a eliminar fue encontrado, lo eliminamos
  previous->next = temp->next;
  delete temp;
}

void LinkedList::showList() {
  Node *temp = _root;

  if (temp == nullptr) {
    std::cout << "La lista está vacía." << std::endl;
    return;
  }

  while (temp != nullptr) {
    std::cout << "(" << temp->value << " - Peso: " << temp->weight << ")"
              << " -> ";
    temp = temp->next;
  }
  std::cout << "NULL" << std::endl;
}

std::vector<std::pair<std::string, int>> LinkedList::getNodes() const {
  std::vector<std::pair<std::string, int>> nodes;
  Node *current = _root;
  while (current != nullptr) {
    nodes.push_back({current->value,
                     current->weight}); // Solo almacenar los valores necesarios
    current = current->next;
  }
  return nodes;
}
