/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu i komentwoania historycznych rozgrywek od strony serwera.
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
#include "karta.h"
#include <iostream>
#include <time.h>
#include <cstring>
#include <pthread.h>
#include <string>
#include <thread>
#include "game.h"
#include <dirent.h>
#include "log.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream> 

std::vector<std::string> listOfFiles;

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

std::string vectorToString(std::vector<std::string> vector) {
   std::string string;
   
   for(int i =0; i<vector.size(); i++) {
	string = string + std::to_string(i) + ". " + vector[i] + "\n";
   }
	return string;
}

std::vector<std::string> listFiles(const char* path)
{
   std::vector<std::string> files;
   DIR* dirFile = opendir( path );
   if ( dirFile ) 
   {
      struct dirent* hFile;
      errno = 0;
      for (int i = 0; ( hFile = readdir( dirFile )) != NULL; i++) 
      {
         if ( !strcmp( hFile->d_name, "."  )) continue;
         if ( !strcmp( hFile->d_name, ".." )) continue;

         // in linux hidden files all start with '.'
         if ( hFile->d_name[0] == '.' ) continue;

         // dirFile.name is the name of the file. Do whatever string comparison 
         // you want here. Something like:
         if ( strstr( hFile->d_name, ".log" ))
            files.push_back(hFile->d_name);
      } 
      closedir( dirFile );
   }
listOfFiles = files;
   return files;
}

/*funkcja obslugujaca czat miedzy klientami*/
void chatowanie(struct client_t* client,std::vector<struct client_t*> &chatList)
{
	chatList.push_back(client);
	bool czyCzatuje = true;
	write(client->socket,"czatuj",6);
	while(czyCzatuje)
	{
		char bufor[1024];
		bzero(bufor,sizeof(bufor));
  		if(( recv( client->socket, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   			printAndWriteLog("Serwer", "Blad recv\n");
    			exit( - 1 );
  		}
		printAndWriteLog(client->nick, bufor);
		if(std::string("exit").compare(bufor) == 0)//uzytkownik zakonczyl uzywanie czatu
		{
			czyCzatuje = false;
			write(client->socket,"exit",4);
		}
		else//przeslanie wiadomosci do pozostalych osob korzystajacych z czatu
		{
			for(int i = 0 ; i < chatList.size() ; i++)
			{
				if(chatList[i] != client)
				{
					char b[1024];
					strcpy(b,"[Klient : ");
					strcat(b,client->nick);
					strcat(b," ]");
					strcat(b,bufor);
					write(chatList[i]->socket,b,sizeof(b));
				}
			}
		}
	}
	for(int i = 0 ; i < chatList.size() ; i++)
	{
		if(chatList[i] == client)
		{
			chatList.erase(chatList.begin() + i);
			break;
		}
	}
}

void sendFileContentToClient(struct client_t* client) {
char bufor[99999];
	while(1)
	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( client->socket, bufor, sizeof(bufor), 0 ) ) <= 0 )
  		{
   			printAndWriteLog("Serwer", "Blad recv\n");
    			exit( - 1 );
  		}
break;

}
std::string fileName = listOfFiles[atoi(bufor)];
std::ifstream t(fileName);
std::stringstream buffer;
buffer << t.rdbuf();
write(client->socket, buffer.str().c_str(), buffer.str().length());
}

/*funkcja obslugujaca klienta. Umozliwia wybor czynnosci jaka chce wykonac klient.*/
void obslugaPojedynczego(std::vector<struct client_t*> &clientList,struct client_t* client,std::vector<struct client_t*> &chatList)
{
	write(client->socket,"wybor",5);
	char bufor[1024];
	while(1)
	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( client->socket, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   			printAndWriteLog("Serwer", "Blad recv\n");
    			exit( - 1 );
  		}
		printAndWriteLog(client->nick, bufor);
		if(std::string("1").compare(bufor) == 0)//chce czatowac
		{
			chatowanie(client,chatList);
			sleep(1);
			write(client->socket,"wybor",5);
		}
		else if(std::string("2").compare(bufor) == 0)//chce komentowac
		{
			std::string message = vectorToString(listFiles("./"));
			printAndWriteLogString("Serwer", message);
			write(client->socket, message.c_str(), message.length());

			sendFileContentToClient(client);
		}
		else if(std::string("3").compare(bufor) == 0)//chce zakonczyc
		{
			write(client->socket,"koniec",6);
			for(int i = 0 ; i < clientList.size() ; i++)
			{
				if(clientList[i] == client)
				{
					clientList.erase(clientList.begin() + i);
					break;
				}
			}
			break;
		}
	}
}

/*funkcja ktora tworzy watek dla kazdego klienta aby mogl byc obsluzony.*/
void czatKomentowanieHistorycznych(std::vector<struct client_t*> clientList)
{
	std::thread t[clientList.size()];
	int siz = clientList.size();
	std::vector<struct client_t*> chatList;
	for(int i = 0 ; i < clientList.size() ; i++)
	{
		t[i] = std::thread(obslugaPojedynczego,std::ref(clientList),clientList[i],std::ref(chatList));
	}
	for(int i = 0 ; i < siz ; i++)
	{
		t[i].join();
		printAndWriteLog("Serwer", "Watek zakonczyl dzialanie");
	}
}
