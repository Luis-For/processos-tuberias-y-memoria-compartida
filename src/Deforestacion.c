#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <pthread.h>

// Constantes de comportamiento del bosque
#define DEFORESTADO 0
#define BOSQUE 1
#define REGENERADO 2
//#define TIME 10

//Datos globales
int anios, filas, columnas;
int **matriz, **nueva_matriz;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void mostrarMatriz(int filas, int columnas, int matriz[filas][columnas]) {
    printf("\nMatriz leída:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void calculandoIndices(char *nameOfArchive,int *filas, int *columnas, int *anios){
    FILE *archivo=fopen(nameOfArchive,"r");
    if (archivo == NULL) {
        perror("Error al abrir el fichero");
        exit(EXIT_FAILURE);
    }

    // Leer el número total, filas y columnas
    fscanf(archivo, "%d", anios);
    fscanf(archivo, "%d", filas);
    fscanf(archivo, "%d", columnas);
    //matriz[filas][columnas];
    fclose(archivo);
    //fscanf("%d %d %d", anios, filas, columnas);
}

void leyendoArchivo(char *nameOfArchive,int filas, int columnas,int matriz[filas][columnas]){
    FILE *archivo=fopen(nameOfArchive,"r");
    if (archivo == NULL) {
        perror("Error al abrir el fichero");
        exit(EXIT_FAILURE);
    }
    int ignoresAux; 
    fscanf(archivo, "%d", &ignoresAux);
    fscanf(archivo, "%d", &ignoresAux);
    fscanf(archivo, "%d", &ignoresAux);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo,"%d",&matriz[i][j]);
        }
        printf("\n");
    }
}

void copiarMatriz(int **origen, int **destino, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            destino[i][j] = origen[i][j]; // Copiar valor
        }
    }
}

//vecinos
void revisarVecinos(int filas, int columnas){
    /*  [-1,-1]  [-1,0]  [-1,1]
        [0,-1]   [nop]   [0,1]    
        [1,-1]   [1,0]   [1,1]
    */
    int direccionesI[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 
    int direccionesJ[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            
        }
    }
}

//bosque a deforestado
//bosque a deforestado
// Hilo 1: Bosque a Deforestado
void* hilo1(void* arg) {
    printf("\nHILO 1 INICIADO\n");
    /*  [-1,-1]  [-1,0]  [-1,1]
        [0,-1]   [nop]   [0,1]    
        [1,-1]   [1,0]   [1,1]
    */
    int direccionesI[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 
    int direccionesJ[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 
    int vecinosDeforestados = 0;
    for(int time=0; time<anios; time++){
        for(int i = 0; i < filas; i++) {
            for(int j = 0; j < columnas; j++) {
                if(matriz[i][j] == BOSQUE) {
                    for(int k = 0; k < 8; k++) {  // 8 direcciones
                        int ni = i + direccionesI[k];
                        int nj = j + direccionesJ[k];
                        
                        if(ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                            if(matriz[ni][nj] == DEFORESTADO) {
                                vecinosDeforestados++;
                            }
                        }
                    }
                    if(vecinosDeforestados >= 4 && matriz[i][j] == BOSQUE) {
                        pthread_mutex_lock(&mutex);  // Bloquear el mutex antes de modificar
                        nueva_matriz[i][j] = DEFORESTADO;
                        pthread_mutex_unlock(&mutex);  // Liberar el mutex después de modificar
                    }
                    vecinosDeforestados = 0;
                }
            }
        }
    }
    printf("\nHILO 1 TERMINADO\n");
    return NULL;
}

// Hilo 2: Deforestado a Regenerado
void* hilo2(void* arg) {
    printf("\nHILO 2 INICIADO\n");
    int direccionesI[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 
    int direccionesJ[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 
    
    int vecinosDeforestados = 0;
    for(int time=0; time<anios; time++){
        for(int i = 0; i < filas; i++) {
            for(int j = 0; j < columnas; j++) {
                if(matriz[i][j] == DEFORESTADO) {
                    for(int k = 0; k < 8; k++) {  // Recorriendo las 8 direcciones
                        int ni = i + direccionesI[k];
                        int nj = j + direccionesJ[k];
                        
                        if(ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                            if(matriz[ni][nj] == REGENERADO) {
                                vecinosDeforestados++;
                            }
                        }
                    }
                    if(vecinosDeforestados >= 5 && matriz[i][j] == DEFORESTADO) {
                        pthread_mutex_lock(&mutex);  // Bloquear el mutex antes de modificar
                        nueva_matriz[i][j] = REGENERADO;
                        pthread_mutex_unlock(&mutex);  // Liberar el mutex después de modificar
                    }
                    vecinosDeforestados = 0;
                }
            }
        }
    }
    printf("\nHILO 2 TERMINADO\n");
    return NULL;
}

int main(int argc, char const *argv[])
{       
    pthread_t tid1, tid2;   //identificadores de los 2 hilos
    const char *NAME_ARCHIVE="/home/luis-for/Documentos/hilos_c/deforestacion.txt";
    //int anios, filas, columnas;
    anios=0;

    //lectura del fichero y creacion de la matriz -----------------------------------------------------------
    calculandoIndices(NAME_ARCHIVE, &filas, &columnas, &anios);
    int matrizDeforestacion[filas][columnas];
    leyendoArchivo(NAME_ARCHIVE, filas, columnas, matrizDeforestacion);
    mostrarMatriz(filas, columnas, matrizDeforestacion);

    //asignandole memoria a la matriz dinamica
    matriz=malloc(filas *sizeof(int *));
    for(int i=0; i<filas; i++){
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }

    //pasamos la matriz a dinamica global
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = matrizDeforestacion[i][j]; 
        }
    }

    // Creando la nueva matriz
    nueva_matriz = malloc(filas * sizeof(int *));
    for (int i = 0; i < filas; i++) {
        nueva_matriz[i] = (int *)malloc(columnas * sizeof(int)); 
    }

    // Copiar los datos de la matriz original a la nueva
    copiarMatriz(matriz, nueva_matriz, filas, columnas);
    
    // Mostrar las matrices
    printf("Matriz original:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }


    //creando los hilos--------------------------------------------------------------------------------------------------------
    pthread_create(&tid1, NULL, hilo1, NULL);
    pthread_create(&tid2, NULL, hilo2, NULL);

    //esperamos a que los hilos terminen
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("\nMatriz final:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", nueva_matriz[i][j]);
        }
        printf("\n");
    }

    //liberando espacio en memoria
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
        free(nueva_matriz[i]);
    }
    free(matriz);
    free(nueva_matriz);

    //pthread_mutex_init(&mutex, NULL);

    //Procesando la matriz para que los hilos la trabajen------------------------------------------------------------------------
   /*for(anios; anios<TIME; anios++){

    }*/

    return 0;
}
