#include "../include/communication.h"
#include "../include/verrou.h"


int envoie_msg(SOCKET flux,int type,int id)
{
	char *tmp;
	int val;
	char msg[50] = "";
	construction_message(msg,type,id);
	printf("---------------/ Envoie du message/---------------------------\n");
	val = write(flux, msg, strlen(msg));
	if(val < 0)
	{
	    perror("write()");
	    exit(errno);
	}
	printf("msg : %s %d\n",msg,val);
	printf("---------------/FIN Envoie du message/------------------------\n");
	return val;
}

int envoie_data(SOCKET flux,int type,char *msg)
{
	int val =-1;
	printf("---------------/ Envoie du message/---------------------------\n");
	strcat(msg,SUCCES);
	val = write(flux, msg, strlen(msg));
	if(val < 0)
	{
	    perror("write()");
	    exit(errno);
	}
	printf("msg : %s %d\n",msg,val);
	printf("---------------/FIN Envoie du message/------------------------\n");
	return val;
}


void traitement(SOCKET flux,char *buffer)
{
	char *id,*data;
	int value = 0;

	id = malloc(sizeof(int)*2+sizeof(char)*2);
	strcpy(id,buffer);
	int send = 0;
	printf("Demande ::");
	switch(get_type(buffer))
	{

		case INIT_MPR		:
			value = memory.size;
			printf(" initialiser la memoire partage :: %d\n", value);
			//data = data_to_char();
			//envoie_data(flux,SUCCES,data);
			envoie_msg(flux,SUCCES,value);
			break;

		case DATA_LOCK_READ		:
			printf(" verrouiller la donnée en lecture\n");
			l_data_read(get_id(id));
			envoie_msg(flux,SUCCES,666);
			break;

		case DATA_UNLOCK_READ	:
			printf(" déverrouiller la donnée en lecture\n");
			unl_data_read(get_id(id));
			break;

		case DATA_LOCK_WRITE	:
			printf(" verrouiller la donnée en écriture\n");
			l_data_write(get_id(id));
			envoie_msg(flux,SUCCES,666);

			break;

		case DATA_UNLOCK_WRITE	:
			printf(" déverrouiller la donnée en écriture\n");
			unl_data_write(get_id(id));

			break;


		case READ		:
			printf(" lire une page\n");
			break;

		case WRITE		:
			printf("	écrire sur une page\n");
			break;

		case SUCCES		:
			printf("	SUCCES\n");
			break;

		default:
			printf("	Type de demande non traitée\n");
			break;
	}
	printf(">> >> Fin de traitement\n" );
}

char *recevoir_msg(SOCKET flux)
{
	char buffer[1024]="",*tmp;
	//buffer = malloc(sizeof(int)*2+sizeof(char)*2);
	int n = 0;
	printf("---------------/ Reception du message/------------------------\n");
	printf(">>  %s  %d FLUX %d\n",buffer,sizeof buffer -1,flux );
	n = read(flux, buffer, sizeof buffer -1);
	if(n < 0)
	{
      		perror("recv()");
      		exit(errno);
	}

	if(n == 0)// Deconnexion forcée du client
		return NULL;
	printf("message :: [ %s ] %d sur le flux %d\n",buffer,n,flux);
	buffer[n] = '\0';
	tmp = malloc(sizeof(int)*2+sizeof(char)*2);
	strcpy(tmp,buffer);
	traitement(flux,tmp);
	free(tmp);
	printf("---------------/ Fin de la reception du message/--------------\n");
	return &buffer;
}


