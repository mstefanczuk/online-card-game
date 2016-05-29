/**
 * Autor: Mateusz Skolimowski
 */
#ifndef CHAT_H
#define CHAT_H

#include <string>

void odbieranieWiadomosciOdInnychGraczy(int sock, bool &czyKoniecGry);
void chat(int &sock);

#endif
