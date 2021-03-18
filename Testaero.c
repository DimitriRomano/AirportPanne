#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "Testaero.h"

// Compilation gcc Testaero.c -I /usr/include/postgresql -L /usr/include/postgresql/ -lpq -o Testaero

 
// --------------------------------  Méthode d'ajout de Valeur ----------------------------------


/* programmes de traitement de la base de données coté serveur avec des fonctions d'ajouts de 
   valeurs dans la base de données suite à la discussion avec le client.

   Connexion à la db de la fac : host=10.40.128.23 user=y2019l3i_dromano password=A123456* 
   dbname=db2019l3i_dromano port=5432.

*/

// ---------------------------------------- IMPLEMENTATION -------------------------------------

/* Procédure insertRetard qui va se connecter à la base de donnee rajouter une valeur dans la table
   retard avec les instructions passées en paramètres.

*  @param : numero_retard : le numero de retard qui sera incrementer dans le main 
			type_retard   : le type de retard possible une anomalies ou météo
			duree		  : la durée du retard en format hh:mm:ss
			annulation	  : booleen qui va nous dire si l'avion est annulé ou non
*
*/

void insertRetard(char *numero_retard,char *type_retard,char *duree,_Bool annulation){
	char query[255];																											//initialisation
	PGconn *conn = PQconnectdb("user=adaoust password=balckdeau dbname=dbadaoust"); //connexion à la bd
	sprintf(query,"INSERT INTO Retard VALUES('%s','%s','%s','%d');",numero_retard,type_retard,duree,annulation);				//preparation de la requete
	PGresult *res = PQexec(conn, query); 																						//execution de la requete et stockage du résultat.
	PQclear(res);																												//on efface le résultat
	PQfinish(conn);																												// arret de la connexion à la bd

}
/* Procédure insertAnomalies qui va se connecter à la base de donnee rajouter une valeur dans 
la table Anomalies avec les instructions passées en paramètres.
   
*  @param : numero_retard : char qui sera incrementer dans le main 
			type_retard   : char qui est tout le temps anomalies ici
			duree		  : char qui est la durée du retard en format hh:mm:ss
			annulation	  : booleen qui va nous dire si l'avion est annulé ou non
			num_anomalies : char qui sera incrementer dans le main 
			type_anomalies: char qui nous donne le type d'anomalies
			numero_vol	  : char qui est donnée par le client pour le numero de vol concerné
*
*/

