/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu od strony serwera.
 * 
 */
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "karta.h"
#include <iostream>
#include <time.h>
#include <cstring>
#include <string>
#include "game.h"

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

/*glowna funkcja obslugujaca chat*/
void* chat(void* args)
{
	std::vector<struct client_t*>* chatList = static_cast<std::vector<struct client_t*>*>(args);
	for(int i = 0 ; i < chatList->size() ; i++)
	{
		printf("chat %d\n",i);
	}
}
