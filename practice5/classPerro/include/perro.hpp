#pragma once
#include <string>
class Perro {
public:
  Perro(std::string raza, int edad);

  // Getter/Ssetter
  inline int getEdad() { return _edad; };
  inline std::string getRaza() { return _raza; };
  inline void setEdad(int newEdad) { _edad = newEdad; };
  inline void setRaza(std::string newRaza) { _raza = newRaza; };

  // Static
  static int getNumPatas() { return 4; }
  static std::string getEspecie() { return especie; };

  std::string getEspecieNoStatic() { return especie; }

private:
  std::string _raza;
  int _edad;

public:
  static std::string especie;
};
