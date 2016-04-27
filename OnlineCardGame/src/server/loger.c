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
#include <string.h>
int login(int sock,char haslo[], pthread_mutex_t* mutex,char nick[])
{
               
	    char trybGracza[2];
	    pthread_mutex_unlock(mutex);
            char czyDobreHaslo[2]="0";
            int i=0;
            char haslo2[200];
  	    int temp;  
            if(( recv( sock, nick, 50, 0 ) ) <= 0 )
            {
        		perror( "Blad recv\n" );
        		exit( - 1 );
            }
	    while(i<5 && czyDobreHaslo[0]=='0')
   	    {  
		if(i==4)
		  break;                
		if(( recv( sock, haslo2, 201, 0 ) ) <= 0 )
            	{
        		perror( "Blad recv\n" );
        		exit( - 1 );
            	}
                printf("Uzytkownik %s podal haslo: %s \n",nick,haslo2);
		temp=strcmp(haslo,haslo2);
		if(temp==0)
			czyDobreHaslo[0]='1';
		else	
			czyDobreHaslo[0]='0';
		write(sock,czyDobreHaslo,2);
		++i;
            }
            if(czyDobreHaslo[0]=='1')
 	    {
		
		write(sock, "Witaj, chcesz byc graczem (1) czy moze widzem(2). Wybierz  odpowiedni numer:",81 );
            //tu bedzie obsługa watek
            	if(( recv( sock, trybGracza, 2, 0 ) ) <= 0 )
        	{
        	     perror( "Blad recv\n" );
        	     exit( - 1 );
        	}
        	printf("Tryb gracza: %s\n",trybGracza);
            }
	    else
	    {
		pthread_mutex_unlock(mutex); 		
		return 1;
            }
 	    pthread_mutex_unlock(mutex);
       return 0;
}
