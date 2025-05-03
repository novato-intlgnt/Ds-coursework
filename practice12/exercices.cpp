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
  std::string outputFile = "./../output.txt";

  Node *frequencyList = buildFrequencyList(outputFile);
  if (frequencyList) {
    printList(frequencyList);
    deleteList(frequencyList);
  }
}
