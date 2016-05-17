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
#include <string>

bool czyTenSamString(char *b, std::string b2)
{
	int size;
	if(sizeof(b) <= b2.length())
		size = sizeof(b);
	else
		size = b2.length();
	for(int  i = 0 ; i < size ; i++)
	{
		if(b[i] != b2[i])
			return false;
	}
	return true;
}

void wykonajRuch(int &sock)
{
	printf("Twoja kolej aby wykonac ruch\n");
	int ktoraKarteZagrac;
	getchar();
	printf("jaka karte chcesz zagrac?\n");
	scanf("%d",&ktoraKarteZagrac);
	char buf[16];
	sprintf(buf,"zagrywam karte %d",ktoraKarteZagrac);
	write(sock,buf,17);
	char b[1024];
	bzero(b,sizeof(b));
  	if(( recv( sock, b, sizeof( b ), 0 ) ) <= 0 )
  	{
   	  	perror( "Blad recv\n" );
    		exit( - 1 );
  	}
  	printf("Server: %s \n", b);
	if(czyTenSamString(b,"ruch nie dozwolony"))
	{
		printf("wykonales niedozwolony ruch, sprobuj ponownie\n");
		wykonajRuch(sock);
	}
}

void game(int &sock)
{
	char bufor[1024];
	while(1)
  	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
  		printf("Server: %s \n", bufor );
		if (czyTenSamString(bufor,"test"))
		{
			printf("TESTUJE\n");
		}
		else if (czyTenSamString(bufor,"wykonaj ruch"))
		{
			wykonajRuch(sock);
		}
		else if (czyTenSamString(bufor,"bledny ruch"))
		{
			printf("Ruch ktory chcesz wykonac jest niepoprawny. Wykonaj inny\n");
			//pokaz karty jakie sa na stole i jakie ma na rece gracz
			//tutaj dodac write z odpowiedzia jaki chce wykonac ruch
		}
		else if (czyTenSamString(bufor,"inny gracz wykonal ruch"))
		{
			printf("Gracz wykonal ruch\n");//dodac jaki to gracz
			//pokaz karty jakie sa na stole
		}
  	}
}

