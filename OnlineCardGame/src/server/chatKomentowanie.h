/**
 * Autor: Mateusz Skolimowski
 */
#ifndef CHATKOMENTOWANIE_H
#define CHATKOMENTOWANIE_H

void chatowanie(struct client_t* client,std::vector<struct client_t*> &chatList);
void obslugaPojedynczego(std::vector<struct client_t*> &clientList,struct client_t* client,std::vector<struct client_t*> &chatList);
void czatKomentowanieHistorycznych(std::vector<struct client_t*> clientList);
#endif
