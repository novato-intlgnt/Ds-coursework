#pragma once
#include <fstream>
#include <string>
#include <vector>

class GraphMatrix {
private:
  std::ifstream _file;
  int _nodes;
  int _edges;
  int **_matrix;
  std::vector<std::string> _labels;
  std::string _matrixType;

public:
  // Constructores y destructores
  GraphMatrix(){};
  ~GraphMatrix();

  // Setters
  void setNumNodesEdges();
  void setLabels();
  void createMatrix();
  void openFile(const std::string &filename);
  inline void setMatrixType(std::string matrixType) {
    _matrixType = matrixType;
  };

  // Getters
  inline int **getMatrix() const { return _matrix; }
  inline int getNumNodes() const { return _nodes; }
  inline int getNumEdges() const { return _edges; }
  inline std::string getMatrixType() const { return _matrixType; }
  inline std::vector<std::string> getLabels() { return _labels; }

  // Lectura de archivo y matrices
  void readMatrixFromFile(const std::string &filename);
  void readIncidenceMatrix();
  void readAdjacencyMatrix();

  // Modificación de la matriz
  void modifyMatrix();
  void modifyIncidenceMatrix();
  void modifyAdjacencyMatrix();
  std::pair<int, int> getNodes(int edge);

  // Utilidades
  void saveMatrixToFile(const std::string &filename, bool modified);
  void printMatrix();
  std::vector<int> isolatedNodesList() const;
};
