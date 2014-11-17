#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define CADEIRAS 10
using namespace std;

void barbeiro2(void* arg);


    sem_t cliente;
    sem_t barbeiro;
    sem_t mutex;
    int espera = 0;
    pthread_t teste;


int main()
{



    cout << "Hello world!" << endl;
    return 0;
}

void* Barbearia(void* args){
     while(TRUE)
      sem_wait(&cliente);
      sem_wait(&mutex);
      espera--;
      sem_post(&barbeiro);// entrando na area de risco
      sem_post(&mutex);
      cout << "O cabelo foi cortado";
    }

void* Clientes(void* args)    {
   sem_wait(&mutex);
   if(espera < CADEIRAS){
    espera++;
    sem_post(&cliente); // Acordar o barbeiro
    sem_post(&mutex);


   }else{
     cout << "Barbearia cheia. Cliente saiu\n"  ;
   }
   sem_post(&mutex);
}
