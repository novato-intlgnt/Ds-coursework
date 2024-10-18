#include <iostream>
#include <string>

class Person {
public:
  std::string name;
  int age;

  void greetPublic() { greet(); }

private:
  void greet() {
    std::cout << "Hello, my name is " << name << " and I am " << age
              << " years old.";
  }
};

int main(int argc, char *argv[]) {
  Person person1;
  std::cout << "Give me your name and how old are you: ";
  std::cin >> person1.name >> person1.age;

  person1.greetPublic();

  return 0;
}
