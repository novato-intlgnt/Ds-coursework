#pragma once
#include <string>

struct Node {
  std::string value;
  int weight;
  Node *next;

  Node(std::string val, int weight)
      : value(val), weight(weight), next(nullptr){};
};
