#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(void)
{
   pid_t filho;
   int i, status;
   int count = 5;

   filho = fork();


   if (filho == 0)
   {
       printf("Sou o processo filho, meu pid é %i\n", getpid());

       for (i = 0; i <= count; i++)
       {
           printf("%i\n", i);
           sleep(1);
       }
       
       _exit(0);
   }

   else {
       wait(filho, &status, 0);
       printf("Sou o processo pai, meu pid é %i\n", getpid());
   }

   sleep(3);
   printf("----------\n");
   printf("Finalizado\n");
   printf("----------\n");
   
}