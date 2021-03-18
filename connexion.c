


/* connexion à la base de données et insertion d'une valeur dans la table retard*/
void insertRetard(char *numero_retard,char *type_retard,char *duree,_Bool annulation){
	char query[255];
	PGconn *conn = PQconnectdb("host=10.40.128.23 user=y2019l3i_dromano password=A123456* dbname=db2019l3i_dromano port=5432");//connexion
	sprintf(query,"INSERT INTO Retard VALUES('%s','%s','%s','%d');",numero_retard,type_retard,duree,annulation);//preparation de la requete
	PGresult *res = PQexec(conn, query); //envoie de la requete et reception de celle ci
	PQclear(res);
	PQfinish(conn);

}
/* modification d'une de la table vol en récuperant un retard 
et le vol en cours.*/
void modifTempsVolArr(char *numero_vol){
		char query[255];
	char *horaire,*arrivee,*heure,*heure1,*minutes,*minutes1,*duree = "";
	int h,h1,h2,m,m1,m2,hf,mf,hf1,mf1 ;
	char hfin [255];
	char hfin1 [255];
	PGconn *conn = PQconnectdb("host=10.40.128.23 user=y2019l3i_dromano password=A123456* dbname=db2019l3i_dromano port=5432");//connexion à la base de données
	sprintf(query,"SELECT horaire_d_arrivee,duree FROM vol NATURAL JOIN retard WHERE numero_vol='%s';",numero_vol);//preparation de la requete
	PGresult *res = PQexec(conn, query); // envoie de la requete et reception de celle ci
	int rows = PQntuples(res); //traitement de la réponse si on affiche horaire et duree on obtient le résultat de la requete
	for (int i = 0; i < rows; i++){
		horaire = PQgetvalue(res,i,0);
		duree = PQgetvalue(res,i,1) ;
	}

	sprintf(horaire,"%s:%s",horaire,duree);
	char * t = strtok(horaire,":"); //traitement pour séparer les reponses de la requete
	heure=t;
	h=atoi(heure);
	t=strtok (NULL,":");

	minutes=t;
	m=atoi(minutes);
	t=strtok (NULL,":");


	t=strtok (NULL,":");
	heure1=t;
	h1=atoi(heure1);

	t=strtok (NULL,":");
	minutes1=t;
	m1=atoi(minutes1);

	t=strtok (NULL,":");

	hf=h+h1;
	mf=m+m1;
	if (mf>=60){
		mf=mf-60;
		hf=hf+1;
	}

	sprintf(hfin,"%d:%d:00",hf,mf);
	sprintf(query,"UPDATE vol SET horaire_d_arrivee='%s' WHERE numero_vol='%s';",hfin,numero_vol); // preparation de la requete update
	PGresult *res1 = PQexec(conn, query); // envoie de la requete et reception de celle ci

	PQclear(res);
	PQclear(res1);
	PQfinish(conn);
}
