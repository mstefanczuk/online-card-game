/**
 * Autor: Mateusz Skolimowski
 */
#include "karta.h"
#include <vector>
#include <stdio.h>

/*konstruktor tworzacy obiekt*/
karta::karta(std::string t, std::string n)
{
	this->typ = t;
	this->numer = n;
}

std::string karta::getTyp()
{
	return this->typ;
}

std::string karta::getNumer()
{
	return this->numer;
}

/*funkcja zwracajaca wartosc liczbowa dla danej karty.
Sluzy do okreslenia ktora karta jest "wieksza" np. As
ma wieksza wartosc niz Krol*/
int karta::sprawdzWartosc(std::string s)
{
	std::string wartosciKart[6] = {"9","10","J","D","K","A"};
	for(int i = 0 ; i < sizeof(wartosciKart) ; i ++)
	{
		if(wartosciKart[i] == s)
		{
			return i;
		}
	}
}

/*funkcja porownujaca karty*/
bool karta::porownajKarty(karta k)
{
	if(sprawdzWartosc(this->getNumer()) <= sprawdzWartosc(k.getNumer()))
		return true;
	else
		return false;
}
