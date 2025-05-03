#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

const int MIN_VERTICES = 8;
const int MAX_VERTICES = 14;
const int MAX_WEIGHT = 10;
const int INF = numeric_limits<int>::max();

class Graph {
private:
  int numVertices;
  vector<vector<int>> matrix;
  vector<pair<int, pair<int, int>>> edges;
  vector<pair<int, pair<int, int>>> kruskalEdges;
  vector<pair<int, pair<int, int>>> primEdges;

public:
  Graph() {
    numVertices = MIN_VERTICES + (rand() % (MAX_VERTICES - MIN_VERTICES + 1));
    matrix = vector<vector<int>>(numVertices, vector<int>(numVertices, 0));
    generateRandomEdges();
  }

  void generateRandomEdges() {
    int numEdges = numVertices - 1;
    int additionalEdges = rand() % numVertices;
    numEdges += additionalEdges;

    for (int i = 0; i < numVertices - 1; i++) {
      int weight = 1 + (rand() % MAX_WEIGHT);
      matrix[i][i + 1] = weight;
      matrix[i + 1][i] = weight;
      edges.push_back({weight, {i, i + 1}});
    }

    for (int i = 0; i < additionalEdges; i++) {
      int source = rand() % numVertices;
      int destination = rand() % numVertices;

      while (source == destination || matrix[source][destination] != 0) {
        destination = rand() % numVertices;
      }

      int weight = 1 + (rand() % MAX_WEIGHT);
      matrix[source][destination] = weight;
      matrix[destination][source] = weight;
      edges.push_back({weight, {source, destination}});
    }
  }

  void showMatrix() {
    cout << "Matriz de adyacencia (" << numVertices << " vértices):" << endl;
    for (int i = 0; i < numVertices; i++) {
      for (int j = 0; j < numVertices; j++) {
        cout << matrix[i][j] << "\t";
      }
      cout << endl;
    }
  }

  void kruskal() {
    vector<int> parent(numVertices);
    vector<int> rank(numVertices);

    for (int i = 0; i < numVertices; i++) {
      parent[i] = i;
      rank[i] = 0;
    }

    sort(edges.begin(), edges.end());
    int totalCost = 0;

    cout << "\nConstruyendo Árbol de Expansión Mínima usando Kruskal:" << endl;

    for (const auto &edge : edges) {
      int weight = edge.first;
      int u = edge.second.first;
      int v = edge.second.second;

      if (find(parent, u) != find(parent, v)) {
        kruskalEdges.push_back(edge);
        totalCost += weight;
        unionSets(parent, rank, u, v);
        cout << "Agregando arista (" << u << ", " << v << ") con peso "
             << weight << endl;
      }
    }

    cout << "Costo total del Árbol de Expansión Mínima (Kruskal): " << totalCost
         << endl;
  }

  void prim() {
    vector<bool> visited(numVertices, false);
    vector<int> key(numVertices, INF);
    vector<int> parent(numVertices, -1);

    key[0] = 0;
    cout << "\nConstruyendo Árbol de Expansión Mínima usando Prim:" << endl;

    for (int i = 0; i < numVertices - 1; i++) {
      int u = getMinimum(key, visited);
      visited[u] = true;

      for (int v = 0; v < numVertices; v++) {
        if (matrix[u][v] && !visited[v] && matrix[u][v] < key[v]) {
          parent[v] = u;
          key[v] = matrix[u][v];
        }
      }
    }

    int totalCost = 0;
    for (int i = 1; i < numVertices; i++) {
      if (parent[i] != -1) {
        primEdges.push_back({matrix[i][parent[i]], {parent[i], i}});
        totalCost += matrix[i][parent[i]];
        cout << "Agregando arista (" << parent[i] << ", " << i << ") con peso "
             << matrix[i][parent[i]] << endl;
      }
    }

    cout << "Costo total del Árbol de Expansión Mínima (Prim): " << totalCost
         << endl;
  }

