#pragma once
#include "node.hpp"

class LinkedList {
private:
  Node *_root;

public:
  inline LinkedList() { _root = nullptr; };
  ~LinkedList();
  LinkedList(const LinkedList &);
  LinkedList &operator=(const LinkedList &);

  void addFisrtNode(int value);
  void addNode(int value);

  void deleteFirstNode();
  void deleteNode(int value);

  void showList();
};
