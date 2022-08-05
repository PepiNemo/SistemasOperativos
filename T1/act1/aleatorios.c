#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
char elecciones[][8]={"Roca","Papel","Tijera"};
char string[80];
char string2[80];

char* elegir(int semilla){
    srand (getpid()*semilla);
    printf("Pid: %d\n",getpid()*semilla);
    int numero = rand()%3;
    strcpy(string, elecciones[numero]);
}

int main(int argc, char *argv[]){
    pid_t me, childpid;
    int numero;
    childpid=fork();
    for (size_t i = 0; i < 3; i++)
    {
        if(childpid>0){
            printf("Padre elige: %s\n",elegir(9531*i+3));
        }
        if(childpid == 0){
            elegir(5471*i+1);

            printf("Hijo elige: %s\n",string);
        }
    }
    return 0;
}