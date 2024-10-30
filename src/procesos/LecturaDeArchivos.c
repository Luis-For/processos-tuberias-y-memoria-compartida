#include <stdio.h>
#include <stdlib.h>

// Función para leer una matriz desde un archivo
void leerMatriz(char *nombreArchivo, int filas, int columnas, int matriz[filas][columnas]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }
    fclose(archivo);
}

// Función para leer un vector desde un archivo
void leerVector(char *nombreArchivo, int longitud, int vector[longitud]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    for (int i = 0; i < longitud; i++) {
        fscanf(archivo, "%d", &vector[i]);
    }
    fclose(archivo);
}

// Función para leer una cadena desde un archivo
void leerCadena(char *nombreArchivo, char *cadena, int longitud) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    fgets(cadena, longitud, archivo);
    fclose(archivo);
}
// Función para mostrar una matriz
void mostrarMatriz(int filas, int columnas, int matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para mostrar un vector
void mostrarVector(int longitud, int vector[longitud]) {
    for (int i = 0; i < longitud; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

// Función para mostrar una cadena
void mostrarCadena(char *cadena) {
    printf("%s\n", cadena);
}

// Función para calcular dimensiones de la matriz
void calcularDimensionesMatriz(char *nombreArchivo, int *filas, int *columnas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    int tempColumnas = 0, tempFilas = 0;
    char linea[256];
    
    // Leer primera línea para contar columnas
    if (fgets(linea, sizeof(linea), archivo)) {
        tempFilas++;
        char *token = strtok(linea, " ");
        while (token) {
            tempColumnas++;
            token = strtok(NULL, " ");
        }
    }

    // Contar el resto de filas
    while (fgets(linea, sizeof(linea), archivo)) {
        tempFilas++;
    }
    *filas = tempFilas;
    *columnas = tempColumnas;

    fclose(archivo);
}

// Función para calcular número de palabras y longitud de cada palabra en un vector
void calcularLongitudPalabras(char *nombreArchivo, int *numPalabras, int longitudes[]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    *numPalabras = 0;
    char palabra[256];
    
    // Leer cada palabra y contar longitud
    while (fscanf(archivo, "%s", palabra) != EOF) {
        longitudes[*numPalabras] = strlen(palabra);
        (*numPalabras)++;
    }

    fclose(archivo);
}

// Función para leer y mostrar una matriz con dimensiones calculadas
void leerYMostrarMatriz(char *nombreArchivo, int filas, int columnas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }
    int matriz[filas][columnas];

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    fclose(archivo);
}

// Función para mostrar longitudes de palabras en un vector de caracteres
void mostrarLongitudesPalabras(int numPalabras, int longitudes[]) {
    for (int i = 0; i < numPalabras; i++) {
        printf("Palabra %d: %d letras\n", i + 1, longitudes[i]);
    }
}

// Función para leer una matriz desde un archivo con dimensiones especificadas al inicio
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

// Función para leer un vector de palabras desde un archivo con el número de palabras especificado al inicio
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

// Función para mostrar una matriz
void mostrarMatriz(int filas, int columnas, int matriz[100][100]) {
    printf("Matriz (%d x %d):\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para mostrar longitudes y contenido de palabras en el vector
void mostrarLongitudesPalabras(int numPalabras, int longitudes[], char palabras[100][256]) {
    printf("Número de palabras en el vector: %d\n", numPalabras);
    for (int i = 0; i < numPalabras; i++) {
        printf("Palabra %d (%d letras): %s\n", i + 1, longitudes[i], palabras[i]);
    }
}

int main() {
    
    return 0;
}
