#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t me, childpid, status;
    me = getpid();
    printf("%d\n", me);
    childpid = fork();
    if(childpid == 0){
        me=getpid();
        printf("Hijo: Me estoy ejecutando, mi pid es : %d\n", me);
        printf("Fuaaaaaa Transformacioooon, ahora me salgo con exit(9)\n");
        exit(9);
        printf("No me quiero ir señor stark\n");
    }else if(childpid > 0){
        printf("Padre: Tengo que esperar a este pendejo ...\n");
        wait(&status);//Almacena la variable de exit, cuando el hijo termino se ejecutarse
        printf("Padre: Por fin llego este chavalin, con un exit : %d\n", WEXITSTATUS(status));
    }
    me=getpid();
    printf("Soy un sobreviviente, mi pid es : %d\n", me);

    return 0;
}