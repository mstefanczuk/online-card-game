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


/*glowna funkcja obslugujaca chat. nasluchuje komunikatow od widzow i przesyla je 
do pozostalych. Konczy swoje dzialanie kiedy gra sie skonczy.*/
void chat(std::vector<struct client_t*> chatList,int numer,bool &czyKoniecGry)
{
	while(!czyKoniecGry)
	{	
		char b[1024];
		bzero(b,sizeof(b));
		if(( recv( chatList[numer]->socket, b, sizeof( b ), 0 ) ) <= 0 )
  		{
   			perror( "Blad recv\n" );
    			exit( - 1 );
  		}
		std::string s = std::string("[WIDZ") + std::to_string(numer) + std::string("] : ")+b;
		std::cout<<s<<std::endl;
		for(int i = 0 ; i < chatList.size() ; i++)
		{
			if(i != numer)
				write(chatList[i]->socket,s.c_str(),s.length());
		}
	}
}
