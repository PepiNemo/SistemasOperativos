#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int status, nose;
    pid_t me, childpid;
    me = getpid();
    printf("%d\n", me);
    childpid = fork();
    if(childpid == 0){
        printf("Proceso hijo: Ejecutando.\n");
        printf("Bienvenidos a Temuco.\n");
        exit(9);
    }
    else if(childpid > 0){
        printf("Proceso padre: el PID del proceso hijo es: %d\n", childpid);
        //wait(&status);
        wait(&nose);
    }
    printf("Sugar daddy: El proceso hijo termino.\n");
    printf("Status de salida: %d\n", WEXITSTATUS(nose));
    printf("Hola");
    return 0;
}