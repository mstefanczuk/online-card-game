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
#include <cstring>
#include <string>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

/*glowna funkcja obslugujaca gre. Rozdaje Karty miedzy graczy,
wysyla im komunikat ze gra sie rozpoczela i w petli obsluguje ruchy
kolejnych graczy*/
int game(std::vector<struct client_t*> clientList, int iloscGraczy)
{
	std::vector<karta> wszystkieKarty = stworzVectorWszystkichKart();
	int kogoJestTura;
	clientList = rozlosujKarty(clientList,wszystkieKarty,kogoJestTura);
	for(int i=0;i<clientList.size();++i)
		wyslij(clientList[i],"Rozpoczynamy gre");
	sleep(1);
	for(int i=0;i<clientList.size();++i)
	{
		std::string s = zamienKartyGraczaNaString(clientList[i]);
		wyslij(clientList[i], s);
	}
	sleep(1);
	std::vector<karta> stosKart;
	while(czyKoniecGry(clientList))
	{
		kogoJestTura = ruchGracza(kogoJestTura,clientList,stosKart);
	}
	printf("KONIEC GRY\n");
}

/*funkcja pomocnicza zamieniajaca typ karty podany jako liczba na string*/
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
/*funkcja pomocnicza zamieniajaca numer karty podany jako liczba na string*/
std::string numerKarty(int i)
{
	switch(i)
	{
		case 0:
			return "9";
		case 1:
			return "10";
		case 2: 
			return "J";
		case 3:
			return "D";
		case 4: 
			return "K";
		case 5:
			return "A";
	}
}

/*funkcja pomocniacza sluzaca do wyslania wiadomosci od serwera do gracza*/
void wyslij(struct client_t* c,std::string wiadomosc)
{
	write(c->socket,wiadomosc.c_str(),wiadomosc.length());
}

/*funkcja sprawdzajaca czy gra sie skonczyla. Gra sie kocnzy jak zostanie tylko
jeden gracz z kartami*/
bool czyKoniecGry(std::vector<struct client_t*> clientList)
{
	if(clientList.size() == 1)
	{
		return false;
	}
	return true;
}

/*funkcja sprawdzajaca czy ruch ktory chce wykonac gracz jest dozwolony.
Ruch nie jest dozwolony kiedy karta która chce polozyc gracz na stosie
jest mniejsza od tej ktora jest na gorze stosu.*/
bool sprawdzCzyRuchDozwolony(struct client_t* c,int ktoraKarta,std::vector<karta> stosKart)
{
	if(c->kartyGracza.size() == ktoraKarta && (!stosKart.empty()))//gracz wybral pobranie kart ze stosu
	{
		printf("mozna wykonac ruch bo gracz chce pobrac karty\n");
		return true;	
	}	
	if(stosKart.empty())//nic nie ma na stosie kart wiec mozemy wrzucic jakakolwiek
	{
		printf("mozna polozyc kazda karte bo stos pusty\n");
		return true;
	}	
	if(stosKart[stosKart.size()-1].porownajKarty(c->kartyGracza[ktoraKarta]))//sprawdamy czy karta ktora lezy na stosie jest "mniejsza" niz ta ktora chcemy polozyc
	{
		printf("mozna wykonac ruch bo karta jest mniejsza");
		return true;
	}
	else
		return false;
}

