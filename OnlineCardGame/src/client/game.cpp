/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi gry od strony gracza.
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

void game(int &sock)
{
	char bufor[1024];
	while(1)
  	{
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
  		printf( "Server: %s \n", bufor );
		if (strcmp(bufor,"test"))
		{
			printf("TESTUJE WYSYLANIE STRINGA\n");
		}
		else if (strcmp(bufor,"wykonaj ruch"))
		{
			printf("Twoja kolej aby wykonac ruch\n");
			//pokaz karty jakie sa na stole i jakie ma na rece gracz
			//tutaj dodac write z odpowiedzia jaki chce wykonac ruch
		}
		else if (strcmp(bufor,"bledny ruch"))
		{
			printf("Ruch ktory chcesz wykonac jest niepoprawny. Wykonaj inny\n");
			//pokaz karty jakie sa na stole i jakie ma na rece gracz
			//tutaj dodac write z odpowiedzia jaki chce wykonac ruch
		}
		else if (strcmp(bufor,"inny gracz wykonal ruch"))
		{
			printf("Gracz wykonal ruch\n");//dodac jaki to gracz
			//pokaz karty jakie sa na stole
		}
  	}
}

