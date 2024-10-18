#include "animales.hpp"

class Gato : public Animal {
public:
  Gato(std::string raza, int edad);
  void maullar();
};
