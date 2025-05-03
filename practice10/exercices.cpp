#include <fstream>
#include <iostream>
#include <memory>
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

// Insert the node
void insertNode(Node *&head, Node *newNode) {
  if (!head || newNode->freq < head->freq) {
    newNode->next = head;
    head = newNode;
    return;
  }

  Node *current = head;
  while (current->next && current->next->freq <= newNode->freq) {
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
    frequencies[c]++;
  }
  inFile.close();

  Node *head = nullptr;

  for (const auto &[item, freq] : frequencies) {
    Node *newNode = new Node(item, freq);
    insertNode(head, newNode);
  }

  return head;
}

// Print the list in console
void printList(Node *head) {
  Node *current = head;
  while (current) {
    std::cout << current->item << " (" << current->freq << ") -> ";
    current = current->next;
  }
  std::cout << "nullptr\n";
}

// Clean the memory
void deleteList(Node *head) {
  while (head) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {
  std::string inputFile = "./../entrada.txt";
  Node *frequencyList = buildFrequencyList(inputFile);

  if (frequencyList) {
    std::cout << "Frequency List (Descending Order):\n";
    printList(frequencyList);
    deleteList(frequencyList);
  }

  return 0;
}