/*funkcja obslugujaca wykonanie ruchu przez gracza. Pobiera od niego ktora karte chce zagrac i
obsluguje to polecenie w zaleznosci od tego co lezy na stosie kart itp.*/
int ruchGracza(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart)
{
	//pokazanie graczowi jakie ma karty
	std::string s = zamienKartyGraczaNaString(clientList[numerGracza]);
	wyslij(clientList[numerGracza], s);
	sleep(1);
	wyslij(clientList[numerGracza], "wykonaj ruch");
	sleep(1);
	char b[1024];
	bzero(b,sizeof(b));
	if(( recv( clientList[numerGracza]->socket, b, sizeof( b ), 0 ) ) <= 0 )
  	{
   		perror( "Blad recv\n" );
    		exit( - 1 );
  	}
	printf("klient %d : %s\n",numerGracza,b);
	int numerKartyGracza;
	printf("b[16] = %d\n",b[16]);
	if(b[16] != '0' || b[16] != '1' || b[16] != '2' || b[16] != '3' || b[16] != '4' || b[16] != '5' || b[16] != '6' || b[16] != '7' || b[16] != '8' || b[16] != '9')
	{
		numerKartyGracza = b[15] - '0';	
	}
	else
	{
		numerKartyGracza = b[16] - '0' + (b[15] - '0')*10;
	}
	std::cout<<"b[15] = "<<b[15]<<" b[16] = "<<b[16]<<" nkg = "<<numerKartyGracza<<std::endl;
	if(sprawdzCzyRuchDozwolony(clientList[numerGracza],numerKartyGracza,stosKart))
	{
		printf("ruch dozwolony\n");
		if(numerKartyGracza == clientList[numerGracza]->kartyGracza.size())//pobranie kart ze stosu
		{
			int ileKartPobrac;
			if(stosKart.size() > 3)
			{
				ileKartPobrac = 3;	
			}
			else
			{
				ileKartPobrac = stosKart.size()-1;
			}
			printf("pobierane sa karty : \n");
			for(int i = 0 ; i < ileKartPobrac ; i++)
			{
				clientList[numerGracza]->kartyGracza.push_back(stosKart[stosKart.size()-1]);
				stosKart.pop_back();
				std::cout<<stosKart[stosKart.size()-1].getNumer()+" "+stosKart[stosKart.size()-1].getTyp()<<std::endl;
			}
			if (numerGracza < clientList.size()-1)
				return numerGracza+1;
			else
				return 0;
			
		}
		else//polozenie karty
		{
			std::cout<<"numer karty ktora gracz chce polozyc : "<<numerKartyGracza<<std::endl;
			std::cout<<"na stos jest polozona karta "+clientList[numerGracza]->kartyGracza[numerKartyGracza].getNumer() + " " + clientList[numerGracza]->kartyGracza[numerKartyGracza].getTyp()<<std::endl;
			stosKart.push_back(clientList[numerGracza]->kartyGracza[numerKartyGracza]);
			clientList[numerGracza]->kartyGracza.erase(clientList[numerGracza]->kartyGracza.begin()+numerKartyGracza);
			if(clientList[numerGracza]->kartyGracza.size() == 0)
			{
				printf("gracz %d skonczyl gre\n",numerGracza);
				clientList.erase(clientList.begin()+numerGracza);
			}
			if(stosKart[stosKart.size()-1].getTyp() != "PIK")
			{
				printf("kolejka idzie dalej\n");
				if (numerGracza < clientList.size()-1)
					return numerGracza+1;
				else
					return 0;
			}
			else
			{
				printf("polozony PIK wiec cofam\n");
				if (numerGracza != 0)
					return numerGracza-1;
				else
					return clientList.size()-1;
			}
		}
		char numer[20];
		sprintf(numer,"gracz %d wykonal ruch",numerGracza);
		for(int i = 0 ; i < clientList.size() ; i++)
		{
			if(i!= numerGracza)
				wyslij(clientList[i],std::string(numer));
		}
	}
	else
	{
		printf("ruch NIE dozwolony\n");
		wyslij(clientList[numerGracza],"ruch nie dozwolony");
		return numerGracza;
	}
}

/*funkcja ktora zamienia wszystkie karty gracza na ciag znakow*/
std::string zamienKartyGraczaNaString(struct client_t* c)
{
	std::string s = "\n";
	for(int i = 0 ; i < c->kartyGracza.size() ; i++)
	{
		char numer[2];
		sprintf(numer,"%d",i);
		s = s + numer + "." + c->kartyGracza[i].getNumer() + " " + c->kartyGracza[i].getTyp() + "\n";
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
/*funkcja ktora rozlosowuje karty pomiedzy graczy oraz wyznacza ktory
gracz ma rozpoczac rozgrywke*/
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty, int &numerGraczaKtoryRozpoczyna)
{
	srand(time(NULL));
	bool czyWiemyKtoZaczyna = false;
	for(int i = 0 ; 0 < wszystkieKarty.size(); i++)
	{
		if (i%clientList.size() == 0)
			i = 0;
		int losowa = rand() % wszystkieKarty.size();
		clientList.at(i)->kartyGracza.push_back(karta(wszystkieKarty.at(losowa).getTyp(),wszystkieKarty.at(losowa).getNumer()));
		if(!czyWiemyKtoZaczyna)
		{
			if(wszystkieKarty.at(losowa).getTyp() == "KIER" && wszystkieKarty.at(losowa).getNumer() == "9")
			{
				printf("bedzie rozpoczynal gracz %d\n",i+1);
				numerGraczaKtoryRozpoczyna = i;
				czyWiemyKtoZaczyna = true;
			}
		}
		std::vector<karta>::iterator it;
		it = wszystkieKarty.begin();
		it += losowa;
		wszystkieKarty.erase(it);
	}
	return clientList;
}
