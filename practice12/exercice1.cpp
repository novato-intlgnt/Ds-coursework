#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

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
// Function to read the contents of a file
std::string readFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo de entrada." << std::endl;
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  file.close();
  return content;
}

// Function to write content to a file
void writeToFile(const std::string &filename, const std::string &content) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo de salida." << std::endl;
    return;
  }
  file << content;
  file.close();
}

// Function to encrypt text using Vigenère cipher
std::string vigenereEncrypt(const std::string &text, const std::string &key) {
  std::string encryptedText;
  int keyIndex = 0;
  int keyLength = key.length();

  for (char c : text) {
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      char keyChar = key[keyIndex % keyLength];
      char keyBase = isupper(keyChar) ? 'A' : 'a';
      encryptedText += ((c - base) + (keyChar - keyBase)) % 27 + base;
      keyIndex++;
    } else {
      encryptedText += c; // Keep non-alphabetic characters as they are
    }
  }

  return encryptedText;
}

// Function to decrypt text using Vigenère cipher
std::string vigenereDecrypt(const std::string &text, const std::string &key) {
  std::string decryptedText;
  int keyIndex = 0;
  int keyLength = key.length();

  for (char c : text) {
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      char keyChar = key[keyIndex % keyLength];
      char keyBase = isupper(keyChar) ? 'A' : 'a';
      decryptedText += ((c - base) - (keyChar - keyBase) + 27) % 27 + base;
      keyIndex++;
    } else {
      decryptedText += c; // Keep non-alphabetic characters as they are
    }
  }

  return decryptedText;
}

int main() {
  std::string inputFilename = "./../input.txt";
  std::string outputFilename = "./../output.txt";
  std::string key;
  int option;

  std::cout << "Ingrese la clave de cifrado: ";
  std::cin >> key;

  std::cout << "Seleccione una opcion (1: Cifrar, 2: Descifrar): ";
  std::cin >> option;

  // Read input file

  std::string result;

  if (option == 1) {
    // Encrypt the text
    std::string text = readFromFile(inputFilename);
    if (text.empty()) {
      return 1; // Exit if file could not be read
    }
    result = vigenereEncrypt(text, key);
    std::cout << "El texto ha sido cifrado y guardado en " << outputFilename
              << std::endl;
  } else if (option == 2) {
    // Decrypt the text
    std::string text = readFromFile(outputFilename);
    if (text.empty()) {
      return 1; // Exit if file could not be read
    }
    result = vigenereDecrypt(text, key);
    std::cout << "El texto ha sido descifrado y guardado en " << outputFilename
              << std::endl;
  } else {
    std::cerr << "Opcion no valida." << std::endl;
    return 1;
  }

  // Write result to output file
  writeToFile(outputFilename, result);

  Node *frequencyList = buildFrequencyList(outputFilename);
  if (frequencyList) {
    printList(frequencyList);
    deleteList(frequencyList);
  }
  return 0;
}
