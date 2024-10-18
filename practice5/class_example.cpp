#include <iostream>

class Rectangle {
public:
  Rectangle();
  Rectangle(Rectangle &&) = default;
  Rectangle(const Rectangle &) = default;
  Rectangle &operator=(Rectangle &&) = default;
  Rectangle &operator=(const Rectangle &) = default;
  ~Rectangle();

private:
  float width, height;
};

Rectangle::Rectangle() {}

Rectangle::~Rectangle() {}
