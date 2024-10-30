#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define WORDS_COUNT 4
#define WORD_MAX_LEN 20

// Función para inicializar una matriz en la memoria compartida
void inicializarMatriz(int *matriz, int filas, int columnas) {
    int valor = 1;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i * columnas + j] = valor++;
        }
    }
}

// Función para inicializar el vector de palabras en la memoria compartida
void inicializarVectorPalabras(char (*vector)[WORD_MAX_LEN], int numPalabras) {
    strcpy(vector[0], "alex");
    strcpy(vector[1], "box");
    strcpy(vector[2], "cx");
    strcpy(vector[3], "xyz");
}

// Función para que cada hijo sume una porción de la matriz
void procesarMatriz(int *matriz, int filas, int columnas, int *resultado, int id, int numHijos) {
    int suma = 0;
    int inicio = id * (filas / numHijos);
    int fin = (id == numHijos - 1) ? filas : (id + 1) * (filas / numHijos);

    for (int i = inicio; i < fin; i++) {
        for (int j = 0; j < columnas; j++) {
            suma += matriz[i * columnas + j];
        }
    }
    resultado[id] = suma;
}

// Función para que cada hijo analice una palabra del vector y busque 'x' con 'a', 'b' o 'c' al lado
void procesarPalabra(char (*vector)[WORD_MAX_LEN], int *resultado, int id) {
    int flag = 0;
    for (int i = 0; i < strlen(vector[id]); i++) {
        if (vector[id][i] == 'x') {
            flag = 1;
            if (i > 0 && (vector[id][i - 1] == 'a' || vector[id][i - 1] == 'b' || vector[id][i - 1] == 'c')) {
                flag = 2;
                break;
            }
            if (i < strlen(vector[id]) - 1 && (vector[id][i + 1] == 'a' || vector[id][i + 1] == 'b' || vector[id][i + 1] == 'c')) {
                flag = 2;
                break;
            }
        }
    }
    resultado[id] = flag;
}

int main(int argc, char *argv[]) {
    int numHijos = atoi(argv[1]);
    if (numHijos < 1) {
        fprintf(stderr, "Número de hijos debe ser mayor que 0\n");
        exit(1);
    }

    // Crear memoria compartida para la matriz, vector de palabras y los resultados
    int shmidMatriz = shmget(IPC_PRIVATE, MATRIX_ROWS * MATRIX_COLS * sizeof(int), IPC_CREAT | 0666);
    int shmidPalabras = shmget(IPC_PRIVATE, WORDS_COUNT * WORD_MAX_LEN * sizeof(char), IPC_CREAT | 0666);
    int shmidResultadoMatriz = shmget(IPC_PRIVATE, numHijos * sizeof(int), IPC_CREAT | 0666);
    int shmidResultadoPalabras = shmget(IPC_PRIVATE, WORDS_COUNT * sizeof(int), IPC_CREAT | 0666);

    int *matriz = (int *)shmat(shmidMatriz, NULL, 0);
    char (*vectorPalabras)[WORD_MAX_LEN] = (char (*)[WORD_MAX_LEN])shmat(shmidPalabras, NULL, 0);
    int *resultadoMatriz = (int *)shmat(shmidResultadoMatriz, NULL, 0);
    int *resultadoPalabras = (int *)shmat(shmidResultadoPalabras, NULL, 0);

    // Inicializar datos en la memoria compartida
    inicializarMatriz(matriz, MATRIX_ROWS, MATRIX_COLS);
    inicializarVectorPalabras(vectorPalabras, WORDS_COUNT);

    for (int i = 0; i < numHijos; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Código para el hijo i - procesar matriz y vector de palabras
            procesarMatriz(matriz, MATRIX_ROWS, MATRIX_COLS, resultadoMatriz, i, numHijos);
            if (i < WORDS_COUNT) {
                procesarPalabra(vectorPalabras, resultadoPalabras, i);
            }
            exit(0); // Finalizar hijo
        }
    }

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < numHijos; i++) {
        wait(NULL);
    }

    // El padre muestra los resultados
    printf("Resultados de la suma de porciones de la matriz:\n");
    for (int i = 0; i < numHijos; i++) {
        printf("Suma del hijo %d: %d\n", i + 1, resultadoMatriz[i]);
    }

    printf("\nResultados de la búsqueda en el vector de palabras:\n");
    for (int i = 0; i < WORDS_COUNT; i++) {
        printf("Resultado para palabra %d ('%s'): %d\n", i + 1, vectorPalabras[i], resultadoPalabras[i]);
    }

    // Liberar memoria compartida
    shmdt(matriz);
    shmdt(vectorPalabras);
    shmdt(resultadoMatriz);
    shmdt(resultadoPalabras);

    shmctl(shmidMatriz, IPC_RMID, NULL);
    shmctl(shmidPalabras, IPC_RMID, NULL);
    shmctl(shmidResultadoMatriz, IPC_RMID, NULL);
    shmctl(shmidResultadoPalabras, IPC_RMID, NULL);

    return 0;
}
