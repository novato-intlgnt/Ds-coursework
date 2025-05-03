#include <string>
struct Edge {
  std::string src;
  std::string dest;
  int weight;
  bool operator<(const Edge &other) const {
    return weight < other.weight; // Para ordenar por peso
  }
};
