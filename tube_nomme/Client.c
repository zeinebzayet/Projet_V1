#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

void main(){

/* Déclarations */
int t1, t2, i, nb;
struct Question q;
struct Reponse rep;

/* Ouverture des tubes nommés */
t1 = open(f1, O_WRONLY);
if (t1 == -1) {
    fprintf(stderr, "Impossible d'ouvrir %s , Veuillez lancer le serveur tout d\'abord\n", f1);
    exit(3);
}
t2 = open(f2, O_RDONLY);
if (t2 == -1) {
    fprintf(stderr, "Impossible d'ouvrir le %s , Veuillez lancer le serveur tout d\'abord\n", f2);
    exit(3);
}

/*initialisation du générateur de nombres aléatoires*/
srand(getpid());

/* Installation des Handlers */
signal(SIGUSR1,hand_reveil);

/* Construction et envoi d’une question */
nb=rand() % (NMAX - 1) + 1;
q.Num=getpid();
q.n=nb;
write(t1,&q,sizeof(q));
close(t1);

/* Affichage du Question du client */
printf("\nVoici mon pid: %d, Veuillez me générer %d nombres aléatoires \n",q.Num,q.n);

/* Attente de la réponse */
pause();

/* Lecture de la réponse */
read(t2,&rep,sizeof(rep));
close(t2);

/* Envoi du signal SIGUSR1 au serveur */
sleep(1);
kill(rep.NumServeur,SIGUSR1);

/* Traitement local de la réponse */
printf("\n********************* Réponse du Serveur de pid %d ************************\n\n",rep.NumServeur);
printf("Les %d nombres aléatoires générés : \n ",nb);
for(i=0;i<nb;i++){
printf("%d |",  rep.tab[i]);
}
printf("\n");
}
