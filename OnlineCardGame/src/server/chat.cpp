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
#include <pthread.h>
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

void* nasluchuj(void* args)
{
	struct client_t* c = static_cast<struct client_t*>(args);
	std::cout<<"nasluchuj : "<<c->socket<<std::endl;
	char bufor[1024];
	if(( recv( c->socket, bufor, sizeof(bufor), 0 ) ) <= 0 )
        {
        	perror( "Blad recv\n" );
        	exit( - 1 );
        }
	printf("widz %s wyslal wiadomosc %s\n",c->nick,bufor);
}

/*glowna funkcja obslugujaca chat*/
void* chat(void* args)
{
	std::vector<struct client_t*>* chatList = static_cast<std::vector<struct client_t*>*>(args);
	std::cout<<"chat : "<<chatList[0]->socket<<std::endl;
	for(int i = 0 ; i < chatList->size() ; i++)
	{
		pthread_t watek;
		if(pthread_create(&watek,NULL,nasluchuj,&chatList[i]))
			printf("blad przy tworzeniu watku\n");
	}
}
