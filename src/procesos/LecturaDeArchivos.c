#include <stdio.h>

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
