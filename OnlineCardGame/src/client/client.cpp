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
struct client_t
{
    int sock;
    pthread_mutex_t* mutex;
    char nick[50];
};
//inicjalizacja mutexu
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char** argv)
{
char pass[200];
char mode[2];

  struct client_t* client = new client_t;
  client->mutex = &mutex;
  //sprawdzanie wczytania poprawnej ilosc agrumentow
  if (argc != 6)
  {
      printf("\nZLA LICZBA ARGUMENTOW.\n");
      exit(1);
  } 
  //WYRZUCONE NA CZAS TESTOW
  //printf("Podaj nick: ");
  //scanf("%50[^\n]",client->nick);
  //getchar();

  strcpy(client->nick, argv[3]);
  strcpy(pass, argv[4]);
  strcpy(mode, argv[5]);

  pthread_t client_thread;
  //polaczenie z serwerem
  //create_connection(argc, argv, client->sock,client->nick);
  create_connection(argc, argv, client->sock,client->nick, pass, mode);
  close(client->sock);
  return 0;
}
