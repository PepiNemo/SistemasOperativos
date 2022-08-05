#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void tenerHijo(pid_t hijo){
    hijo=fork();

}

int main(int argc, char *argv[]){
    pid_t arbitro, jugador1, jugador2;
    jugador1=fork();
    if(jugador1>0){jugador2=fork();}
    if(jugador1>0 && jugador2>0){       
        for (size_t i = 0; i < 3; i++){
            printf("Recibo papel de j1: %d \n", jugador1);
            printf("Recibo tijera de j2: %d \n", jugador2);
            printf("Gana jugador 2, por lo que muere j1 y pasa otro a jugar \n");
            kill(jugador1, SIGKILL);
            jugador1=fork();
        }
    }
    

    return 0;
}