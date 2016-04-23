/**
 * Autor: Kamil Zieliński
 */
#include <sys/socket.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "connectionn.h"

//struktura klienta
struct client_struct 
{
    int sock;
    pthread_mutex_t* mutex;
};
//inicjalizacja mutexu
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char** argv)
{
  int count;
  struct client_struct* structure = new client_struct;
  structure->mutex = &mutex;
  //sprawdzanie wczytania poprawnej ilosc agrumentow
  if (argc != 3)
  {
    if(argc != 4 && atoi(argv[3]) != 1)
    {
      printf("\nZLA LICZBA ARGUMENTOW.\n");
      exit(1);
    }
  
  }  
  pthread_t client_thread;
  //polaczenie z serwerem
  create_connection(argc, argv, structure->sock);
  close(structure->sock);
  return 0;
}
