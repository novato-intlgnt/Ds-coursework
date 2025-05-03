#pragma once
#include "node.hpp"
#include <string>
#include <vector>

class LinkedList {
private:
  Node *_root;

public:
  inline LinkedList() { _root = nullptr; };
  ~LinkedList();
  LinkedList(const LinkedList &);
  LinkedList &operator=(const LinkedList &);

  void addFirstNode(std::string value, int wight = 0);
  void addNode(std::string value, int weight = 0);

  void deleteFirstNode();
  void deleteNode(std::string value);

  void showList();

  std::vector<std::pair<std::string, int>> getNodes() const;

  Node *getRoot() const { return _root; };
};
