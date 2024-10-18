#include "animales.hpp"
#include <iostream>

Animal::Animal(std::string raza, int edad) {
  _raza = raza;
  _edad = edad;
}
void Animal::come() { std::cout << "Todos los animales comen. \n"; }
