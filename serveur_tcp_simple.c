#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "Testaero.c"


/* Procédure Main qui est le coeur du programme il va lancer le serveur attendre une connexion
*  d'un client puis échanger avec lui et en fonction des messages du client il va modifier ou
*  non la base de données
*/
void main (int argc,char *argv[]) {
	char buf [80] ;								//
	char zone[80];								//
	int m=1;									//
	char mm[5];									//	initialisation
	char *t="";									//
	int al=1,i=0,port;							//
	long it=80;									// 
	int s_ecoute, s_dial, cli_len ;				//
	struct sockaddr_in serv_addr, cli_addr ;	//
	

	port = atoi(argv[1]);						// récupération et transformation de l'entrée courante en int

	serv_addr.sin_family = AF_INET ;
	if (strncmp(argv[2],"127.0.0.1",strlen("127.0.0.1")))
	{
		printf("erreur d'ip\n");
		exit(0);
	}
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]) ;
	if(port!=5000 && port != 6000){
		printf("port deja utilisé probleme\n");
		exit(0);
	} // adresse ip du serveur
	serv_addr.sin_port = htons (port) ;				// sur quel port attendre la connexion
	memset (&serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));


	s_ecoute = socket (PF_INET, SOCK_STREAM, 0) ;		
	bind (s_ecoute, (struct sockaddr *)&serv_addr, sizeof serv_addr) ;

	listen (s_ecoute, 5) ;			//le serveur attends une connexion
	cli_len = 79 ;
	s_dial = accept (s_ecoute, (struct sockaddr *)&cli_addr, &cli_len) ;	// le serveur l'accepte
	printf ("Le client d'adresse IP %s s'est connecté depuis son port %d\n", \
	            inet_ntoa (cli_addr.sin_addr), ntohs (cli_addr.sin_port)) ;



	while(1){	

				memset (buf, 0, 80);		//on vide le buffer
				//read (s_dial, buf, 80); // on écrit le message du client sur le buf
				sprintf(mm,"%d",m);	


			if (read (s_dial, buf, 80)){
				printf ("J'ai reçu [%s] du client\n", buf) ;
				if (strlen(buf)==80){													// si le message est trop long on sort	
					i++;
				}else{
					i=0;
				}
				if (i==1){																// ici on change la condition pour savoir combien de buffer on va tester 1 pour 80 , 2 pour 160 etc
					printf("Message trop grand arret.\n");
					break;
				}
				if (!strncmp (buf, "trafic ", strlen ("trafic "))) {					// si le message contient le mot trafic
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);														// on récupere le numero de vol du message
					insertAnomalies(mm,"anomalies","00:15:00",0,"1","probleme trafic",t);	// on insert dans la base de données une anomalie sur le numéro de vol récupéré
					modifTempsVolDepArr(t);													// on modifie le temps de départ et arrivée sur le vol concerné
        			strncpy (buf, "Trafic. ",80) ;											// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici trafic
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoyer au client ici le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "casse ", strlen ("casse "))) {							// si le message continet le mot casse
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);														// on récupère le numéro de vol du message
					insertAnomalies(mm,"anomalies","06:00:00",1,"1","probleme moteur",t);	// on insert dans la base de données une anomalie sur le numero de vol récupéré
					modifTempsVolDepArr(t);													// on modifie le temps de départ et d'arrivée
        			strcpy (buf, "Moteur. ") ;												// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici moteur
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoyer au client ici le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "soute ", strlen ("soute "))) {							// si le message continet le mot soute
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);														// on récupère le numéro de vol du message 
					insertAnomalies(mm,"anomalies","01:00:00",0,"1","probleme soute",t);	// on insert dans la base de données une anomalie sur le numero de vol récupéré
					modifTempsVolDepArr(t);													// on modifie le temps de départ et d'arrivée
        			strcpy (buf, "Soute. ") ;												// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici soute
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoyer ici au client le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "neige ", strlen ("neige "))) {							// si le message continet le mot neige
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);
					printf("%s\n",t );														// on récupère le numéro de vol du message
					insertDonneeMeteo("10","meteo","01:15:00",0,"24.4254,18.2548","neige",20,t);			// on insert une donnée météo sur le numero de vol récupéré
					modifTempsVolArr(t);													// on modifie le temps d'arrivée
        			strcpy (buf, "Neige. ") ;												// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici neige
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoyer au client ici le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "brouillard ", strlen ("brouillard "))) {				// si le message continet le mot neige
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);														// on récupère le numéro de vol du message
					insertDonneeMeteo(mm,"meteo","00:30:00",0,zone,"brouillard",20,t);		// on insert une donnée météo sur le numero de vol récupéré
					modifTempsVolArr(t);													// on modifie le temps d'arrivée
        			strcpy (buf, "brouillard. ") ;											// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici brouillard
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoyer au client ici le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "vent ", strlen ("vent "))) {							// si le message continet le mot vent
					printf ("J'ai recu [%s] du client\n", buf) ;
					t=recupVol(buf);														// on récupère le numéro de vol du message
					insertDonneeMeteo(mm,"meteo","00:05:00",0,zone,"vent violent",70,t);	// on insert une donnée météo sur le numero de vol récupéré
					modifTempsVolArr(t);													// on modifie le temps d'arrivée
        			strcpy (buf, "vent. ") ;												// on écrit dans le buf un message de confirmation que le message du client a bien été compris ici vent
					write (s_dial, buf, strlen (buf)) ;										// on ecrit ce que l'on veut envoye au client ici le buf
        			printf ("J'ai envoye [%s] au client\n", buf) ;
					m++;
				}
				if (!strncmp (buf, "quit", strlen ("quit"))) {								// si le message contient quit on ferme la connexion
					break;																				
				}
			
		
        		memset (buf, 0, 80);
        		strcpy (buf, "Message reçu\n") ;					// on ecrit que l'on a bien reçu le message 
        		write (s_dial, buf, strlen (buf)) ;					// on envoie le buf
        		printf ("J'ai envoye [%s] au client\n", buf) ;
        	}else{
        		printf("deconnexion\n");
        		break;
        	}

    		}

		close (s_dial) ;				// on ferme la connexion
		close (s_ecoute) ;

}
