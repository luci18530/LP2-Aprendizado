#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define QTD_THREADS 26

char string[8] = "AAAAAAAA";
FILE *textogerado;

/* (Questão 1 - 4 pontos) Faça um programa em C/C++ que crie um arquivo de texto de
 um dicionário contendo todas as strings com 8 caracteres alfabéticos maiúsculos
 (de "AAAAAAAA" a "ZZZZZZZZ"). Cada letra do alfabeto (de A a Z) deverá ter sua
 parte do dicionário gerada por uma thread individual, de tal forma que esta
 thread gere todas as strings iniciadas por aquela letra (ex. a thread que gerará 
as strings começando com a letra 'C' gerará as strings de "CAAAAAAA" a
 "CZZZZZZZ"). O programa deverá gerar um arquivo de texto contendo o dicionário
 inteiro ou o dicionário dividido em vários arquivos de texto (um para cada letra). */

 void *funcao_thread()
{
    textogerado = fopen("textogerado.txt", "a");
     
    for (int i = 0; i < QTD_THREADS; i++) {
        
        printf("%s\n", string);
        fputs(string, textogerado);
        fputs("\n", textogerado);
        
        string[1] = string[1] + 1;
        string[2] = string[2] + 1;
        string[3] = string[3] + 1;
        string[4] = string[4] + 1;
        string[5] = string[5] + 1;
        string[6] = string[6] + 1;
        string[7] = string[7] + 1;
        
    }


    
    string[0] = string[0] + 1;
    string[1] = 65;
    string[2] = 65;
    string[3] = 65;
    string[4] = 65;
    string[5] = 65;
    string[6] = 65;
    string[7] = 65;

    fclose(textogerado);
}

 int main () {
    pthread_t threads[QTD_THREADS];
    
    

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, NULL);
        usleep(20000);
    }

    
    return 0;
 }