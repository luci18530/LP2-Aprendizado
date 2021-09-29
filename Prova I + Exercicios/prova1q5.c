#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#define QTD_THREADS 12
double varglob = 0;


 void *funcao_thread(void *param)
{
   long id = (long)param;


   if (id % 3 == 0) { // se for divisivel por 3
       for (long i = 0; i <= 100; i++)
       {
           printf("THREAD [%d] Variável Global : %lf\n", id, varglob);
           varglob++;
           sleep((rand() % 2) + 1);
       }

       
       
   }

   else { // se nãp for divisivel por 3
            for (long i = 0; i <= 33; i++){
            printf("THREAD [%d] Variável Global : %lf\n", id, varglob);
            varglob--;
            sleep(1);
       }
       }

       pthread_exit(NULL); // sai
}

 int main () {
    pthread_t threads[QTD_THREADS];
    double random;
    double retornorandom;
    int fork_return;
    srand((unsigned int)time(NULL));
    varglob = ( (double)rand( ) / (double) RAND_MAX * 60) + 20;
    printf("Valor randomico dado a Variável Global : %lf\n", varglob);

    // não foi possivel usar processos para receber um valor aleatorio pois o retorno de um processo filho só pode ser um valor inteiro, sendo que a variavel global é double

    //fork_return = fork();

    //if (fork_return == 0){
    //    // clonado
    //    varglob = ( (double)rand( ) / (double) RAND_MAX * 60) + 20;
    //    printf("Valor randomico dado a Variável Global : %lf\n", varglob);
    //    exit(0);
    //    
    //}

    //else {
        // original
        //wait(&retornorandom);
        //varglob = (double WEXITSTATUS(retornorandom));
        //printf("Valor randomico dado a Variável Global : %lf\n", varglob);
    //}

    
    

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, (void *)i);
        //usleep(100000);
        
    }

    for (int i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nO valor final da Variavel Global é : %lf\n", varglob);



    
    return 0;
 }