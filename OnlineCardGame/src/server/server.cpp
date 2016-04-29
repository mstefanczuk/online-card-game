/**
 * Autor: Kamil Zieliński
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "connection.h"

int main(int argc, char **argv)
{
    int socket, http_socket;
    int getC;
    pthread_t http_thread;
    char haslo[200];
    printf("Podaj haslo zabezpieczajace serwer: ");
    scanf("%99[^\n]",haslo);
    getC=getchar();
    //tworzenie socketu
    printf("\t\t\t!!!!!!!!!Uruchamiam Serwer!!!!!!!!!!!");
    socket = create_connection();
    //funkcja nasluchujaca
    listen_connections(socket,haslo);
}
