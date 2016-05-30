/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu po rozgrywce od strony gracza.
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

/*funkcja ktora nasluchuje komunikatow od serwera ktory przekazuje komunikaty od innych
uzytkownikow korzystajacych z czatu*/
void nasluchuj(int sock, bool &czyKoniec)
{
	char bufor[1024];
	while(!czyKoniec)
	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		if(std::string("exit").compare(bufor) == 0)
		{
			czyKoniec = true;
		}
		else
			printf("Czat: %s\n",bufor);
	}
}

/*funkcja umozliwiajaca wyslanie wiadomosci do innych czatujacych poprzez
serwer. jezeli uzytkownik wysle "exit" to wraca do mozliwosci wyboru
co chce robic*/
void czatuj(int &sock)
{
	bool czyKoniec = false;
	std::thread t(nasluchuj,sock,std::ref(czyKoniec));
	printf("Co chcesz napisac? (jezeli chcesz wrocic do menu wyboru wpisz 'exit')\n");
	while(!czyKoniec)
	{	
		std::string s;
		std::getline(std::cin,s);
		write(sock,s.c_str(),s.length());
		if(s.compare("exit") == 0)
			break;
	}
	t.join();
}

void displayGame(int &sock) {
char bufor[999999];
	while(true)
	{
		bzero(bufor,sizeof(bufor));
		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		printf("%s\n", bufor);
		break;

}

czatuj(sock);
}

void sendFileChoiceToServer(int &sock, std::string s) {
if(std::string("2").compare(s) == 0) {
char bufor[99999];
	while(true)
	{
		bzero(bufor,sizeof(bufor));
		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		printf("%s\n", bufor);
		break;

}
}
std::string str;
	std::getline(std::cin, str);
write(sock,str.c_str(),str.length());

displayGame(sock);
}

/*funkcja umozliwiajaca graczowi co chce robic. korzystac z czatu, komentowac historyczne rozgrywki
czy zakonczyc sesje. wysyla swoj komunikat do serwera*/
void wybor(int &sock)
{
	printf("wybierz co chcesz robic\n");
	printf("1. czat\n");
	printf("2. komentowanie historycznych rozgrywek\n");
	printf("3. zakoncz\n");
	std::string s;
	std::getline(std::cin,s);
	write(sock,s.c_str(),s.length());

	sendFileChoiceToServer(sock, s);
}

/*funkcja ktora odbiera komunikaty od serwera i w zelznosci od tego co otrzyma
umozliwia uzytkownikowi rozne funkcje jak wybor co chce dalej robic czy 
korzystanie z czatu*/
void czatKomentowanieHistorycznych(int &sock)
{
	char bufor[1024];
	bool czyKoniecGry = false;
	while(!czyKoniecGry)
  	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		if(std::string("wybor").compare(bufor) == 0)
		{
			wybor(sock);
		}
		else if(std::string("czatuj").compare(bufor) == 0)
		{
			czatuj(sock);
		}
		else if(std::string("koniec").compare(bufor) == 0)
		{
			czyKoniecGry = true;
		}
	}
}

