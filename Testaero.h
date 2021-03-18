#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



//--------------------------- PROTOTYPES -------------------------------

void insertRetard(char *num_retard,char *type_retard,char *duree,_Bool annulation);
void insertAnomalies(char *num_retard,char *type_retard,char *duree,_Bool annulation,char *num_anomalies,char *type_anomalies,char *numero_vol);
void insertDonneeMeteo(char *num_retard,char *type_retard,char *duree,_Bool annulation,char *zone,char *intemperies,int vitesse_vent,char *numero_vol);
void modifTempsVolDepArr(char *numero_vol);
void modifTempsVolArr(char *numero_vol);
char* recupVol(char *buf);