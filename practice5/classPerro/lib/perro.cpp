#pragma once

#include "./../include/perro.hpp"
#include <string>

std::string Perro::especie = "Mamifero";
Perro::Perro(std::string raza, int edad) {
  _raza = raza;
  _edad = edad;
}
