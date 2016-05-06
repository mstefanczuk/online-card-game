/**
 * Autor: Mateusz Skolimowski
 */
#include "karta.h"
#include <vector>

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

bool karta::porownajKarty(karta k)
{
	if(this->getNumer() > k.getNumer())
		return true;
	else
		return false;
}
