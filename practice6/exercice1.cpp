#include <fstream>
#include <iostream>
// Definition of a Node in the Binary Tree
struct Node {
  int data;    // Data stored in the node
  Node *left;  // Pointer to the left child
  Node *right; // Pointer to the right child

  // Constructor to initialize the node with a value
  Node(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};

// Insert a value in the Binary Tree
Node *insert(Node *root, int val) {
  if (root == nullptr) { // Base case: if the tree is empty, create a new node
    return new Node(val);
  }

  if (val < root->data) { // If the value is less, insert into the left subtree
    root->left = insert(root->left, val);
  } else { // If the value is greater or equal, insert into the right subtree
    root->right = insert(root->right, val);
  }

  return root; // Return the updated root node
}

// Search for a value in the Binary Tree
bool search(Node *root, int val) {
  if (root == nullptr) {
    return false; // If we reach an empty node, the value is not in the tree
  }

  if (root->data == val) {
    return true; // If we find the value, return true
  }

  if (val < root->data) { // If the value is less, search in the left subtree
    return search(root->left, val);
  } else { // If the value is greater, search in the right subtree
    return search(root->right, val);
  }
}

// Find the minimum value in the Binary Tree (used for deletion)
Node *findMin(Node *root) {
  while (root->left != nullptr) {
    root = root->left;
  }
  return root;
}

// Delete a node in the Binary Tree
Node *deleteNode(Node *root, int val) {
  if (root == nullptr) {
    return root; // If the tree is empty
  }

  if (val < root->data) {
    root->left = deleteNode(root->left, val); // Search in the left subtree
  } else if (val > root->data) {
    root->right = deleteNode(root->right, val); // Search in the right subtree
  } else {
    // Case 1: The node is a leaf or has one child
    if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    }

    // Case 3: The node has two children
    Node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }

  return root;
}

// In-order traversal of the Binary Tree
void inOrder(Node *root) {
  if (root != nullptr) {
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
  }
}

// Pre-order traversal of the Binary Tree
void preOrder(Node *root) {
  if (root != nullptr) {
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

// Post-order traversal of the Binary Tree
void postOrder(Node *root) {
  if (root != nullptr) {
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << " ";
  }
}

void generateDot(Node *root, std::ofstream &file) {
  if (root == nullptr) {
    return;
  }

  // Escribir el nodo actual
  if (root->left != nullptr) {
    file << "    " << root->data << " -> " << root->left->data << ";\n";
    generateDot(root->left, file);
  }
  if (root->right != nullptr) {
    file << "    " << root->data << " -> " << root->right->data << ";\n";
    generateDot(root->right, file);
  }
}

void exportTreeToDot(Node *root, const std::string &filename) {
  std::ofstream file(filename);
  file << "digraph BinaryTree {\n";
  generateDot(root, file);
  file << "}\n";
  file.close();
}

int main() {
  Node *root = nullptr;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  std::cout << "Recorrido inorden: ";
  inOrder(root);
  std::cout << std::endl;

  std::cout << "Recorrido preorden: ";
  preOrder(root);
  std::cout << std::endl;

  std::cout << "Recorrido postorden: ";
  postOrder(root);
  std::cout << std::endl;

  std::cout << "\nBuscando el 40 en el arbol: ";
  if (search(root, 40)) {
    std::cout << "Encontrado" << std::endl;
  } else {
    std::cout << "No encontrado" << std::endl;
  }

  std::cout << "\nEliminando 20\n";
  root = deleteNode(root, 20);
  std::cout << "Recorrido inorden despues de eliminar: ";
  inOrder(root);
  std::cout << std::endl;

  exportTreeToDot(root, "tree.dot");
  return 0;
}
