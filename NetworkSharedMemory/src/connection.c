#include "../include/connection.h"
#include <pthread.h>

pthread_t slave_co[MAX_SLAVE];
SOCKET client[MAX_SLAVE];
int nb_co=0;

SOCKET connection(int port,const char *addr)
{
	/*	Création de la socket	*/
	printf("---------------/Demande de connexion /------------------------\n");
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    exit(errno);
	}
	printf("connection :: Socket crée\n");
	/*	Connection au serveur	*/
	SOCKADDR_IN sin = { 0 }; 
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_port = htons(port); 
	sin.sin_family = AF_INET;
	printf("connection :: envoie de la demande\n");
	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
	    perror("connect()");
	    exit(errno);
	}
	printf("connexion :: connexion établie\n");
	printf("---------------/Fin Demande de connexion /--------------------\n");
	return sock;
}

void deconnection(SOCKET sock)
{
	/*On signale au serveur que l'on va se déconnecté*/
	
	/* On ferme le flux*/
	close(sock);
}


void *slave_action(int * acc){

	printf(" >>>  >>> Thread is running\n");
	char *dec = "mllpzo";
	int i=0;
	while(rcv_msg(*acc) != NULL)
	{
		printf("***********/ REQUEST %d\n",i);
		i++;
	}
	printf(" >>>  >>> Thread is ending\n");
	close(*acc);
	free(acc);
}

/*boucle infini qui traite les connections au serveur*/
void valider_connexion(int port)
{
	printf("---------------/Accept d'une connexion /----------------------\n");
	/*	Creation de la socket	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    exit(errno);
	}
	/*	Fournir un nom à une socket/Création de l'interface 	*/
	SOCKADDR_IN sin = { 0 };
	sin.sin_addr.s_addr = htonl(INADDR_ANY); 
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
	    perror("bind()");
	    exit(errno);
	}
	/*	on attend une connexion	*/
	if(listen(sock, 1) == SOCKET_ERROR)
	{
	    perror("listen()");
	    exit(errno);
	}

	socklen_t fromlen = sizeof(sin);

	SOCKET_ACCEPT *acc;

	while(1){
		acc = (int *)malloc(sizeof(int));
		/*	On accept la connection	*/
		if((*acc = accept(sock, (struct sockaddr *)&sin, &fromlen)) == -1){
			perror("accept");
			exit(1);
		}
		/*	On associe un thread a chaque client connecter	*/
		pthread_create(&slave_co[nb_co], NULL,slave_action, acc);
		nb_co ++;
		printf("---------------/ Connexion Accepter %d/--------------------------\n",nb_co);
	}


}










