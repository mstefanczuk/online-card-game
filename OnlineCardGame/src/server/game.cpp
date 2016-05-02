/**
 * Autor: Mateusz Skolimowski
 */
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
};

int game(std::vector<struct client_t*> clientList)
{
	while(1)
	{
        	for(int i=0;i<clientList.size();++i)
			write(clientList[i]->socket, "Rozpoczynamy gre\n",18 );
		sleep(1);
		for(int i=0;i<clientList.size();++i)
			write(clientList[i]->socket, "TEST\n",5 );
		sleep(1);
	}
}
