#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
char arrAcronia[4*2][10]; 
int militares[4+1];

int posicion(int n){
    pid_t temp=getpid();
    srand(temp*37/2);
    return rand()%n;
}

int main(int argc, char *argv[]){
    pid_t me, temp, zulensky;
    int n=3;
    me=getpid();
    zulensky=fork();
    militares[n+1]=zulensky;
    if(zulensky == 0){
        while(1==1){
            temp=getpid();
            int position=posicion(4*2);
            printf("Zulensky : %d, posicion %d \n", temp, position);
            strcpy(arrAcronia[position],"Zulensky");
            printf("Zulensky en arrAcronia : %s , %d \n",arrAcronia[position], position );
            kill(temp, SIGSTOP);
            printf("Zulensky se va de posicion %d \n", position);
            strcpy(arrAcronia[position],"");
        }
    }
    sleep(1);
    for (size_t i = 0; i < n; i++){
        //sleep(1);
        pid_t newMilitar=fork();
        if(newMilitar==0){
            while(1==1){
                temp= getpid();
                int position=posicion(4*2);
                printf("Soy el militar: %d, con posicion: %d, y encontre: %s\n", temp, position, arrAcronia[position]);
                if(strcmp(arrAcronia[position], "Zulensky") == 0){
                    printf("El militar %d , encontro a Zulensky en la posicion: %d", temp, position );
                    for (size_t z = 0; z < 4; z++)
                    {
                        if(militares[z] != me){
                            kill(militares[z], SIGKILL);
                        }
                    }
                    kill(me, SIGKILL);
                    
                }
                kill(temp, SIGSTOP);
                printf("Seguimooos ..., ahora muero \n");
                //exit(9);
            }
            
        }
        if(newMilitar > 0){
            militares[i]=newMilitar;
        }
    }



    sleep(1);
    printf("EL militar 2 tiene id : %d \n", militares[1]);
    kill(militares[1], SIGCONT);
    
    return 0;
}