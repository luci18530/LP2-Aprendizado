#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define QTD_THREADS 5

typedef struct pedaco {
    int index;
    char type;
    int datachunk;
} pedaco;

void *processaestrutura(void *param){
    pedaco *meupedaco;
    meupedaco = (pedaco*) param;
    long processed;
    printf("[%d] type: %c\n", meupedaco->index, meupedaco->type);
    printf("[%d] data chunk: %d\n", meupedaco->index, meupedaco->datachunk);
    printf("[%d] processing...\n", meupedaco->index);
    processed = meupedaco->datachunk * meupedaco->datachunk;
    sleep(rand() % 10 + meupedaco->index);
    printf("[%d] processed data chunk = %ld\n", meupedaco->index,
           processed);
    pthread_exit((void *)processed);       
}



int main (void) {
    time_t t;
    pedaco imagem[QTD_THREADS];
    pthread_t threads[QTD_THREADS];
    int result[QTD_THREADS];
    srand((unsigned)time(&t));

    for (int i = 0; i < QTD_THREADS; i++)
    {
        imagem[i].index = i + 1;
        imagem[i].type = 65 + i;
        imagem[i].datachunk = rand() % 255;
    }
    
    for (int i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, processaestrutura, (void *)&imagem[i]);
        usleep(50000);
    }

    for (int i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(threads[i], (void *)&result[i]);
        printf("[main] resultado recebido da thread %ld: %d\n",
               i, result[i]);
    }

    

    return 0;
}