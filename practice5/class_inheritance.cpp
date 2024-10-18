#include "perro.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Perro miPerro("Labrador", 23);

  std::cout << "Mi perro es de raza " << miPerro.getRaza();
  return 0;
}
