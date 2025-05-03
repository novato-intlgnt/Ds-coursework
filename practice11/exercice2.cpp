#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  char item;
  int freq;
  Node *next;
  Node *left;
  Node *right;

  Node(char item, int freq)
      : item(item), freq(freq), next(nullptr), left(nullptr), right(nullptr) {}
};

void insertNode(Node *&head, Node *newNode) {
  if (!head || newNode->freq > head->freq) {
    newNode->next = head;
    head = newNode;
    return;
  }

  Node *current = head;
  while (current->next && current->next->freq >= newNode->freq) {
    current = current->next;
  }
  newNode->next = current->next;
  current->next = newNode;
}

Node *buildFrequencyList(const std::string &inputFile) {
  std::ifstream inFile(inputFile);
  if (!inFile) {
    std::cerr << "Error: Could not open the input file: " << inputFile
              << std::endl;
    return nullptr;
  }

  std::unordered_map<char, int> frequencies;
  char c;

  while (inFile.get(c)) {
    if (std::isalpha(c)) {
      frequencies[std::tolower(c)]++;
    }
  }
  inFile.close();

  Node *head = nullptr;

  for (const auto &[item, freq] : frequencies) {
    Node *newNode = new Node(item, freq);
    insertNode(head, newNode);
  }

  return head;
}

int calcularDesplazamiento(Node *frecuenciaCifrado,
                           char letraMasFrecuenteIdioma = 'e') {
  if (!frecuenciaCifrado)
    return 0;
  char letraMasFrecuenteCifrado = frecuenciaCifrado->item;
  return (letraMasFrecuenteCifrado - letraMasFrecuenteIdioma + 26) % 26;
}

std::string cifrarCesar(const std::string &texto, int clave) {
  std::string resultado;

  for (char c : texto) {
    if (std::isalpha(c)) {
      char base = std::islower(c) ? 'a' : 'A';
      char cifrado = static_cast<char>((c - base + clave) % 26 + base);
      resultado += cifrado;
    } else {
      resultado += c;
    }
  }

  return resultado;
}

std::string cifrarCesarMejorado(const std::string &texto,
                                std::vector<int> &claves) {
  std::string resultado;
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(1, 25);

  for (char c : texto) {
    if (std::isalpha(c)) {
      int clave = dist(rng);
      claves.push_back(clave);
      char base = std::islower(c) ? 'a' : 'A';
      char cifrado = static_cast<char>((c - base + clave) % 26 + base);
      resultado += cifrado;
    } else {
      resultado += c;
      claves.push_back(0);
    }
  }

  return resultado;
}

std::string descifrarCesarMejorado(const std::string &texto,
                                   const std::vector<int> &claves) {
  std::string resultado;
  size_t index = 0;

  for (char c : texto) {
    if (std::isalpha(c)) {
      int clave = claves[index];
      char base = std::islower(c) ? 'a' : 'A';
      char descifrado = static_cast<char>((c - base - clave + 26) % 26 + base);
      resultado += descifrado;
    } else {
      resultado += c;
    }
    index++;
  }

  return resultado;
}

std::string descifrarCesar(const std::string &texto, int clave) {
  return cifrarCesar(texto, 26 - (clave % 26));
}

void deleteList(Node *head) {
  while (head) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
}

void printList(Node *head) {
  Node *current = head;
  while (current) {
    std::cout << current->item << ": " << current->freq << " | ";
    current = current->next;
  }
  std::cout << "nullptr\n";
}

std::string openFile(const std::string &path) {
  std::ifstream inFile(path);
  if (!inFile) {
    std::cerr << "Error: Could not open the input file: " << path << std::endl;
    return "";
  }

  std::string content;
  char c;
  while (inFile.get(c)) {
    content += c;
  }
  inFile.close();

  return content;
}

void saveFile(const std::string &path, const std::string &msg) {
  std::ofstream saveFile(path);
  if (!saveFile) {
    std::cerr << "Error: Could not open the output file: " << path << std::endl;
    return;
  }

  saveFile << msg;
}

int main() {
  std::string inputFile = "./../input.txt";
  std::string outputFile = "./../output.txt";

  std::string msg = openFile(inputFile);
  if (msg.empty())
    return 1;

  std::vector<int> key;
  std::string msgCoded = cifrarCesarMejorado(msg, key);
  saveFile("outputBest.txt", msgCoded);

  Node *frequencyList = buildFrequencyList("outputBest.txt");
  if (frequencyList) {
    std::cout << "Frequency List (Descending Order):\n";
    printList(frequencyList);

    Node *current = frequencyList;
    while (current) {
      int desplazamiento = calcularDesplazamiento(current);
      std::string textoDescifrado = descifrarCesar(msgCoded, desplazamiento);

      std::cout << "Texto descifrado con desplazamiento " << desplazamiento
                << ":\n"
                << textoDescifrado << "\n\n";

      current = current->next;
    }
    deleteList(frequencyList);
  }

  return 0;
}
