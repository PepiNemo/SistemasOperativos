#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>//nmap para compartir memoria



void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  return mmap(NULL, size, protection, visibility, 0, 0);
}

int acumulador=1;
int posicion(int n){
    pid_t temp=getpid();
    acumulador=acumulador+37;
    srand(acumulador*temp*37/2);
    return rand()%n;
}

int main(int argc, char *argv[]){
    pid_t me, temp, zulensky, newMilitar;
    void* shareMem = create_shared_memory(124); //Para que militares revisen la posicion de Zulenski
    void* shareMem2 = create_shared_memory(124); ///TerminoJuego
    void* shareMem3 = create_shared_memory(124); ///Para contar las rondas
    int acumulador=1;// Para cambiar la semilla de Srand()
    int n;//Numero de militares
    printf("Inserte un entero con el numero de militares(Hijoss) de Grusia\n");
    scanf("%d",&n);
    int militares[n+1];//n mas Zulensky
    
    //Creamos los n militares y guardamos su pid en un array militares
    for (size_t i = 0; i < n; i++){
        newMilitar=fork();
        if(newMilitar==0){
            temp= getpid();
            while(1==1){
                kill(temp, SIGSTOP);//Esperaremos a que Zulensky se esconda, y avisara para buscarlo
                //Le damos una posicion aleatoria al militar, donde podria estar Zulensky
                int position=posicion(n*7);//Habran n*5 posiciones donde podra estar Zulensky
                printf("Soy el militar: %d, con posicion: %d\n", temp, position);
                int* positionZulenksy=shareMem;//Obtenemos la ubicacion de zulensky
                if(*positionZulenksy == position){
                    //El militar encontro a Zulensky
                    printf("El militar %d , encontro a Zulensky en la posicion: %d, termino el juego\n", temp, position );
                    int* rondas=shareMem3;
                    printf("El juego duro: %d rondas \n", *rondas);
                    int terminoJuego=n*3;
                    int *termino=&terminoJuego;
                    memcpy(shareMem2, termino, sizeof(termino));
                    for (size_t z = 0; z<n+1; z++){
                        if(militares[z] != temp){
                            kill(militares[z], SIGKILL);}//Matamos todos los procesos para terminar el juego
                    }
                    kill(temp,SIGKILL);//Se suicida el militar
                }
                //Al termino de la busqueda, le sumamos 1 por cada militar que ya busco ha zulenski, para saber cuando ya todos lo buscaron
                int* contador;
                contador=shareMem2;
                int terminoJuego=*contador+1;
                int *termino=&terminoJuego;
                memcpy(shareMem2, termino, sizeof(termino));
            }  
        }
        else if(newMilitar > 0){
            militares[i]=newMilitar;//Guarmos el pid de los militares, para referenciarlos.
        }
    }


    zulensky=fork();
    if(zulensky>0){militares[n]=zulensky;}
    if(zulensky == 0){
        temp=getpid();
        while(1==1){
            //Cambiamos de posicion a Zulensky
            int position=posicion(n*7);
            int* positionZulensky=&position;
            memcpy(shareMem, positionZulensky, sizeof(positionZulensky));
            //Resetemos para otra ronda el contador de militares que buscaron
            int reset=0;
            int *numreset=&reset;
            memcpy(shareMem2, numreset, sizeof(numreset));
            printf("Zulensky : %d, posicion %d \n", temp, position);
            for (size_t x = 0; x < n; x++){
                kill(militares[x], SIGCONT);//Avisa a los milirares que lo vayan a buscar.
            }
            
            int* termino;
            termino=shareMem2;
            //Esperar a que los militares lo busquen en un spinlock
            while(*termino<n){
                int* termino;
                termino=shareMem2;
            } 
            if(*termino==n*3){printf("Se suicida Zulensky\n"); exit(9);}//Termino el juego
            printf("Zulensky se va de la posicion %d \n", position);
            int* rondasAnt;
            rondasAnt=shareMem3;
            int actual=1+*rondasAnt;
            int* rondasActual=&actual;
            memcpy(shareMem3, rondasActual, sizeof(rondasActual));
            printf("-------------------------Comienza otra ronda: %d-------------------------\n", actual);
            //sleep(1);//Para poder ver mas lento el output, se pude comentar
        }
    }
    ///sleep(1);
    int* termino;
    termino=shareMem2;
    while(*termino<n*3){
        int* termino;
        termino=shareMem2;
        //printf(".\n");
    }
    return 0;
}