#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t me, childpid;
    me = getpid();
    printf("Mi pid es: %d\n", me);
    printf("El valor por defecto de childpid es : %d \n", childpid);
    childpid = fork();
    if(childpid == 0){
        printf("Yo soy el hijo, por lo que mi childpid es : %d\n",childpid);
        me=getpid();
        printf("Hijo: El pid de este proceso es : %d \n",me);
    }else if (childpid >0){
        printf("Padre: Yo soy el padre, ya que yo si invoque a childpid=fork(), y el pid del hijo es : %d\n",childpid);
    }
    return 0;
}