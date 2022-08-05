#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t mutex;

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[],int arr2[],int arr3[],int arr4[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
 

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        
        swap(&arr[min_idx], &arr[i]);
        swap(&arr2[min_idx], &arr2[i]);
        swap(&arr3[min_idx], &arr3[i]);
        swap(&arr4[min_idx], &arr4[i]);
    }
}
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int k[10]={0,1,2,3,4,5,6,7,8,9};
int hilo[10]= {1,2,3,4,5,6,7,8,9,10};
int total[10]={6,1,7,8,2,4,8,1,6,9};
int dia[10]=  {0,4,2,3,5,6,1,2,3,4};
int hora[10]={12,2,4,8,16,22,7,9,21,7};

int lunes=24;
int martes=24;
int miercoles=24;
int jueves=24;
int viernes=24;
int sabado=24;
int domingo=24;

void* schedulling(void* arg) {
    pthread_mutex_lock(&mutex);
        int a = *(int*)arg;
        //int b = *(int*)arg2;
        //int c = *(int*)arg3;
        //int d = *(int*)arg4;
        printf("%d ",a);

        printf("%d ",hilo[a]);
        printf("%d ",total[a]);
        printf("%d ",dia[a]);
        printf("%d ",hora[a]);
        int a1=hilo[a];
        int a2=total[a];
        int a3=dia[a];
        int a4=hora[a];
        int b=0;
        int c=0;
        printf("\n");    
        //printf(b); 
        //printf(c); 
        //printf(d); 
        if(a3==0){
            if(a4<lunes){
                printf("el hilo %d\n",a1);
                printf("sucede un lunes\n");
                printf("Desde %d\n",24-lunes);
                lunes=lunes-a4;
                printf("a %d\n",24-lunes);
                if(lunes<0){
                    b=lunes*-1;
                    lunes=0;
                    martes=martes-b;
                }
            }
        }
        if(a3==1){
            if(a4<martes){
                printf("el hilo %d\n",a1);
                printf("sucede un martes\n");
                printf("Desde %d\n",24-martes);
                martes=martes-a4;
                printf("a %d\n",24-martes);
                if(martes<0){
                    b=martes*-1;
                    martes=0;
                    miercoles=miercoles-b;
                }
            }
        }
        if(a3==2){
            if(a4<miercoles){
                printf("el hilo %d\n",a1);
                printf("sucede un miercoles\n");
                printf("Desde %d\n",24-miercoles);
                miercoles=miercoles-a4;
                printf("a %d\n",24-miercoles);
                if(miercoles<0){
                    b=miercoles*-1;
                    miercoles=0;
                    jueves=jueves-b;
                }
            }
        }
        if(a3==3){
            if(a4<jueves){
                printf("el hilo %d\n",a1);
                printf("sucede un jueves\n");
                printf("Desde %d\n",24-jueves);
                jueves=jueves-a4;
                printf("a %d\n",24-jueves);
                if(jueves<0){
                    b=jueves*-1;
                    viernes=0;
                    viernes=viernes-b;
                }
            }
        }
        if(a3==4){
            if(a4<viernes){
                printf("el hilo %d\n",a1);
                printf("sucede un viernes\n");
                printf("Desde %d\n",24-viernes);
                viernes=viernes-a4;
                printf("a %d\n",24-viernes);
                if(viernes<0){
                    b=viernes*-1;
                    viernes=0;
                    sabado=sabado-b;
                }
            }
        }
        if(a3==5){
            if(a4<sabado){
                printf("el hilo %d\n",a1);
                printf("sucede un sabado\n");
                printf("Desde %d\n",24-sabado);
                sabado=sabado-a4;
                printf("a %d\n",24-sabado);
                if(lunes<0){
                    b=sabado*-1;
                    sabado=0;
                    domingo=domingo-b;
                }
            }
        }
        if(a3==6){
            if(a4<domingo){
                
                printf("el hilo %d\n",a1);
                printf("sucede un domingo\n");
                printf("Desde %d\n",24-domingo);
                domingo=domingo-a4;
                printf("a %d\n",24-domingo);
                if(domingo<0){
                    b=domingo*-1;
                    domingo=0;
                
                }
            }
        }
        //printf("%d ",lunes);
        //printf("%d ",martes);
        //printf("%d ",miercoles);
        //printf("%d ",jueves);
        //printf("%d ",viernes);
        //printf("%d ",sabado);
        //printf("%d ",domingo);
        printf("\n");

    pthread_mutex_unlock(&mutex);

}





int main(int argc, char* argv[]) {
    //int k[10]={0,1,2,3,4,5,6,7,8,9};
    //int hilo[10]= {1,2,3,4,5,6,7,8,9,10};
    //int total[10]={6,1,7,8,2,4,8,1,6,9};
    //int dia[10]=  {1,4,2,3,5,6,1,2,3,4};
    //int hora[10]={12,2,4,8,16,22,7,9,21,7};
    
    int dias[7]={0,1,2,3,4,5,6};
   
    int horas1[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas2[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas3[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas4[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas5[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas6[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int horas7[24]={0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};



    int n = sizeof(dia) / sizeof(dia[0]);
    printf("Original array: \n");
    printArray(dia, n);
 
    selectionSort(dia,hilo,total,hora, n);
    printf("\nOrdenado por dias array: \n");
    printArray(hilo, n);
    printArray(total, n);
    printArray(dia, n);
    printArray(hora, n);
    pthread_t th[8];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 10; i++) {
        int* a = malloc(sizeof(int));
        //int* b = malloc(sizeof(int));
        //int* c = malloc(sizeof(int));
        //int* d = malloc(sizeof(int));
        *a=i;

        //*b=hilo[i];
        //*c=hilo[i];
        //*d=hilo[i];
        if (pthread_create(&th[i], NULL, &schedulling,a) != 0) {
            perror("Failed to create thread");
            return 1;
        }

        //printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        //printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);

    return 0;

}
