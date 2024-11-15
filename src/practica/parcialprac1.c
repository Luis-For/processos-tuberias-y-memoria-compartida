#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void creationsOfChildrens(int childrens, pid_t root){
    for (int i = 0; i < childrens; i++)
    {
        if(!fork()) break;
    }
    if(root==getpid()){
        tree(root);
    }
}

void tree(pid_t pid){
    char command[50];
    sprintf(command, "pstree -pl %d", pid);
    system(command);
}

int main(int argc, char const *argv[])
{
    const pid_t ROOT=getpid();
    creationsOfChildrens(3,ROOT);
    //tree(ROOT);
    
    return 0;
}
