#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <features.h>
#include <execinfo.h>
#include <signal.h>
#include <ucontext.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>


#ifndef VAR_H_
#define VAR_H_
/*		GESTIONNAIRE MEMOIRE PARTAGEE	*/
#define MAX_SLAVE 10
unsigned page_shift; //pour decaler d'une page
int page_size; //nb octe d'une page

/*		STOCKER MPR VAR	*/
typedef struct mpr mpr;
struct mpr 
{
	long adr_begin; //adresse du debut de la mpr
	long adr_cur; //addr qui pointe vers la premier page disponible(ou la fin si mpr pleine)
	int size; //nb octe de la mpr
}memory;

/*		GESTIONNAIRE DE DONNEES	*/
typedef struct data data;
struct data 
{
	int id; //id d'une donnée
	long adr_begin; //adr du debut de la donnée
	int size;//nb octe de la donnée
	int nb_page;//nb page que prend la donnée en mémoire
	pthread_mutex_t mutexlecture,mutexressource,fifo; //verrou pour les accèes a la donnée en R/W
	int nbl;
	int page_update;
	int flags;
	data *next_data;//pointeur vers la prochaine donnée
} *store;
/*		FLAGS LOCK	*/
#define LOCK_R			20	
#define LOCK_W			21

/*		TYPE  DE MESSAGE	*/
#define INIT_MPR			99	//INITIaLISE LA MEMOIRE
#define DATA_LOCK_READ		2	//DEMANDE DE VERROU POUR UNE LECTURE
#define DATA_UNLOCK_READ	3	//FIN DE LA LECTURE DU CLIENT
#define DATA_LOCK_WRITE		4	//DEMANDE DE VERROU POUR UNE ECRITURE
#define DATA_UNLOCK_WRITE	5	//FIN DE L'ECRITURE DU CLIENT
#define READ				6	//DEMANDE LECTURE (SUR UNE PAGE)
#define WRITE				7	//DEMANDE D'ECRITURE SUR UNE PAGE
#define ERROR_I				8	//ERREUR INITIALISATION
#define ERROR_R				9	//ERREUR LECTURE
#define ERROR_W				10	//ERREUR ECRITURE
#define ERROR_L				11	//ERREUR VERROU
#define UPDATE				12	
#define SUCCES				13
#define FAIL_INIT			14

/*	PORT SERVEUR	*/
# define PP 4025	//PORT CONNEXION SERVEUR

/*		TYPAGE POUR LA COMMUNICATION	*/

#define INVALID_SOCKET -1	
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef int SOCKET_ACCEPT;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

/*		process defaut de page_size	*/
struct sigaction sa;
SOCKET sockac;

#endif
