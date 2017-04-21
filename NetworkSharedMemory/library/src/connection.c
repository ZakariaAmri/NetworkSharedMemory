#include "connection.h"
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

void deconnection(int *sock)
{
	/*On signale au serveur que l'on va se déconnecté*/
	
	/* On ferme le flux*/

	printf("SOCK %d\n",sock[1]);
	slave_co[sock[1]]=-1;
	nb_co--;

	close(*sock);
	free(sock);
}


void *slave_action(int * acc){
	/*
	printf(" >>>  >>> Thread is running\n");

	FILE* fichier = NULL;

	char namefile[1024];
	sprintf(namefile,"%d",acc[1]);
	strcat(namefile,".txt");
	printf("FICHIER %s cree\n",namefile);
	fichier = fopen(namefile, "w+");
	if(fichier == NULL){
		printf("FICHIERR %d",fichier);
	}

	fputs("0",fichier);

	fseek(fichier, 0, SEEK_SET);
	
	char c[1024];
	int val;
	*/
	char dec[1024] = "mllpzo";
	while(recevoir_msg(*acc) != NULL)
	{
		/*
		fgets(c,1024,fichier);
		printf("LU %s\n",c);
		fseek(fichier, 0, SEEK_SET);
		val = atoi(c);
		val++;
		sprintf(c,"%d",val);
		fputs(c,fichier);
		fseek(fichier, 0, SEEK_SET);
		*/
	}
	//close(fichier);
	printf(" >>>  >>> Thread is ending\n");
	deconnection(acc);
}

/*boucle infini qui traite les connections au serveur*/
void valider_connexion(int port)
{
	printf("---------------/Accept d'une connexion /----------------------\n");
	/*	Creation de la socket	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	int i;
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

	for(i=0;i<MAX_SLAVE;i++){
		slave_co[i]=-1;
	}

	while(1){
		acc = (int *)malloc(2*sizeof(int));
		/*	On accept la connection	*/

		if((*acc = accept(sock, (struct sockaddr *)&sin, &fromlen)) == -1){
			perror("accept");
			exit(1);
		}
		/*	On associe un thread a chaque client connecter	*/
		if(nb_co>=MAX_SLAVE){
			envoie_msg(*acc,FAIL_INIT,-1);
			close(*acc);
			free(acc);
		}else{
			acc[1]=nb_co;
			for(i=0;i<MAX_SLAVE;i++){
				if(slave_co[i]==-1){
					pthread_create(&slave_co[i], NULL,slave_action, acc);
					nb_co ++;
					break;
				}
			}
			
			printf("---------------/ Connexion Accepter %d/--------------------------\n",nb_co);
		}
	}


}










