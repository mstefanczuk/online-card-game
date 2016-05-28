/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu od strony gracza.
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
#include <time.h>
#include "game.h"
#include <cstring>
#include <string>
#include <iostream>
#include <thread>

void odbieranieWiadomosciOdInnychGraczy(int sock, bool &czyKoniecGry)
{
	char bufor[1024];
	while(!czyKoniecGry)
  	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
  		printf("Server: %s \n", bufor );
		if (czyTenSamString(bufor,"koniec gry"))
		{
			printf("TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
			czyKoniecGry = true;
		}
	}
}


void chat(int &sock)
{
	std::string s;
	bool czyKoniecGry = false;
	std::thread t(odbieranieWiadomosciOdInnychGraczy,sock,std::ref(czyKoniecGry));
	while(!czyKoniecGry)
	{	
		std::getline(std::cin,s);
		write(sock,s.c_str(),s.length());
	}
}

