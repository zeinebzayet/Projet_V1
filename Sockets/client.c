#include "serv_cli.h"
 
int main(int argc, char const* argv[])
{
    int sock = 0, valread, nb,i;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cliAddr;   /* Client socket structure */
    struct question q;
    struct reponse r;
    int clientSocket;  	// Socket id

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);  	// Creating socket id

	if (clientSocket < 0) {
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

	// Initializing socket structure with NULL
	memset(&cliAddr, '\0', sizeof(cliAddr));

	// Assigning port number and IP address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(clientSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)   // connect() to connect to the server
	{
		printf("Error in connection.\n");
		exit(1);
	}

	printf("Connected to Server.\n");

    /* initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    /* Construction et envoi d’une question */
    nb=rand() % (NMAX - 1) + 1;
    q.pidc=getpid();
    q.quest=nb;

    send(clientSocket, &q, sizeof(q), 0);
    printf("Message sent\n");

    valread = read(clientSocket, &r, sizeof(r));
    /* Traitement local de la réponse */
    printf("\n********************* Réponse du Serveur numéro %d ************************\n\n",r.pidserveur);
    printf("Les %d nombres aléatoires générés : \n\n ",nb);
    for(i=0;i<nb;i++)
    {
        printf("%d  ",r.rep[i]);
    }
    printf("\n");

    close(clientSocket);  /* closing the connected socket */
    return 0;
}
