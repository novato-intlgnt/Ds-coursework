#include <unordered_map>
#include <string>
#include <vector>

class UnionFind {
private:
    std::unordered_map<std::string, int> mapping;  // Mapeo de nombres a índices
    std::vector<int> parent;  // Representa los padres de cada conjunto
    std::vector<int> rank;    // Rango para optimizar la unión

public:
    // Constructor para inicializar la estructura UnionFind con un número de elementos
    UnionFind() {}

    // Método para agregar un nuevo elemento al conjunto
    void addElement(const std::string& u) {
        if (mapping.find(u) == mapping.end()) {  // Si el elemento no está en el mapa
            int idx = mapping.size();  // Obtener un nuevo índice
            mapping[u] = idx;  // Mapear el nombre a ese índice
            parent.push_back(idx);  // Inicializar su padre como sí mismo
            rank.push_back(0);  // Inicializar el rango a 0
        }
    }

    // Método para encontrar el representante (raíz) de un conjunto
    int find(const std::string& u) {
        int idx = mapping[u];  // Obtenemos el índice del conjunto
        if (parent[idx] != idx) {
            parent[idx] = find(parent[idx]);  // Compresión de caminos
        }
        return parent[idx];
    }

    // Método para unir dos conjuntos
    bool unionSets(const std::string& u, const std::string& v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) return false;  // Si ya están en el mismo conjunto

        // Unión por rango
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};
