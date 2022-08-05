#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
char hola[80];
int HornoEnUso=0; //0 => Libre 1=>En uso

int main(int argc, char *argv[]){
    pid_t me, childpid;
    //hola[0]='c';
    for (size_t i = 0; i < 3; i++)
    {
        childpid=fork();
        if(childpid>0){
            while(HornoEnUso==1){
            printf("Estoy esperando el horno ... \n");
            sleep(1);
            }
            HornoEnUso=1;
            me=getpid();
            printf("Estoy cocinando ... : %d \n", me);
            sleep(2);
            HornoEnUso=0;

        }
        exit
    }
    

    return 0;
}