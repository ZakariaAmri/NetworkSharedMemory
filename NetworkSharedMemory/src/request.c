#include "../include/communication.h"
#include "../include/msg.h"
#include "../include/data.h"
#include "../include/verrou.h"
#include "../include/default.h"

SOCKET slave_mpr(SOCKET flux,int port,const char * addr)
{
	int request,i=0;
	char *reponse;
	char *size = malloc(sizeof(int));
	char *data;
	char *tmp;
	int data_id= -1,data_size=-1;
	printf("Debut request salve mpr \n");
	flux = connection(port,addr);
	request = envoie_msg(flux,INIT_MPR,999);
	if(request > 0)
	{
		reponse = recevoir_msg(flux);

	}
	strcpy(size,reponse);
	init_mpr(get_id(size));
	
	init_sig(flux);
	//extract_data(reponse);
	printf("FIN request slave mpr\n");
	return flux;
}




int lock_data_read(SOCKET flux,int id)
{
	int request;
	char *reponse;
	printf("*************LOCK READ\n");
	request = envoie_msg(flux,DATA_LOCK_READ,id);
	printf(">>> MSG:: %d\n", request);
	reponse = recevoir_msg(flux);
	if(atoi(reponse) == SUCCES)
		return 0;
	else
		return -1;
}

int unlock_data_read(SOCKET flux,int id)
{
	int request;
	request = envoie_msg(flux,DATA_UNLOCK_READ,id);
	return request;
}

int lock_data_write(SOCKET flux,int id)
{
	int request;
	char *reponse;
	request = envoie_msg(flux,DATA_LOCK_WRITE,id);
	reponse = recevoir_msg(flux);
	if(atoi(reponse) == SUCCES)
		return 0;
	else
		return -1;
}

int unlock_data_write(SOCKET flux,int id)
{
	int request;
	request = envoie_msg(flux,DATA_UNLOCK_WRITE,id);
	return request;
}
