#include "Handlers_Serv.h"

void hand_reveil (int sig){
    printf("\n*********************** Signal numéro %d reçu **********************\n",sig);
    printf("\t\t     Le Client a lu la réponse \n");
    printf("\n********************************************************************\n");
}

void fin_serveur (int sig){
    printf("\n************************ Signal numéro %d reçu **********************\n",sig);
    printf("\t\t\t   Fin du Serveur \n");
    printf("********************************************************************\n");
    unlink(f1);
    unlink(f2);
    exit(2);
}