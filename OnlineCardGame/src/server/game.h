/**
 * Autor: Mateusz Skolimowski
 */
#ifndef GAME_H
#define GAME_H

#include <string>
#include "karta.h"

int game(std::vector<struct client_t*> clientList, int iloscGraczy,bool &czyKoniecGry);
std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty,int &numerGraczaKtoryRozpoczyna);
std::string zamienKartyNaString(std::vector<karta> karty);
std::string typKarty(int j);
std::string numerKarty(int i);
void wyslij(struct client_t* c,std::string wiadomosc);
bool czyKoniecGry(std::vector<struct client_t*> clientList);
bool sprawdzCzyRuchDozwolony(struct client_t* c,int ktoraKarta,std::vector<karta> stosKart);
int ruchGracza(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart);
int game(std::vector<struct client_t*> clientList, int iloscGraczy);
std::string zamienKartyGraczaNaString(struct client_t* c);
std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty, int &numerGraczaKtoryRozpoczyna);
int pobierzKartyZeStosu(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart);
int polozKarteNaStosie(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart,int numerKartyGracza);
void wyslijWszystkimStanStosu(std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart);

#endif
