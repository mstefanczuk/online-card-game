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
//#include <boost/thread/thread.hpp>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};


/*glowna funkcja obslugujaca chat*/
void chat(std::vector<struct client_t*> chatList,int numer,bool &czyKoniecGry)
{
	while(1)
	{	
		char b[1024];
		bzero(b,sizeof(b));
		if(( recv( chatList[numer]->socket, b, sizeof( b ), 0 ) ) <= 0 )
  		{
   			perror( "Blad recv\n" );
    			exit( - 1 );
  		}
		printf("[WIDZ %d] : %s\n",numer,b);
		/*for(int i = 0 ; i < chatList.size() ; i++)
		{
			printf("[w%d]chatlist[%d].sock = %d\n",numer,i,chatList[i]->socket);
		}*/
	}
}
