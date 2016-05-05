/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi gry od strony serwera.
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

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty);
std::string zamienKartyGraczaNaString(struct client_t*);
/*funkcja zamieniajaca typ karty podany jako liczba na string*/
std::string typKarty(int j)
{
	switch(j)
	{
		case 0:
			return "PIK";
		case 1:
			return "TREFL";
		case 2: 
			return "KARO";
		case 3:
			return "KIER";
	}
}
/*funkcja zamieniajaca numer karty podany jako liczba na string*/
std::string numerKarty(int i)
{
	switch(i)
	{
		case 0:
			return "DZIEWIATKA";
		case 1:
			return "DZIESIATKA";
		case 2: 
			return "WALET";
		case 3:
			return "DAMA";
		case 4: 
			return "KROL";
		case 5:
			return "AS";
	}
}

/*glowna funkcja obslugujaca gre*/
int game(std::vector<struct client_t*> clientList, int iloscGraczy)
{
	std::vector<karta> wszystkieKarty = stworzVectorWszystkichKart();
	clientList = rozlosujKarty(clientList,wszystkieKarty);
	//while(1)
	//{
        	for(int i=0;i<clientList.size();++i)
			write(clientList[i]->socket, "Rozpoczynamy gre\n",18 );
		sleep(1);
		for(int i=0;i<clientList.size();++i)
		{
			std::string s = zamienKartyGraczaNaString(clientList[i]);
			write(clientList[i]->socket, s.c_str(),s.length() );
		}
		sleep(1);
	//}
}

/*funkcja ktora zamienia wszystkie karty gracza na ciag znakow*/
std::string zamienKartyGraczaNaString(struct client_t* c)
{
	std::string s = "";
	for(int i = 0 ; i < c->kartyGracza.size() ; i++)
	{
		s = s + c->kartyGracza[i].getNumer() + " " + c->kartyGracza[i].getTyp() + "\n";
	}
	return s;
}
/*funkcja ktora tworzy vector wszystkich kart aby mozna bylo je rozlosowac miedzy graczy*/
std::vector<karta> stworzVectorWszystkichKart()
{
	std::vector<karta> v;
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			v.push_back(karta(typKarty(j),numerKarty(i)));
		}
	}
	return v;
}
/*funkcja ktora rozlosowuje karty pomiedzy graczy*/
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty)
{
	srand(time(NULL));
	for(int i = 0 ; 0 < wszystkieKarty.size(); i++)
	{
		if (i%clientList.size() == 0)
			i = 0;
		int losowa = rand() % wszystkieKarty.size();
		clientList.at(i)->kartyGracza.push_back(karta(wszystkieKarty.at(losowa).getTyp(),wszystkieKarty.at(losowa).getNumer()));
		std::vector<karta>::iterator it;
		it = wszystkieKarty.begin();
		it += losowa;
		wszystkieKarty.erase(it);
	}
	return clientList;
}