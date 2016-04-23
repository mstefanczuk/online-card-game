/**
 * Autor: Kamil Zieliński
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "connection.h"
int MAX_CLIENTS=5;
struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
};
/**
 * Tworzy połączenie korzystając z gniazd BSD
 *
 * @return numer gniazda
 */
int create_connection()
{
    int sock, length;
    struct sockaddr_in6 server;
    sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Blad socketu");
        exit(1);
    }
    server.sin6_family = AF_INET6;
    server.sin6_addr = in6addr_any;
    server.sin6_port = htons(8888);
    if (bind(sock, (struct sockaddr *) &server,sizeof server) == -1)
    {
        perror("Blad bindingu socketu");
        exit(1);
    }

    length = sizeof(server);
    if (getsockname(sock,(struct sockaddr *) &server,
                &length) == -1)
    {
        perror("Blad getsockname");
        exit(1);
    }
    printf("Port: %d\n", ntohs(server.sin6_port));
    return sock;

}

/**
 * Funkcja nasłuchująca i dla każdego klienta włączająca odzielny wątek do obsługi
 */
void listen_connections(int sock)
{
    pthread_t thread;
    listen(sock, MAX_CLIENTS);
    do 
    {
        
    	struct client_t *new_client;
        //alokacja kilenta
    	if ((new_client = calloc(1, sizeof(struct client_t))) == NULL)
    	{
    		perror("Blad alokacji pamieci");
    		exit(1);
    	}
        new_client->socket = accept(sock,(struct sockaddr *) 0,(int *) 0);
	printf("\nlol\n");
        if (new_client->socket == -1 )
        {
            perror("Blad accept");
        }
        else
        {   
    	    printf("Dolacza\n");
   	    //tu bedzie obsługa watek
        }
    } while(1);
}
