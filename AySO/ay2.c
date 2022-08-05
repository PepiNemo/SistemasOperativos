#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t me, childpid;
    me = getpid();
    printf("%d\n", me);
    childpid = fork();
    printf("%d\n", childpid);
    return 0;
}