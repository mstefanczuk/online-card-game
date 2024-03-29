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

/*funkcja w ktorej gracz odbiera komunikaty od serwera ktore pochodza od 
innych gracyz korzystajacych z czatu. Ewentualnie otrzymuje komunikat od
samego serwera o zakonczeniu gry*/
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
		std::string s("koniec gry");
		if (s.compare(bufor) == 0)
		{
			printf("napiszcie swoje ostatnie wiadomosci \n");
			czyKoniecGry = true;
		}
	}
}

/*funkcja tworzy watek do odbierania wiadomosci od serwera oraz pozwala na wysylanie
wiadomosci do serwera zeby przeslal je do pozostalych graczy*/
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
	t.join();
}

