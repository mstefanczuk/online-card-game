/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu od strony gracza.
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
#include <time.h>
#include "game.h"
#include <cstring>
#include <string>
#include <iostream>


void chat(int &sock)
{
	std::string s;
	std::getline(std::cin,s);
	while(1)
	{	
		printf("co chcesz napisac do innych?\n");
		std::getline(std::cin,s);
		std::cout<<"wczytany string : "<<s<<std::endl;
		write(sock,s.c_str(),s.length());
	}
}

