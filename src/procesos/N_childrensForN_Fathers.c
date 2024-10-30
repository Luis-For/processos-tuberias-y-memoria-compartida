#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

void crearHijosConTuberias(int n) {
    int pipes[n][2]; // Arreglo de tuberías para comunicación entre hijos
    pid_t pid;
    
    // Crear todas las tuberías antes de los hijos
    for (int i = 0; i < n; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Error al crear la tubería");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        pid = fork();
        
        if (pid == -1) {
            perror("Error al crear el hijo");
            exit(1);
        } else if (pid == 0) { // Código para el hijo i
            char mensaje[BUFFER_SIZE];
            
            // Cerrar la escritura de la tubería de entrada y la lectura de la tubería de salida
            if (i > 0) close(pipes[i - 1][1]); // Cierra la escritura de la tubería anterior
            if (i < n - 1) close(pipes[i][0]); // Cierra la lectura de la tubería actual
            
            // Leer mensaje de la tubería anterior si no es el primer hijo
            if (i > 0) {
                read(pipes[i - 1][0], mensaje, BUFFER_SIZE);
                close(pipes[i - 1][0]); // Cerrar lectura después de leer
            } else {
                // Si es el primer hijo, inicializamos mensaje con algo del padre
                strcpy(mensaje, "Mensaje inicial del padre");
            }

            // Aquí es donde cada hijo puede operar con el mensaje antes de enviarlo
            printf("Hijo %d recibió el mensaje: %s\n", i + 1, mensaje);

            // Operación de ejemplo (agregar texto al mensaje)
            char temp[BUFFER_SIZE];
            snprintf(temp, BUFFER_SIZE, " -> Modificado por hijo %d", i + 1);
            strncat(mensaje, temp, BUFFER_SIZE - strlen(mensaje) - 1);

            // Enviar mensaje al siguiente hijo o de vuelta al padre si es el último hijo
            if (i < n - 1) {
                write(pipes[i][1], mensaje, strlen(mensaje) + 1);
                close(pipes[i][1]); // Cerrar escritura después de enviar
            } else {
                // Si es el último hijo, devolver al padre
                write(pipes[0][1], mensaje, strlen(mensaje) + 1);
                close(pipes[0][1]); // Cerrar escritura después de enviar al padre
            }
            exit(0); // Termina el proceso hijo
        }
    }

    // Código para el proceso padre
    char mensajeFinal[BUFFER_SIZE];
    close(pipes[0][1]); // Cerrar la escritura de la primera tubería del padre

    // Leer el mensaje final de la última tubería de vuelta del último hijo
    read(pipes[0][0], mensajeFinal, BUFFER_SIZE);
    close(pipes[0][0]); // Cerrar lectura después de leer el mensaje final

    // Esperar a todos los hijos para que terminen
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    // Mostrar el mensaje final recibido
    printf("Mensaje final en el padre: %s\n", mensajeFinal);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número de hijos>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        fprintf(stderr, "El número de hijos debe ser mayor que 0\n");
        exit(1);
    }

    crearHijosConTuberias(n);

    return 0;
}
