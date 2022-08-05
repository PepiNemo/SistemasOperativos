#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
		
	pid_t me, childpid, asdf;
	me = getpid();
	printf("%d: Yo soy \n", me);
	childpid = fork();
	
	if(childpid == 0){
		printf("Proceso hijo: pronto a llamar a exec().\n");
		asdf = getpid();
		printf("%d : Hijo pid \n", asdf);
		execlp("./wazza","",NULL);
		printf("Proceso hijo: exec() terminado.\n");
	}
	else if(childpid > 0)
	{
		printf("Proceso padre: el PID del proceso hijo es: %d\n", childpid);
		wait(NULL);
	}
	
	printf("Sugar daddy: El proceso hijo termino.\n");
	
	return 0;
}
