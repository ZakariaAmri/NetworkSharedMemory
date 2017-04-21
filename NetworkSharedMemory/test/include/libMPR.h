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
#define MAX_SLAVE 10
unsigned next_page; //pour decaler d'une page
int page_size; //nb octe d'une page

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
	data *next_data;//pointeur vers la prochaine donnée
} *store;

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
#define SUCCES				12	

/*	PORT SERVEUR	*/
# define PP 4011	//PORT CONNEXION SERVEUR

/*		TYPAGE POUR LA COMMUNICATION	*/

#define INVALID_SOCKET -1	
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef int SOCKET_ACCEPT;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

/*		Traitement defaut de page_size	*/
struct sigaction sa;
SOCKET sockac;
//Serveur
extern void init_mpr(int size); 
extern void valider_connexion(int port); //accept() +thread

//Client
extern SOCKET slave_mpr(SOCKET flux,int port,const char * addr);
extern int lock_data_read(SOCKET flux,int id);
extern int unlock_data_read(SOCKET flux,int id);
extern int lock_data_write(SOCKET flux,int id);
extern int unlock_data_write(SOCKET flux,int id);

//DEBUG

extern void print_mpr(mpr m);
extern void add_data(void **adr_data,int taille_data,int id);