  void generateDotNormal(const string &fileName) {
    ofstream file(fileName);
    file << "graph G {\n";
    for (const auto &edge : edges) {
      int u = edge.second.first;
      int v = edge.second.second;
      int weight = edge.first;
      file << " " << u << " -- " << v << " [label=\"" << weight << "\"];\n";
    }
    file << "}\n";
    file.close();
    cout << "Archivo DOT del grafo original generado: " << fileName << endl;
  }

  void generateDotKruskal(const string &fileName) {
    ofstream file(fileName);
    file << "graph G {\n";

    for (const auto &edge : edges) {
      int u = edge.second.first;
      int v = edge.second.second;
      int weight = edge.first;

      bool isMST = false;
      for (const auto &mstEdge : kruskalEdges) {
        if ((mstEdge.second.first == u && mstEdge.second.second == v) ||
            (mstEdge.second.first == v && mstEdge.second.second == u)) {
          isMST = true;
          break;
        }
      }

      if (isMST) {
        file << " " << u << " -- " << v << " [label=\"" << weight
             << "\", color=red, penwidth=2.0];\n";
      } else {
        file << " " << u << " -- " << v << " [label=\"" << weight << "\"];\n";
      }
    }

    file << "}\n";
    file.close();
    cout << "Archivo DOT del Árbol de Expansión Mínima (Kruskal) generado: "
         << fileName << endl;
  }

  void generateDotPrim(const string &fileName) {
    ofstream file(fileName);
    file << "graph G {\n";

    for (const auto &edge : edges) {
      int u = edge.second.first;
      int v = edge.second.second;
      int weight = edge.first;

      bool isMST = false;
      for (const auto &mstEdge : primEdges) {
        if ((mstEdge.second.first == u && mstEdge.second.second == v) ||
            (mstEdge.second.first == v && mstEdge.second.second == u)) {
          isMST = true;
          break;
        }
      }

      if (isMST) {
        file << " " << u << " -- " << v << " [label=\"" << weight
             << "\", color=blue, penwidth=2.0];\n";
      } else {
        file << " " << u << " -- " << v << " [label=\"" << weight << "\"];\n";
      }
    }

    file << "}\n";
    file.close();
    cout << "Archivo DOT del Árbol de Expansión Mínima (Prim) generado: "
         << fileName << endl;
  }
  void generarImagen(const string &dotFileName, const string &imageFileName) {
    string command = "dot -Tpng " + dotFileName + " -o " + imageFileName;
    system(command.c_str());
  }

private:
  int find(vector<int> &parent, int x) {
    if (parent[x] != x) {
      parent[x] = find(parent, parent[x]);
    }
    return parent[x];
  }

  void unionSets(vector<int> &parent, vector<int> &rank, int x, int y) {
    int px = find(parent, x);
    int py = find(parent, y);

    if (rank[px] < rank[py]) {
      parent[px] = py;
    } else if (rank[px] > rank[py]) {
      parent[py] = px;
    } else {
      parent[py] = px;
      rank[px]++;
    }
  }

  int getMinimum(vector<int> &key, vector<bool> &visited) {
    int min = INF, minIndex;
    for (int v = 0; v < numVertices; v++) {
      if (!visited[v] && key[v] < min) {
        min = key[v];
        minIndex = v;
      }
    }
    return minIndex;
  }
};

int main() {
  srand(time(0));

  Graph g;
  cout << "Grafo generado aleatoriamente:" << endl;
  g.showMatrix();

  g.generateDotNormal("grafo_original.dot");
  g.kruskal();
  g.generateDotKruskal("grafo_kruskal.dot");
  g.prim();
  g.generateDotPrim("grafo_prim.dot");

  g.generarImagen("grafo_original.dot", "grafo_original.png");
  g.generarImagen("grafo_kruskal.dot", "grafo_kruskal.png");
  g.generarImagen("grafo_prim.dot", "grafo_prim.png");

  return 0;
}
