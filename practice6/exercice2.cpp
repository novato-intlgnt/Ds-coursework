#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Definición de un nodo en el árbol binario
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Insertar un valor en el árbol binario
Node* insert(Node* root, int val) {
    if (root == nullptr) { // Si el árbol está vacío, crea un nuevo nodo
        return new Node(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val); // Insertar en el subárbol izquierdo
    } else {
        root->right = insert(root->right, val); // Insertar en el subárbol derecho
    }

    return root; // Retornar el nodo raíz actualizado
}

// Buscar un valor en el árbol binario
bool search(Node* root, int val) {
    if (root == nullptr) return false; // Si el árbol está vacío, el valor no está presente

    if (root->data == val) return true; // Valor encontrado

    if (val < root->data) {
        return search(root->left, val); // Buscar en el subárbol izquierdo
    } else {
        return search(root->right, val); // Buscar en el subárbol derecho
    }
}

// Encontrar el valor mínimo en el árbol binario
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Eliminar un nodo en el árbol binario
Node* deleteNode(Node* root, int val) {
    if (root == nullptr) return root; // Si el árbol está vacío, no hay nada que eliminar

    if (val < root->data) {
        root->left = deleteNode(root->left, val); // Buscar en el subárbol izquierdo
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val); // Buscar en el subárbol derecho
    } else {
        // Caso 1: El nodo es una hoja o tiene un solo hijo
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Caso 2: El nodo tiene dos hijos
        Node* temp = findMin(root->right); // Buscar el sucesor en inorden
        root->data = temp->data;           // Reemplazar los datos
        root->right = deleteNode(root->right, temp->data); // Eliminar el sucesor
    }

    return root;
}

// Recorrido inorden del árbol binario
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Recorrido preorden del árbol binario
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Recorrido postorden del árbol binario
void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

// Generar el código DOT para visualizar el árbol binario
void generateDot(Node* root, ofstream &file) {
    if (root == nullptr) return;

    // Nodo izquierdo
    if (root->left != nullptr) {
        file << "  " << root->data << " -> " << root->left->data << ";\n";
        generateDot(root->left, file);
    } else {
        // Nodo nulo para el subárbol izquierdo
        static int nullCount = 0;
        file << "  n" << nullCount << "[label=\"\", color=white];\n";
        file << "  " << root->data << " -> n" << nullCount++ << "[color=white];\n";
    }

    // Nodo derecho
    if (root->right != nullptr) {
        file << "  " << root->data << " -> " << root->right->data << ";\n";
        generateDot(root->right, file);
    } else {
        // Nodo nulo para el subárbol derecho
        static int nullCount = 0;
        file << "  n" << nullCount << "[label=\"\", color=white];\n";
        file << "  " << root->data << " -> n" << nullCount++ << "[color=white];\n";
    }
}

// Exportar el árbol a un archivo DOT
void exportTreeToDot(Node* root, const string& filename) {
    ofstream file(filename);
    file << "digraph BinaryTree {\n";
    generateDot(root, file);
    file << "}\n";
    file.close();
}

// Generar un árbol binario aleatorio
Node* generateRandomTree(int numNodes, int minValue, int maxValue) {
    Node* root = nullptr;
    srand(time(0));  // Inicializar la semilla para números aleatorios

    for (int i = 0; i < numNodes; ++i) {
        int val = rand() % (maxValue - minValue + 1) + minValue; // Valor aleatorio entre minValue y maxValue
        root = insert(root, val); // Insertar el valor en el árbol
    }

    return root;
}

int main() {
    // Generación de un árbol binario aleatorio con 10 nodos y valores entre 1 y 100
    Node* root = generateRandomTree(10, 1, 100);

    // Visualización de los recorridos del árbol
    cout << "Recorrido inorden: ";
    inOrder(root);
    cout << endl;

    cout << "Recorrido preorden: ";
    preOrder(root);
    cout << endl;

    cout << "Recorrido postorden: ";
    postOrder(root);
    cout << endl;

    // Exportar el árbol a un archivo DOT
    exportTreeToDot(root, "random_tree.dot");
    cout << "Árbol aleatorio exportado a 'random_tree.dot'. Usa Graphviz para visualizarlo.\n";

    return 0;
}
