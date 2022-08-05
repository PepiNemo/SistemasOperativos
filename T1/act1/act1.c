#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

pid_t jugador1;
pid_t jugador2;
char elecciones[][8]={"Roca","Papel","Tijera"};
char string[8] ;
char string2[8];

void elegir(int semilla, int jugador){
    srand (getpid()*semilla);
    int numero = rand()%3;
    if(jugador==1){strcpy(string, elecciones[numero]);}
    if(jugador==2){strcpy(string2, elecciones[numero]);}
}

void crearJugador(int numJugador, int rw[2], int rw2[2]){
    if(numJugador == 1){
        jugador1=fork();
        if(jugador1==0){
            //Jugador 1:
            int contador=0;
            while(1==1){
                //printf("Soy j1:%d\n", temp);
                contador+=3;
                pid_t temp=getpid();
                elegir(temp/contador*9531, numJugador);
                write(rw[1], string, (strlen(string)+1));
                kill(temp, SIGSTOP);
            }
        }
    }else if(numJugador==2){
        jugador2=fork();
        if(jugador2==0){
            //Jugador 2:
            int contador= 43;
            while(1==1){
                contador+=37;
                pid_t temp=getpid();
                //printf("Soy j2:%d\n", temp);
                elegir(temp/contador*5471, numJugador);
                write(rw2[1], string2, (strlen(string2)+1));
                kill(temp, SIGSTOP);
            }
        }
    }

}


int main(int argc, char *argv[]){
    int rw[2], rw2[2], diferenciador=0, status;
    pid_t arbitro;
    char readbuffer[80], readbuffer2[80];
    pipe(rw);
    pipe(rw2);
    crearJugador(1, rw, rw2);
    crearJugador(2, rw, rw2);
    if(jugador1 > 0 && jugador2 > 0){
        int seguirjugando=1;//1->Seguir jugando ; Cualquier otro->No
        
        while (seguirjugando==1){
            //Abitro
            read(rw[0], readbuffer, sizeof(readbuffer));
            read(rw2[0], readbuffer2, sizeof(readbuffer2));
            while(strlen(readbuffer) == 0 && strlen(readbuffer2) == 0){printf("Esperando haber leido .... \n");}
            printf("\nTenemos j1:%d -> eligio:%s \n Ademas j2:%d -> eligio:%s \n",jugador1, readbuffer, jugador2, readbuffer2);

            if((strcmp(readbuffer,"Roca")==0 && strcmp(readbuffer2,"Papel")== 0)    |
               (strcmp(readbuffer,"Papel")==0 && strcmp(readbuffer2,"Tijera")== 0)  |
               (strcmp(readbuffer,"Tijera")==0 && strcmp(readbuffer2,"Roca")== 0)   )
            {
                printf("\n-------Gano el jugador 2, muere el j1-------\n");
                kill(jugador1, SIGKILL);
                crearJugador(1, rw, rw2);
                kill(jugador2, SIGCONT);
            }
            else if( (strcmp(readbuffer,"Roca")==0 && strcmp(readbuffer2,"Tijera")== 0) |
                     (strcmp(readbuffer,"Papel")==0 && strcmp(readbuffer2,"Roca")== 0)  |
                     (strcmp(readbuffer,"Tijera")==0 && strcmp(readbuffer2,"Papel")== 0))
            {
                printf("\n-------Gano el jugador 1, muere el j2-------\n");
                kill(jugador2, SIGKILL);
                crearJugador(2, rw, rw2);
                kill(jugador1, SIGCONT);
            }
            else if(strcmp(readbuffer, readbuffer2)==0){
                printf("\n-------Empate-------\n");
                kill(jugador1, SIGCONT);
                kill(jugador2, SIGCONT);
            }

            printf("\nSi quieres otra ronda ingresa un 1, si no cualquier otro numero \n");
            scanf("%d", &seguirjugando);
            
        }
    }
    return 0;
}