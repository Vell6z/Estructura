// ============================================================================
//  Practica 1 - Estructura de Datos
//  Algoritmo: QUICKSORT (Ordenamiento Rapido)
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

    archivo.close();                             // cierra el archivo
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
//  PARTICION (esquema de Lomuto)
//  Escoge un pivote (el ultimo elemento) y reordena el subarreglo de modo que
//  los menores al pivote queden a su izquierda y los mayores a su derecha.
//  Devuelve la posicion final del pivote.
// ----------------------------------------------------------------------------
int particion(std::vector<std::string>& v, int bajo, int alto) {
    std::string pivote = v[alto];                // el pivote es el ultimo elemento
    int i = bajo - 1;                            // indice del ultimo "menor" hallado

    for (int j = bajo; j < alto; j++) {          // recorre el subarreglo
        if (v[j] < pivote) {                     // si el actual es menor al pivote
            i++;                                 // avanza la frontera de menores
            std::string temp = v[i];             // intercambia v[i] con v[j]
            v[i] = v[j];
            v[j] = temp;
        }
    }

    // Coloca el pivote justo despues de los menores (posicion i+1).
    std::string temp = v[i + 1];
    v[i + 1] = v[alto];
    v[alto] = temp;

    return i + 1;                                // posicion definitiva del pivote
}

// ----------------------------------------------------------------------------
//  ALGORITMO QUICKSORT (recursivo)
//  Divide y venceras: particiona el arreglo alrededor de un pivote y luego
//  ordena recursivamente las dos mitades. Complejidad promedio O(n log n).
// ----------------------------------------------------------------------------
void quickSort(std::vector<std::string>& v, int bajo, int alto) {
    if (bajo < alto) {                           // condicion base: hay >1 elemento
        int p = particion(v, bajo, alto);        // ubica el pivote y particiona

        quickSort(v, bajo, p - 1);               // ordena la mitad izquierda
        quickSort(v, p + 1, alto);               // ordena la mitad derecha
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

    std::cout << "Algoritmo: QUICKSORT\n";
    std::cout << "Palabras cargadas: " << palabras.size() << "\n";

    // 2. Tomar el tiempo ANTES de ordenar.
    auto inicio = std::chrono::high_resolution_clock::now();

    quickSort(palabras, 0, palabras.size() - 1); // ejecuta el ordenamiento

    // 3. Tomar el tiempo DESPUES de ordenar.
    auto fin = std::chrono::high_resolution_clock::now();

    // 4. Calcular la duracion en milisegundos.
    std::chrono::duration<double, std::milli> duracion = fin - inicio;

    std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms\n";

    // 5. Guardar el resultado ordenado en un archivo.
    guardarPalabras("salida_quicksort.txt", palabras);
    std::cout << "Resultado guardado en salida_quicksort.txt\n";

    return 0;
}
