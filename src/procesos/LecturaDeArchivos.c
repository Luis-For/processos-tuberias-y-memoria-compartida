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

int main() {
    FILE *file = fopen("archivo.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el fichero");
        return 1;
    }

    fseek(file, 0, SEEK_END); // Moverse al final del fichero
    long size = ftell(file); // Obtener la posición actual (tamaño del fichero)
    fseek(file, 0, SEEK_SET); // Regresar al inicio del fichero

    printf("Tamaño del fichero: %ld bytes\n", size);
    
    fclose(file);
    return 0;
}
