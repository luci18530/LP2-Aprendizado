#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define QTD_THREADS 26 // letras do alfabeto

char string[4] = "AAAA"; // string inicial
FILE *textogerado; // arquivo

 void *funcao_thread()
{
    textogerado = fopen("textogerado.txt", "a"); // abrir aquivo
     
    for (int i = 0; i < QTD_THREADS; i++) {
        
        printf("%s\n", string);
        fputs(string, textogerado); // escreve a string no arquivo
        fputs("\n", textogerado); // pula a linha
        
        string[1] = string[1] + 1; // muda a letra
        string[2] = string[2] + 1;
        string[3] = string[3] + 1;
        
        
    }


    
    string[0] = string[0] + 1; // muda para proxima letra
    string[1] = 65; // ajusta a letra para A 
    string[2] = 65; // ajusta a letra para A 
    string[3] = 65; // ajusta a letra para A 


    fclose(textogerado); // fecha arquivo
}

 int main () {
    
    pthread_t threads[QTD_THREADS];
    
    

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, NULL); // cria as threads
        usleep(50000); // para evitar conflitos / inconsistencias de memora / resultados inespereados
    }

    
    return 0;
 }