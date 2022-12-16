#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

void main(){

/*Déclarations */
int t1, t2, i, sig;
struct Question q;
struct Reponse rep;

/* Création des tubes nommés */
if( mkfifo (f1, S_IRUSR|S_IWUSR) == -1 || mkfifo (f2, S_IRUSR|S_IWUSR) == -1){
    printf("Erreur de création des tubes\n");
    exit(1);
}

/*initialisation du générateur de nombres aléatoires*/
srand(getpid());

/* Ouverture des tubes nommés */
t1 = open(f1, O_RDWR);
t2 = open(f2, O_WRONLY);

/* Installation des Handlers */
signal(SIGUSR1,hand_reveil);
for(sig=1;sig<=NSIG;sig++){
    if(sig!=10)
        signal(sig,fin_serveur);
}

while(1){

    /* lecture d’une question */
    read(t1,&q,sizeof(q));

    /* Affichage du Question envoyé par le client */
    printf("\n****************** Question du Client numéro %d *****************\n",q.Num);
    printf("\t      Veuillez me générer %d nombres aléatoires \n",q.n);

    
    /* construction de la réponse */
    rep.NumServeur=getpid();
    for(i=0;i<q.n;i++){
        rep.tab[i] = rand() % (NMAX - 1) + 1;
    }

    /* envoi de la réponse */
    write(t2,&rep,sizeof(rep));
    
    /* envoi du signal SIGUSR1 au client concerné */
    sleep(1);
    kill(q.Num,SIGUSR1);

    /* Attente de la terminaison de la lecture de la reponse de la part du client */
    pause();

    }
close(t1);
close(t2);
}
