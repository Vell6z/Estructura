// ============================================================================
//  Practica 1 - Estructura de Datos
//  Algoritmo: MERGESORT (Ordenamiento por Mezcla)  [cuarto algoritmo elegido]
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
//  MEZCLA (merge)
//  Combina dos mitades ya ordenadas [izq..medio] y [medio+1..der] en un solo
//  segmento ordenado, usando vectores temporales.
// ----------------------------------------------------------------------------
void merge(std::vector<std::string>& v, int izq, int medio, int der) {
    int n1 = medio - izq + 1;                    // tamano de la mitad izquierda
    int n2 = der - medio;                        // tamano de la mitad derecha

    std::vector<std::string> L(n1);              // vector temporal izquierdo
    std::vector<std::string> R(n2);              // vector temporal derecho

    for (int i = 0; i < n1; i++)                 // copia datos a la mitad izquierda
        L[i] = v[izq + i];
    for (int j = 0; j < n2; j++)                 // copia datos a la mitad derecha
        R[j] = v[medio + 1 + j];

    int i = 0;                                   // indice para recorrer L
    int j = 0;                                   // indice para recorrer R
    int k = izq;                                 // indice de escritura en v

    // Mezcla comparando el frente de cada mitad y tomando el menor.
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {                      // si el de la izquierda es menor/igual
            v[k] = L[i];                         // lo coloca en v
            i++;
        } else {                                 // si el de la derecha es menor
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {                             // copia lo que quede en L
        v[k] = L[i];
        i++; k++;
    }

    while (j < n2) {                             // copia lo que quede en R
        v[k] = R[j];
        j++; k++;
    }
}

// ----------------------------------------------------------------------------
//  ALGORITMO MERGESORT (recursivo)
//  Divide y venceras: parte el arreglo por la mitad, ordena cada mitad de
//  forma recursiva y luego las mezcla. Complejidad O(n log n) garantizada.
// ----------------------------------------------------------------------------
void mergeSort(std::vector<std::string>& v, int izq, int der) {
    if (izq < der) {                             // condicion base: hay >1 elemento
        int medio = izq + (der - izq) / 2;       // punto medio (evita overflow)

        mergeSort(v, izq, medio);                // ordena la mitad izquierda
        mergeSort(v, medio + 1, der);            // ordena la mitad derecha

        merge(v, izq, medio, der);               // mezcla ambas mitades ordenadas
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

    std::cout << "Algoritmo: MERGESORT\n";
    std::cout << "Palabras cargadas: " << palabras.size() << "\n";

    // 2. Tomar el tiempo ANTES de ordenar.
    auto inicio = std::chrono::high_resolution_clock::now();

    mergeSort(palabras, 0, palabras.size() - 1); // ejecuta el ordenamiento

    // 3. Tomar el tiempo DESPUES de ordenar.
    auto fin = std::chrono::high_resolution_clock::now();

    // 4. Calcular la duracion en milisegundos.
    std::chrono::duration<double, std::milli> duracion = fin - inicio;

    std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms\n";

    // 5. Guardar el resultado ordenado en un archivo.
    guardarPalabras("salida_mergesort.txt", palabras);
    std::cout << "Resultado guardado en salida_mergesort.txt\n";

    return 0;
}
