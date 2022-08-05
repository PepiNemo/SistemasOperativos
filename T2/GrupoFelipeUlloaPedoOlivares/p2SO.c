#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <stdbool.h>
//gcc -pthread name.c -lpthread -o eje
pthread_mutex_t pergaminoA, pergaminoB, alumno ;
pthread_cond_t ordenEstudiar, Btermino;
sem_t students;


bool Aused=false;
bool Bused=false;
int turnoA=0, turnoB=0; //Por comportamientosDistinto en el primer round
int contadorEscrituraA=1, contadorEscriturasB=0;
int contadorAlumnos=0;
int temp=0; //Tendra los valores de los contadores de Escritura A o B

int cantidadAlumnos=4; //Tiene que ser multiplo de 2, mayore que 2, por el contador del semaforo
int materias=4;// Tiene que ser mayor que 1


//Esta primera el escriba2, porque tiene menos codigo, ya que realiza menos operaciones, las elementales del A.
void* Escriba2(void* arg){
    pthread_mutex_lock(&pergaminoB);
    turnoB+=1;
    if(Bused==true && turnoB<=materias){
        //Saltar Turno
        if(contadorEscriturasB>0){contadorEscriturasB=0;}
        sleep(1);
        if(turnoB==materias){pthread_cond_signal(&Btermino);}
        pthread_mutex_unlock(&pergaminoB);
    }else if(Bused==false && turnoB<=materias){
        //Escribir
        printf("Escribire B: %d , con  %d escrituras\n", *(int*)arg, contadorEscriturasB+1);
        sleep(1);
        contadorEscriturasB+=1;
        pthread_mutex_unlock(&pergaminoB);
        if(turnoB==materias){sleep(1);pthread_cond_signal(&Btermino);}
    }
    free(arg);
}

void* Escriba1(void* arg){
    pthread_mutex_lock(&pergaminoA);
    turnoA+=1;
    if(Aused==true && turnoA<materias){
        //No hacer nada, saltar el turno.
        if(contadorEscrituraA>1){contadorEscrituraA=1;}
        sleep(1);
        pthread_mutex_unlock(&pergaminoA);
    }else if(Aused==false && turnoA<materias){
        //Escribir
        printf("Escribire A : %d , con %d escrituras\n", (*(int*)arg), contadorEscrituraA);
        sleep(1);
        if(turnoA==1){ // Caso unico del primero turno
            Aused=true;
            temp=contadorEscrituraA*4;// x4, porque Tiempo de lectura es el doble que escritura y leen 2 hilos por 1 tiempo.
            contadorAlumnos=0;
        }
        contadorEscrituraA+=1;
        pthread_mutex_unlock(&pergaminoA);
    }else if(turnoA == materias){
        //AutoDestruccion
        if(Aused==false | turnoA==1){printf("Escribire A : %d , con %d escituras\n", *(int*)arg, contadorEscrituraA);}
        pthread_cond_wait(&Btermino, &pergaminoA);
        int ordenes=(materias*2)-turnoA;
        pthread_mutex_unlock(&pergaminoA);
        printf("Autodestruccion, ordenes = %d\n", ordenes);        
        for (size_t i = 0; i < ordenes; i++)
        {
            pthread_cond_signal(&ordenEstudiar);
            pthread_cond_signal(&ordenEstudiar);
            pthread_cond_signal(&ordenEstudiar);
            pthread_cond_signal(&ordenEstudiar);
            sleep(1);
        }
        
    }
    for (size_t i = 0; i < cantidadAlumnos; i++){pthread_cond_signal(&ordenEstudiar);}
    free(arg);
}


void* Alumnos(void* arg){
    pthread_mutex_lock(&alumno);
    pthread_cond_wait(&ordenEstudiar, &alumno);
    sem_wait(&students);
    if(Aused==true){
        contadorAlumnos+=1;
        if(contadorAlumnos==temp){
            Bused=true;
            temp=contadorEscriturasB*4;
            contadorAlumnos=0;
            Aused=false;
        }
        printf("Leyendo A -> %d  contador Alumnos: %d temp: %d\n", *(int*)arg, contadorAlumnos, temp);
        pthread_mutex_unlock(&alumno);
        sleep(1);
    }else if (Bused==true){
        contadorAlumnos+=1;
        if(contadorAlumnos==temp){
            Aused=true;
            temp=contadorEscrituraA*4;
            contadorAlumnos=0;
            Bused=false;
        }
        printf("Leyendo B -> %d  contador Alumnos: %d temp: %d\n", *(int*)arg, contadorAlumnos, temp);
        pthread_mutex_unlock(&alumno);
        sleep(1);
    }
    sem_post(&students);
    free(arg);
}

void* timeSleep(void* arg){
    for (size_t i = 0; i <= materias*2; i++)
    {
        printf("----------Tiempo : %ld ----------\n", i);
        sleep(1);
    }
    
}

int main(int argc, char* argv[]){
    pthread_mutex_init(&pergaminoA, NULL);
    pthread_mutex_init(&pergaminoB,NULL);
    pthread_mutex_init(&alumno, NULL);
    pthread_cond_init(&ordenEstudiar, NULL);
    pthread_cond_init(&Btermino, NULL);
    sem_init(&students, 0, 2);
    pthread_t alumnos[cantidadAlumnos];
    pthread_t escribas[2];
    pthread_t tiempo;
    for (size_t i = 0; i < materias; i++)
    {
        if(i==0){if(pthread_create(&tiempo, NULL,&timeSleep, NULL)!=0){perror("Failed to create alumno");}}
        
        for (size_t z = 0; z < cantidadAlumnos; z++)
        {
            int* a=malloc(sizeof(int));*a=i+1;
            if(pthread_create(&alumnos[z], NULL, &Alumnos, a)!=0){perror("Failed to create alumno");}
        }
        int* e1=malloc(sizeof(int));int* e2=malloc(sizeof(int));
        *e1=i+1;*e2=i+1;
        if(pthread_create(&escribas[0], NULL, &Escriba1, e1)!=0){perror("Failed to create 1er escriba");}
        if(pthread_create(&escribas[1], NULL, &Escriba2, e2)!=0){perror("Failed to create 2DO escriba");}
    }

    //join alumnos y escribas
    for (size_t z = 0; z < cantidadAlumnos; z++)
    {
        if(pthread_join(alumnos[z], NULL)!=0){perror("Failed to join alumno");}
    }

    if(pthread_join(escribas[0], NULL)!=0){perror("Failed to join 1er escriba");}
    if(pthread_join(escribas[1], NULL)!=0){perror("Failed to join 2do escriba");}
    if(pthread_join(tiempo, NULL)!=0){perror("Failed to join tiempo");}

    pthread_mutex_destroy(&pergaminoA);
    pthread_mutex_destroy(&pergaminoB);  
    pthread_mutex_destroy(&alumno);
    pthread_cond_destroy(&ordenEstudiar);
    pthread_cond_destroy(&Btermino);
    sem_destroy(&students);       
    return 0;
}