/**
 * Autor: Mateusz Skolimowski
 *
 * klasa definiujaca wlasciowsci kart ktore beda uzywane w grze.
 */
#ifndef KARTA_H
#define KARTA_H

#include <iostream>

class karta
{
	private:
	std::string typ;
	std::string numer;
	public:
	karta(std::string t, std::string n);
	bool porownajKarty(karta k);
	std::string getTyp();
	std::string getNumer();
};

#endif
