#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para leer una matriz desde un archivo y pasarla a una variable local
void leerMatrizConDimensiones(char *nombreArchivo, int *filas, int *columnas, int matriz[100][100]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    fscanf(archivo, "%d %d", filas, columnas); // Leer las dimensiones al inicio del archivo

    for (int i = 0; i < *filas; i++) {
        for (int j = 0; j < *columnas; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }
    fclose(archivo);
}

// Función para leer un vector de palabras desde un archivo y pasar los datos a variables locales
void leerVectorConLongitudes(char *nombreArchivo, int *numPalabras, int longitudes[], char palabras[100][256]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    fscanf(archivo, "%d", numPalabras); // Leer el número de palabras al inicio del archivo

    for (int i = 0; i < *numPalabras; i++) {
        fscanf(archivo, "%s", palabras[i]);
        longitudes[i] = strlen(palabras[i]); // Calcular y almacenar la longitud de cada palabra
    }
    fclose(archivo);
}

// Función para leer una cadena completa desde un archivo
void leerCadena(char *nombreArchivo, char *cadena) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    fgets(cadena, 256, archivo); // Leer la cadena completa, suponiendo un máximo de 256 caracteres
    fclose(archivo);
}

int main() {
    // Variables locales para la matriz
    int filas, columnas;
    int matriz[100][100]; // Tamaño máximo de la matriz
    
    // Variables locales para el vector de palabras
    int numPalabras;
    int longitudes[100]; // Hasta 100 palabras
    char palabras[100][256]; // Hasta 100 palabras, máximo 256 caracteres cada una
    
    // Variable local para la cadena
    char cadena[256];

    // Leer la matriz y almacenarla en la variable local
    leerMatrizConDimensiones("matriz.txt", &filas, &columnas, matriz);
    
    // Operaciones de ejemplo con la matriz
    printf("Matriz (%d x %d):\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Leer el vector de palabras y almacenarlo en las variables locales
    leerVectorConLongitudes("vector.txt", &numPalabras, longitudes, palabras);
    
    // Operaciones de ejemplo con el vector de palabras
    printf("\nNúmero de palabras en el vector: %d\n", numPalabras);
    for (int i = 0; i < numPalabras; i++) {
        printf("Palabra %d (%d letras): %s\n", i + 1, longitudes[i], palabras[i]);
    }

    // Leer la cadena completa y almacenarla en la variable local
    leerCadena("cadena.txt", cadena);

    // Operación de ejemplo con la cadena
    printf("\nCadena leída del archivo: %s\n", cadena);

    return 0;
}
