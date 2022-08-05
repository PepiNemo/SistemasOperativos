#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t me, childpid;
    childpid=fork();
    me=getpid();
    printf("%d\n",me);
    if(childpid == 0){
        //execlp("./p2","",NULL);
        printf("Soy el baby : %d\n", me);
    }else if(childpid>0){
        printf("Finalizo : %d\n", me);
    }
    
    return 0;
}