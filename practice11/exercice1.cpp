#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

// Función para cifrar usando el cifrado César
std::string cifrarCesar(const std::string &texto, int clave) {
  std::string resultado;

  for (char c : texto) {
    if (std::isalpha(c)) { // Verifica si es una letra
      char base = std::islower(c)
                      ? 'a'
                      : 'A'; // Define la base según sea minúscula o mayúscula
      char cifrado = static_cast<char>((c - base + clave) % 26 + base);
      resultado += cifrado;
    } else {
      resultado += c; // Si no es una letra, no se modifica
    }
  }

  return resultado;
}

// Función para descifrar usando el cifrado César
std::string descifrarCesar(const std::string &texto, int clave) {
  return cifrarCesar(texto, 26 - (clave % 26)); // Invertimos el desplazamiento
}

// Carga un archivo de palabras válidas en un conjunto para búsqueda rápida
std::unordered_set<std::string>
cargarPalabrasValidas(const std::string &rutaArchivo) {
  std::unordered_set<std::string> palabras;
  std::ifstream archivo(rutaArchivo);

  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo de palabras válidas: "
              << rutaArchivo << std::endl;
    return palabras;
  }

  std::string palabra;
  while (archivo >> palabra) {
    palabras.insert(palabra);
  }

  archivo.close();
  return palabras;
}

// Función para realizar ataque de fuerza bruta con validación por palabras

void fuerzaBrutaCesar(const std::string &textoCifrado,
                      const std::string &rutaPalabrasValidas,
                      const std::string &outputPath) {
  // Cargar palabras válidas
  std::unordered_set<std::string> palabrasValidas =
      cargarPalabrasValidas(rutaPalabrasValidas);
  if (palabrasValidas.empty()) {
    std::cerr << "Error: No se pudieron cargar palabras válidas.\n";
    return;
  }

  // Abrir archivo para guardar resultados
  std::ofstream saveFile(outputPath);
  if (!saveFile.is_open()) {
    std::cerr << "Error al abrir el archivo para guardar resultados de fuerza "
                 "bruta.\n";
    return;
  }

  const int NUM_CLAVES = 26; // Número de posibles claves para el cifrado César
  int mejorClave = -1;       // Clave que genera el mejor descifrado
  int maxPalabrasValidas = 0;
  std::string mejorTextoDescifrado;

  for (int clave = 1; clave < NUM_CLAVES; ++clave) {
    // Intentar descifrar el texto con la clave actual
    std::string posibleTexto = descifrarCesar(textoCifrado, clave);
    std::istringstream stream(posibleTexto);
    std::string palabra;
    int palabrasValidasEncontradas = 0;

    // Contar palabras válidas en el texto descifrado
    while (stream >> palabra) {
      if (palabrasValidas.find(palabra) != palabrasValidas.end()) {
        ++palabrasValidasEncontradas;
      }
    }

    // Actualizar la mejor clave si el texto descifrado tiene más palabras
    // válidas
    if (palabrasValidasEncontradas > maxPalabrasValidas) {
      maxPalabrasValidas = palabrasValidasEncontradas;
      mejorClave = clave;
      mejorTextoDescifrado = posibleTexto;
    }
  }

  // Guardar el mejor resultado encontrado
  if (mejorClave != -1) {
    saveFile << "Clave encontrada: " << mejorClave << "\n";
    saveFile << "Texto descifrado: " << mejorTextoDescifrado << "\n";
  } else {
    saveFile << "No se encontró una clave que descifre el texto con éxito.\n";
  }

  saveFile.close();
}

void saveFile(std::string path, std::string msg) {
  std::ofstream saveFile(path);

  if (!saveFile) {
    std::cerr << "Error al abrir el archivo, para guardar \n";
    return;
  }

  saveFile << msg;
}

std::string openFile(std::string path) {
  std::ifstream inFile(path);
  if (!inFile) {
    std::cerr << "Error: Could not open the input file: " << path << std::endl;
  }

  std::string word;
  char c;
  while (inFile.get(c)) {
    word += c;
  }
  inFile.close();

  return word;
}

int main() {
  std::string inputFile = "./../input.txt";
  std::string outputFile = "./../output.txt";
  std::string bruteForceFile = "./../fuerza_bruta.txt";
  std::string validWordsFile = "./../words.txt";

  std::string word = openFile(inputFile);
  int key;

  std::cout << "Ingrese la clave (desplazamiento): ";
  std::cin >> key;

  // Cifrado
  std::string msg = cifrarCesar(word, key);
  saveFile(outputFile, msg);

  // Descifrado
  std::string msgDecode = descifrarCesar(msg, key);

  // Ataque de fuerza bruta con validación
  fuerzaBrutaCesar(msg, validWordsFile, bruteForceFile);

  return 0;
}
