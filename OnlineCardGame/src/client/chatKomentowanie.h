/**
 * Autor: Mateusz Skolimowski
 */
#ifndef CHATKOMENTOWANIE_H
#define CHATKOMENTOWANIE_H

#include <string>

void wybor(int &sock);
void czatKomentowanieHistorycznych(int &sock);
void czatuj(int &sock);
void nasluchuj(int sock, bool &czyKoniec);

#endif
