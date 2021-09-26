
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define QTDTHREAD 10
double globalvariable = 0;

void *functionthread(void *param){
    long id = (long)param; // recupera o valor passado

    if (id%2 == 0){
        for (int i = 0; i < 10; i++)
        {
            globalvariable++;
        }
        
    }

    else {
        for (int i = 0; i < 10; i++)
        {
            globalvariable--;
        }
    }

    printf("Thread [%d] | Variavel Global: %lf\n", id, globalvariable);

}

int main(){
    pthread_t threads[QTDTHREAD];
    printf("Variavel Global: %lf\n", globalvariable);



    for (long i = 0; i < QTDTHREAD; i++) {
        pthread_create(&threads[i], NULL, functionthread, (void*)i);
        sleep(1);
    }

    printf("------------------\nValor Final da Variavel Global: %lf\n", globalvariable);

}