void insertAnomalies(char *num_retard,char *type_retard,char *duree,_Bool annulation,char *numero_anomalies,char *type_anomalies,char *numero_vol){
	char query[255];																																					//initialisation
	PGconn *conn = PQconnectdb("user=adaoust password=balckdeau dbname=dbadaoust");											//connexion à la bd														
	sprintf(query,"INSERT INTO anomalies VALUES('%s','%s','%s','%d','%s','%s','%s');",num_retard,type_retard,duree,annulation,numero_vol,numero_anomalies,type_anomalies); //preparation de la requete
	PGresult *res = PQexec(conn, query);																																//exécution de la requete et stockage du résultat
	PQclear(res);																																						//on efface le résultat
	PQfinish(conn);																																						//arret de la connexion à la bd

}
/* Procédure insertDonneeMeteo qui va se connecter à la base de donnee rajouter une valeur dans 
la table donnee_meteo avec les instructions passées en paramètres.
   
*  @param : numero_retard : char qui sera incrementer dans le main 
			type_retard   : char qui est tout le temps anomalies ici
			duree		  : char qui est la durée du retard en format hh:mm:ss
			annulation	  : booleen qui va nous dire si l'avion est annulé ou non
			zone		  : char qui représente la zone concernée 
			intemperies   : char qui représente le type d'intemperies(brouillard,neige...) 
			vitesse_vent  : integer qui donne la vitesse du vent
			numero_vol	  : char qui est donnée par le client pour le numero de vol concerné
*
*/
void insertDonneeMeteo(char *num_retard,char *type_retard,char *duree,_Bool annulation,char *zone,char *intemperies,int vitesse_vent,char *numero_vol){
	char query[255];																																								//initialisation
	PGconn *conn = PQconnectdb("user=adaoust password=balckdeau dbname=dbadaoust");														//connexion à la bd
	sprintf(query,"INSERT INTO donnee_meteo VALUES('%s','%s','%s','%d','%s','%s','%s','%d');",num_retard,type_retard,duree,annulation,numero_vol,zone,intemperies,vitesse_vent);	//preparation de la requete
	PGresult *res = PQexec(conn, query);																																			// exécution de la requete et stockage du résultat
	PQclear(res);																																									//on efface le résultat
	PQfinish(conn);																																									//arret de la connexion à la bd

}
/* Procédure modifTempsVolArr qui va se connecter à la base de donnee récuperer les valeurs 
horaire_arrive et retard si il y a un retard sur l'avion dans les tables vol et retard
avec le numero de vol passées en paramètres.En récuperant les valeurs heures minutes de chaque valeur
et calcul de la nouvel heure apres ajout du retard 
   
*  @param :  numero_vol	  : char qui est donnée par le client pour le numero de vol concerné
*
*/
void modifTempsVolArr(char *numero_vol){
		char query[255];														//
	char *horaire,*arrivee,*heure,*heure1,*minutes,*minutes1,*duree = "";		// 
	int h,h1,h2,m,m1,m2,hf,mf,hf1,mf1 ;											// Initialisation 
	char hfin [255];															//
	char hfin1 [255];		
	printf("init\n");												//
	PGconn *conn = PQconnectdb("user=adaoust password=balckdeau dbname=dbadaoust"); 
	printf("ok");// connexion à la bd
	sprintf(query,"SELECT horaire_arrive,duree FROM vol NATURAL JOIN retard WHERE numero_vol='%s';",numero_vol);				// preparation de la requete
	PGresult *res = PQexec(conn, query);			//execution de la requete et stockage du résultat
	int rows = PQntuples(res);						//
	for (int i = 0; i < rows; i++){					//
		horaire = PQgetvalue(res,i,0);				// récupération des valeurs					
		duree = PQgetvalue(res,i,1) ;				//
	}												//

	sprintf(horaire,"%s:%s",horaire,duree);   // concaténation de l'horaire d'arrivée et du retard 
	char * t = strtok(horaire,":");			  // séparation de horaire avec : comme délimiteur
	heure=t;								  // récupération de l'heure d'arrivée
	h=atoi(heure);							  // conversion en integer
	t=strtok (NULL,":");					  // passage au suivant

	minutes=t;								  // meme opération sur les minutes de l'horaire d'arrivée
	m=atoi(minutes);
	t=strtok (NULL,":");


	t=strtok (NULL,":");					  // meme opération sur les heures du retard
	heure1=t;
	h1=atoi(heure1);

	t=strtok (NULL,":");					  // meme opération sur les minutes du retard
	minutes1=t;
	m1=atoi(minutes1);

	t=strtok (NULL,":");

	hf=h+h1;								  // calcul de l'heure final
	mf=m+m1;								  // calcul des minutes final
	if (mf>=60){							  // passage en heure si jamais minutes>60
		mf=mf-60;
		hf=hf+1;
	}

	sprintf(hfin,"%d:%d:00",hf,mf);			  // écriture de l'horaire final
	sprintf(query,"UPDATE vol SET horaire_arrive='%s' WHERE numero_vol='%s';",hfin,numero_vol);  //préparation de la requete de modification
	PGresult *res1 = PQexec(conn, query);	//execution de la requete et stockage de la réponse

	PQclear(res);		//on vide les résultats et on se déconnecte
	PQclear(res1);
	PQfinish(conn);
}

