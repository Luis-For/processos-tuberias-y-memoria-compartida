#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void manejador_senal(int sig) {
    printf("Hijo %d: Señal recibida, continuando...\n", getpid());
}

void tree(pid_t pid){
    char command[50];
    sprintf(command, "pstree -pl %d", pid);
    system(command);
}


int main(int argc, char const *argv[])
{
    int i=0, numeroDeHijos=3;
    pid_t childrens[numeroDeHijos];
    pid_t root=getpid();

    //create of process
    printf("el pid proceso padre: %d", root);
    for(i=0; i<numeroDeHijos; i++){
        if((childrens[i]=fork())==0){
            //hijo
            printf("Hijo %d creado, PID: %d, PID del padre: %d\n", i+1, getpid(), getppid());
            signal(SIGUSR1, manejador_senal);

            // Pausamos el proceso hijo hasta recibir la señal para continuar
            pause();
            // Continuar con el proceso hijo
            printf("Hijo %d: Ahora continuaré con mi tarea...\n", i+1);
            exit(0);
        }else{
            //padre
            sleep(1);   //para visualizar la jeradquia de procesos
        }
    }

    return 0;
}
