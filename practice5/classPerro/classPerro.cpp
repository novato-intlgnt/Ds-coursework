#include "include/perro.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Perro miPerro("Labrador", 23);

  std::cout << "Mi perro es de raza " << miPerro.getRaza() << " y tiene "
            << miPerro.getEdad() << " años. \n";
  miPerro.setEdad(14);
  miPerro.setRaza("Pastor Aleman");
  std::cout << "Mi perro es de raza " << miPerro.getRaza() << " y tiene "
            << miPerro.getEdad() << " años. \n";
  std::cout << "Mi perro " << miPerro.getRaza() << " es "
            << miPerro.getEspecie() << "\n";

  std::cout << "1. Todos los perros son de la especie " << Perro::especie
            << "\n";
  std::cout << "2. Todos los perros son de la especie " << Perro::getEspecie();
  return 0;
}
