/**
 * Autor: Mateusz Skolimowski
 */
#ifndef KARTA_H
#define KARTA_H

enum typKarty {PIK = 0,TREFL = 1, KARO = 2, KIER = 3};
enum numerKarty {DZIEWIATKA = 0, DZIESIATKA = 1, WALET = 2, DAMA = 3, KROL = 4, AS = 5};
class karta
{
	private:
	typKarty typ;
	numerKarty numer;
	public:
	karta(typKarty t, numerKarty n);
	bool porownajKarty(karta k);
	typKarty getTyp();
	numerKarty getNumer();
};

#endif