/* Procédure modifTempsVolDepArr qui va se connecter à la base de donnee récuperer les valeurs 
horaire_depart, horaire_arrive et retard si il y a un retard sur l'avion dans les tables vol et retard
avec le numero de vol passées en paramètres. En récuperant les valeurs heures minutes de chaque valeur
et calcul de la nouvel heure apres ajout du retard 
   
*  @param :  numero_vol	  : char qui est donnée par le client pour le numero de vol concerné
*
*/
void modifTempsVolDepArr(char *numero_vol){
	char query[255];																			//
	char *horaire,*arrivee,*heure,*heure1,*minutes,*minutes1,*heure2,*minutes2,*duree = "";     //
	int h,h1,h2,m,m1,m2,hf,mf,hf1,mf1 ;															// Initialisation
	char hfin [255];																			//
	char hfin1 [255];																			//
	PGconn *conn = PQconnectdb("user=adaoust password=balckdeau dbname=dbadaoust"); //connexion à la base de données
	sprintf(query,"SELECT horaire_depart,duree,horaire_arrive FROM vol NATURAL JOIN retard WHERE numero_vol='%s';",numero_vol); //préparation de la requete
	PGresult *res = PQexec(conn, query);		//execution de la requete et stockage du résultat
	int rows = PQntuples(res);					//
	for (int i = 0; i < rows; i++){				// Affichage des données
		horaire = PQgetvalue(res,i,0);			// horaire depart
		duree = PQgetvalue(res,i,1) ;			// duree retard
		arrivee= PQgetvalue(res,i,2);			// horaire arrivee
	}

	sprintf(horaire,"%s:%s:%s",horaire,duree,arrivee); // concaténation des chaines de caractères
	char * t = strtok(horaire,":"); 	//sépration de horaire avec comme délimiteur :
	heure=t;							// récuperation de l'heure de départ
	h=atoi(heure);						// conversion en integer
	t=strtok (NULL,":");				// passage au suivant

	minutes=t;							// de meme pour minutes de départ
	m=atoi(minutes);
	t=strtok (NULL,":");


	t=strtok (NULL,":");				// de meme pour heure du retard
	heure1=t;
	h1=atoi(heure1);

	t=strtok (NULL,":");				// de meme pour minutes de retard
	minutes1=t;
	m1=atoi(minutes1);

	t=strtok (NULL,":");
	t=strtok (NULL,":");
	heure2=t;						    // de meme pour heure d'arrivee
	h2=atoi(heure2);
	t=strtok (NULL,":");
	minutes2=t;							// de meme pour minutes d'arrivee
	m2=atoi(minutes2);


	hf=h+h1;							// calcul de la nouvelle heure de départ
	mf=m+m1;							// calcul des nouvelles minutes de départ
	if (mf>=60){						// si minutes > 60 +1h
		mf=mf-60;
		hf=hf+1;
	}

	sprintf(hfin,"%d:%d:00",hf,mf);		// écriture de la nouvelle horaire de départ

	hf1=h2+h1;							// calcul de la nouvelle horaire d'arrivee
	mf1=m2+m1;							// calcul des nouvelle minutes d'arrivee
		if (mf1>=60){					// si minutes>60 h+1
		mf1=mf1-60;
		hf1=hf1+1;
	}
	sprintf(hfin1,"%d:%d:00",hf1,mf1);	// ecriture de la nouvelle horaire d'arrivee

	sprintf(query,"UPDATE vol SET horaire_depart='%s',horaire_arrive='%s' WHERE numero_vol='%s';",hfin,hfin1,numero_vol); // preparation de la requete update
	PGresult *res1 = PQexec(conn, query); // execution de la requete et stockage du résultat

	PQclear(res);		//vidage des résultats des requetes et déconnexion
	PQclear(res1);
	PQfinish(conn);
}
/* Fonction recupVol qui va récuperer le numero de vol à partir de la commande entrée par le client 
   
*  @param :  buf  : char qui est le message du client
*
*/

char* recupVol(char *buf){
	char *t="";	 
	t=strtok(buf," "); 	// récupération de la premiere partie du message 
	t=strtok(NULL,"\n");	// récupération du numero de vol 
	return t ;				// renvoie le numero de vol
}