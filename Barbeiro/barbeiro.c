#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CADEIRAS 3

#define TRUE 1


sem_t cliente, barbeiros, mutex;

int num_Clientes = 0;

void* barbeiro(void* arg);
void* clientes(void* arg);

int main(int argc, char* argv[])
{
 sem_init(&cliente, 1, 0);
 sem_init(&barbeiros, 1, 0);
 sem_init(&mutex, 1, 1);

 pthread_t teste, teste2;

 pthread_create(&teste, NULL,(void*) barbeiro, NULL);




 while(1)
 {
  pthread_create(&teste2, NULL, (void*) clientes, NULL);
  sleep(1);
 }

 return 0;
}

void* barbeiro(void* arg)
{
 while(1)
 {
 sem_wait(&cliente);
 sem_wait(&mutex);
 num_Clientes= num_Clientes -1;
 sem_post(&barbeiros);
 sem_post(&mutex);
 printf("Barbeiro cortou o cabelo\n");
 }
  pthread_exit(NULL);
}

void* clientes(void* arg)
{
 sem_wait(&mutex);
 if(num_Clientes < NUM_CADEIRAS)
 {
  printf("Cliente foi atendido\n");
  num_Clientes++;
  sem_post(&cliente);
  sem_post(&mutex);
  sem_post(&barbeiros);
  printf("Cliente teve cabelo cortado\n");
 }else{
  sem_post(&mutex);
  printf("Cliente nao cortou o cabelo\n");
 }
 pthread_exit(NULL);
}

