/**
 * Autor: Mateusz Skolimowski
 */
#include "karta.h"
#include <vector>

karta::karta(typKarty t, numerKarty n)
{
	this->typ = t;
	this->numer = n;
}

enum typKarty karta::getTyp()
{
	return this->typ;
}

enum numerKarty karta::getNumer()
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
