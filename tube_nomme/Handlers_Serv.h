#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void hand_reveil (int sig){
    printf("\n*********************** Signal numéro %d reçu **********************\n",sig);
    puts("\t\t    +---------------------------+");
    printf("\t\t    | Le Client a lu la réponse |\n");
    puts("\t\t    +---------------------------+");
    printf("\n********************************************************************\n");
}

void fin_serveur (int sig){
    printf("\n************************ Signal numéro %d reçu **********************\n",sig);
    puts("\t\t\t  +----------------+");
    printf("\t\t\t  | Fin du Serveur |\n");
    puts("\t\t\t  +----------------+");
    printf("********************************************************************\n");
    unlink(f1);
    unlink(f2);
    exit(2);
}