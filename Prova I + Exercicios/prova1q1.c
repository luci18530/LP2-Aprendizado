// luciano pereira de oliveira filho - 20190018530
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
int win = 0; // variavel de vitoria

typedef struct lebres{
    int id; // identificador
    double salto_max; // aleatorio (vamos supor que seja entre 10 a 20)
    float pecorrido; // distancia pecorrida
    int distancia; // distancia da corrida 
} lebres;


// threads
void *corridathread(void *lebre){

    struct lebres *lebre_t = lebre; // novo tipo lebres que recebe os parametros da lebrecorrda[i]
    printf("Oi sou a lebre[%d]\n",lebre_t->id); // apresentação
    win = 0;
    float salto; // variavel salto

    lebre_t ->pecorrido = 0.0;

    // enquanto a distancia pecorrida pelo lebre for menor que a distancia da corrida...
    while(lebre_t -> pecorrido < lebre_t -> distancia){

        salto = ( (float)rand( ) / (float) RAND_MAX * lebre_t ->salto_max); // valor aleatorio entre 0 e salto_max
        lebre_t -> pecorrido += salto; // somatorio dos valores pecorridos
        usleep(10000); // usleep para reduzir a probabilidade de eventos indesejados 

        if (win == 1) {
            break; // se houve vitoria, sair
        }

        // se ainda nao houve vitoria, apresentar dados da corrida
        else {
            printf("[Lebre %d] Saltou %.2f cm e Percorreu %.2f cm\n", lebre_t->id, salto, lebre_t->pecorrido);
        }

        

        // vamos dormir um pouco
        sleep(1);

        // se a distancia pecorrida pelo lebre for maior que a distancia da corrida & ainda não houve vitoria
        // entao temos um vitorioso, e a variavel vitoria muda pra 1, e a thread sai
        if (lebre_t ->pecorrido >= lebre_t -> distancia && win == 0){
            printf("\n\nLebre %d ganhou a corrida! A distancia era de : %d cm\n\n", lebre_t->id, lebre_t ->distancia);
            win = 1;
            pthread_exit(NULL);
            break;
        }
       
    }
    
}

void corridaprocesso(int pidpai, lebres lebresp) {
    printf("Novo processo\n");
    float salto;
    int winp = 0; //variavel de vitoria

    struct lebres lebre_p = lebresp;
    printf("Oi sou a lebre [%d]\n",lebre_p.id);
    lebre_p.pecorrido = 0.0;

// se a distancia pecorrida pelo lebre for menor que a distancia da corrida & não houve vitoria...
    while(lebre_p.pecorrido < lebre_p.distancia && winp != 1){

        salto = ( (float)rand( ) / (float) RAND_MAX * lebre_p.salto_max); // salto com valor aleatorio
        lebre_p.pecorrido += salto;
        usleep(10000); // usleep para evitar prints indesejados

        // em caso de vitoria, sair
        if (winp == 1) {
            break;
        }

        // apresentação dos dados da corrida
        else {
            printf("[Lebre %d] Saltou %.2f cm e Percorreu %.2f cm\n", lebre_p.id, salto, lebre_p.pecorrido);
        }

        sleep(1);

        // se distancia pecorrida pelo lebre for maior que a distancia da corrida & não houve vitoria, matar os processos filhos
        if (lebre_p.pecorrido >= lebre_p.distancia && winp == 0){
            printf("\n\nLebre %d ganhou a corrida! A distancia era de : %d cm\n\n", lebre_p.id, lebre_p.distancia);
            kill(0, SIGKILL);
            break;
            
            
        }
       
    }


    // se o PID nao for igual a pidpai, encerra o processo
    if(getpid() != pidpai)
        exit(0);
}



int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL)); // randomizador
    char *definidor = argv[1]; // definidor se é processo ou thread, recebe o primeiro argumento após o nome do executavel
    char *instanciasarg = argv[2]; // instancias a serem executadas, recebe o segundo argumento após o nome do executavel  
    char *distanciaarg = argv[3]; // distancia da corrida, recebe o terceiro argumento após o nome do executavel

    int instancias = atoi(instanciasarg); // converte a string da quantidade de instancias para inteiro
    int distancia = atoi(distanciaarg); // converte a distancia para inteiro

    struct lebres lebrecorrida[instancias]; // criação do tipo lebres em um array com tamanho das instancias

    // condiçional em relação definidor
    if (definidor[0] == '-' && definidor[1] == 't'){
        printf("THREADS!\n"); 
        pthread_t lebres[instancias];
        
        // aplicação de valores para cada elemento do array de structs, recebendo um indentificador, salto maximo, dist pecorrida e a distancia da corrida
        for (long i = 0; i < instancias; i++){
            lebrecorrida[i].id = i;
            lebrecorrida[i].salto_max = ( (float)rand( ) / (float) RAND_MAX * 10) + 10; // valor aleatorio entre 10 e 20
            lebrecorrida[i].pecorrido = 0.0;
            lebrecorrida[i].distancia = distancia;
            
            pthread_create(&lebres[i], NULL, &corridathread, (void *)&lebrecorrida[i]); // cria a thread recebendo como parametro a struct de uma posição de array
            //usleep(10000);
            
        }

        for(int i = 0; i < instancias; i++){
        
        pthread_join(lebres[i], NULL); // junta as threads
    }

    }

    // processos
    else if (definidor[0] == '-' && definidor[1] == 'p'){
        printf("PROCESSOS!\n");
        int pidpai;
        pidpai = getpid(); // pid do pai
        int fork_return;
        int status;
        

        for (int i = 0; i < instancias; i++){

        if(getpid()==pidpai){
            // processo pai
            // atribuindo valores padrão aos lebres
            lebrecorrida[i].id = i;
            lebrecorrida[i].salto_max = ( (float)rand( ) / (float) RAND_MAX * 10) + 10; // valor aleatorio entre 10 e 20
            lebrecorrida[i].pecorrido = 0.0;
            lebrecorrida[i].distancia = distancia;

            printf("Criando processo %i\n", i);
            
            fork_return = fork(); // clona processo

            if (fork_return == 0){
                // processo filho
                 corridaprocesso(pidpai,lebrecorrida[i]);
                }
                
            }

        else {
            // se por ventura um filho chegar aqui, ele sai do loop
            break;
        }
        
    }

    }

    
    return 0;
}

