#include "gato.hpp"
#include <iostream>
#include <string>

Gato::Gato(std::string raza, int edad) : Animal(raza, edad){};
void Gato::maullar() { std::cout << "Miau miau \n"; };
