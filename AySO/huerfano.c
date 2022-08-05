#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t me, childpid;
    me=fork();
    if(me>0){
        //sleep(2);
        printf("Soy hijo, mi padre tiene id es : %d\n", getppid());
    }else{
        exit(0);
    }

    return 0;
}