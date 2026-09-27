// ============================================================================
//  Practica 1 - Estructura de Datos
//  Algoritmo: ORDENAMIENTO BURBUJA (Bubble Sort)
//
//  Ordena alfabeticamente un dataset largo de palabras leidas desde un
//  archivo de texto. NO usa ninguna funcion de libreria que ordene.
//  Mide el tiempo de ejecucion con la libreria <chrono>.
// ============================================================================

#include <iostream>   // std::cout, std::cerr  -> imprimir por consola
#include <fstream>    // std::ifstream, std::ofstream -> leer/escribir archivos
#include <vector>     // std::vector -> array dinamico para las palabras
#include <string>     // std::string -> tipo de dato para cada palabra
#include <chrono>     // std::chrono -> medicion precisa del tiempo

// ----------------------------------------------------------------------------
//  Carga todas las palabras de un archivo de texto en un vector<string>.
//  Cada palabra separada por espacios o saltos de linea se lee por separado.
// ----------------------------------------------------------------------------
std::vector<std::string> cargarPalabras(const std::string& nombreArchivo) {
    std::vector<std::string> palabras;          // vector vacio que iremos llenando
    std::ifstream archivo(nombreArchivo);       // abre el archivo en modo lectura

    if (!archivo.is_open()) {                    // valida que el archivo si exista
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return palabras;                         // devuelve vector vacio si falla
    }

    std::string palabra;                         // variable temporal por palabra
    while (archivo >> palabra) {                 // lee token a token hasta EOF
        palabras.push_back(palabra);             // agrega la palabra al vector
    }

    archivo.close();                             // cierra el archivo (buena practica)
    return palabras;                             // devuelve el vector ya lleno
}

// ----------------------------------------------------------------------------
//  Guarda el vector de palabras (ya ordenado) en un archivo de salida.
// ----------------------------------------------------------------------------
void guardarPalabras(const std::string& nombreArchivo,
                     const std::vector<std::string>& palabras) {
    std::ofstream salida(nombreArchivo);         // abre/crea archivo de escritura
    for (const std::string& p : palabras) {      // recorre cada palabra del vector
        salida << p << "\n";                     // la escribe seguida de salto de linea
    }
    salida.close();                              // cierra el archivo
}

// ----------------------------------------------------------------------------
//  ALGORITMO BURBUJA
//  Recorre el vector repetidamente comparando pares de elementos adyacentes.
//  Si estan en el orden incorrecto los intercambia, "burbujeando" el mayor
//  hacia el final en cada pasada. Complejidad O(n^2).
// ----------------------------------------------------------------------------
void bubbleSort(std::vector<std::string>& v) {
    int n = v.size();                            // cantidad de elementos a ordenar

    for (int i = 0; i < n - 1; i++) {            // controla cuantas pasadas se hacen
        bool huboIntercambio = false;            // bandera de optimizacion

        // En cada pasada el mayor ya quedo al final, por eso restamos i.
        for (int j = 0; j < n - 1 - i; j++) {    // recorre los pares adyacentes
            if (v[j] > v[j + 1]) {               // compara alfabeticamente (operador >)
                std::string temp = v[j];         // guarda temporalmente el elemento
                v[j] = v[j + 1];                 // mueve el menor a la izquierda
                v[j + 1] = temp;                 // coloca el mayor a la derecha
                huboIntercambio = true;          // marca que si hubo cambio
            }
        }

        // Si en una pasada completa no hubo intercambios, ya esta ordenado.
        if (!huboIntercambio) break;             // sale antes -> optimizacion
    }
}

// ----------------------------------------------------------------------------
//  FUNCION PRINCIPAL
// ----------------------------------------------------------------------------
int main() {
    // 1. Cargar el dataset de palabras desde el archivo.
    std::vector<std::string> palabras = cargarPalabras("dataset.txt");

    if (palabras.empty()) {                      // si no se cargo nada, terminar
        std::cerr << "No hay palabras para ordenar.\n";
        return 1;
    }

    std::cout << "Algoritmo: BURBUJA (Bubble Sort)\n";
    std::cout << "Palabras cargadas: " << palabras.size() << "\n";

    // 2. Tomar el tiempo ANTES de ordenar.
    auto inicio = std::chrono::high_resolution_clock::now();

    bubbleSort(palabras);                        // ejecuta el ordenamiento

    // 3. Tomar el tiempo DESPUES de ordenar.
    auto fin = std::chrono::high_resolution_clock::now();

    // 4. Calcular la duracion en milisegundos.
    std::chrono::duration<double, std::milli> duracion = fin - inicio;

    std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms\n";

    // 5. Guardar el resultado ordenado en un archivo.
    guardarPalabras("salida_burbuja.txt", palabras);
    std::cout << "Resultado guardado en salida_burbuja.txt\n";

    return 0;
}
