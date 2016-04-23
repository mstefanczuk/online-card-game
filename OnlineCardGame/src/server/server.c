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
    pthread_t http_thread;
    //tworzenie socketu
    printf("\t\t\t!!!!!!!!!Uruchamiam Serwer!!!!!!!!!!!");
    socket = create_connection();
    //funkcja nasluchujaca
    listen_connections(socket);
}
