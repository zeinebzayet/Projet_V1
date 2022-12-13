#include <stdio.h>

void hand_reveil (int sig){
    printf("\n************************** Signal numéro %d reçu ****************************\n",sig);
    puts("\t\t    +--------------------------------+");
    printf("\t\t    | Le Serveur a écrit la réponse  |\n");
    puts("\t\t    +--------------------------------+");
}