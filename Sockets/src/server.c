#include "serv_cli.h"

int main(int argc, char const* argv[])
{
    int server_fd, valread,i;
    struct sockaddr_in serverAddr;  	/* Server socket address structures */
    struct sockaddr_in cliAddr;  /* Client socket address structures */
    struct reponse r;      /* Reponse du serveur */
    struct question q;     /*Question du client */
    int clientSocket;       // Client socket id
    socklen_t addr_size;   	// Stores byte size of server socket address
    pid_t childpid;  // Child process id
	int s_pid=getpid();


    // Creates a TCP socket id from IPV4 family
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Error handling if socket id is not valid
	if (server_fd < 0) {
		printf("Error in connection.\n");
		exit(1);
	}

	//printf("Server Socket is created.\n");

	// Initializing address structure with NULL
	memset(&serverAddr, '\0', sizeof(serverAddr));

	// Assign port number and IP address to the socket created
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Binding the socket id with the socket structure
	if (bind(server_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {    	// Error handling
		printf("Error in binding.\n");
		exit(1);
	}

	// Listening for connections (upto 10)
	if (listen(server_fd, 10) == 0) {
		printf("Listening...\n\n");
	}

	int cnt = 0;
	while (1) {

		// Accept clients and store their information in cliAddr
		clientSocket = accept( server_fd, (struct sockaddr*)&cliAddr, &addr_size);

		// Error handling
		if (clientSocket < 0) {
			exit(1);
		}

		// Displaying information of connected client
		printf("Connection accepted from %s:%d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

		// Print number of clients connected till now
		printf("Clients connected: %d\n\n", ++cnt);

		// Creates a child process
		if ((childpid = fork()) == 0) {

			// Closing the server socket id
			close(server_fd);

	    	/* initialisation du générateur de nombres aléatoires*/
	    	srand(getpid());

	    	valread = read(clientSocket, &q, sizeof(q));

			/* Affichage du Question envoyé par le client */
			printf("\n****************** Question du Client numéro %d *****************\n",q.pidc);
			printf("\t      Veuillez me générer %d nombres aléatoires \n",q.quest);
			
			/* Construction de la réponse */
			r.pidserveur=s_pid;
			for(i=0;i<q.quest;i++){
			r.rep[i] = rand() % (NMAX - 1) + 1;
			}

			send(clientSocket, &r, sizeof(r), 0);
		
			close(clientSocket);  			// Close the client socket id

	    		}
		}

	    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}