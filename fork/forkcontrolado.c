// Gera 3 forks
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(void)
{
    int forkreturn;
    char c;
    printf("Mensagem antes do fork\n\n");
    printf("Aperte qualquer tecla: ");
    scanf("%c", &c);
    forkreturn =  fork();

    /*
        fork_return > 0 (execucao do processo pai)
        fork_return == 0 (execucao do processo clonado)
        fork_return == -1 (erro, nao houve clonagem)
    */

    if (forkreturn >0)
    {
        /*processo original*/
        fork();

    }

   printf("----------\n");
   printf("Finalizado\n");
   printf("----------\n");
   
}