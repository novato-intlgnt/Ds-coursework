#include <string>

class Animal {
public:
  Animal(std::string raza, int edad);
  // Getter - Setter
  inline int getEdad() { return _edad; };
  inline std::string getRaza() { return _raza; };
  inline void setEdad(int newEdad) { _edad = newEdad; };
  inline void setRaza(std::string newRaza) { _raza = newRaza; };

  static void come();

private:
  std::string _especie;
  std::string _raza;
  int _edad;
  int _patas;
};
