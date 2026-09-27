// ============================================================================
//  Practica 1 - Estructura de Datos
//  Algoritmo: ORDENAMIENTO POR INSERCION (Insertion Sort)
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
//  ALGORITMO INSERCION
//  Construye el arreglo ordenado un elemento a la vez: toma cada elemento y
//  lo "inserta" en su posicion correcta dentro de la parte ya ordenada a su
//  izquierda, desplazando los mayores hacia la derecha. Complejidad O(n^2).
// ----------------------------------------------------------------------------
void insertionSort(std::vector<std::string>& v) {
    int n = v.size();                            // cantidad de elementos a ordenar

    // Empezamos en 1 porque el primer elemento se considera ya ordenado.
    for (int i = 1; i < n; i++) {
        std::string clave = v[i];                // elemento actual a insertar
        int j = i - 1;                           // indice del ultimo ya ordenado

        // Desplaza a la derecha todos los que sean mayores que 'clave'.
        while (j >= 0 && v[j] > clave) {         // mientras haya mayores a la izq.
            v[j + 1] = v[j];                     // mueve el elemento una posicion
            j--;                                 // sigue comparando hacia la izq.
        }

        v[j + 1] = clave;                        // coloca la clave en su hueco correcto
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

    std::cout << "Algoritmo: INSERCION (Insertion Sort)\n";
    std::cout << "Palabras cargadas: " << palabras.size() << "\n";

    // 2. Tomar el tiempo ANTES de ordenar.
    auto inicio = std::chrono::high_resolution_clock::now();

    insertionSort(palabras);                     // ejecuta el ordenamiento

    // 3. Tomar el tiempo DESPUES de ordenar.
    auto fin = std::chrono::high_resolution_clock::now();

    // 4. Calcular la duracion en milisegundos.
    std::chrono::duration<double, std::milli> duracion = fin - inicio;

    std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms\n";

    // 5. Guardar el resultado ordenado en un archivo.
    guardarPalabras("salida_insercion.txt", palabras);
    std::cout << "Resultado guardado en salida_insercion.txt\n";

    return 0;
}
