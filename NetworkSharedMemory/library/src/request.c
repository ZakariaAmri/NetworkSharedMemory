#include "request.h"
#include "communication.h"
#include "data.h"

SOCKET slave_mpr(SOCKET flux,int port,const char * addr)
{
	int request,i=0;
	char *reponse;
	char *size = malloc(sizeof(int));
	char *data;
	char *tmp;
	int data_id= -1,data_size=-1;
	printf("Debut request salve mpr \n");
	//On se connect au Serveur
	flux = connection(port,addr);
	//On demande la taille de la MPR
	request = send_msg(flux,INIT_MPR,999);
	if(request > 0)
	{
		//On  attend la reponse du Serveur
		reponse = rcv_msg(flux);

	}
	strcpy(size,reponse);
	//Initialise la MPR coter client
	init_mpr(get_id(size));
	//On enlève les droits
	if ( mprotect((caddr_t)memory.adr_begin, memory.size, 0) <0 ) {
				perror("mprotect");
				pthread_exit ((void*)EXIT_FAILURE);
	}
	init_sig(flux);
	//extract_data(reponse);
	return flux;
}




int get_lock_read(SOCKET flux,int id)
{
	printf("Debut lock R %d\n",pthread_self());
	int request;
	char *reponse;
	data* d = search_data(id);
	printf("data trouvée\n");
	request = send_msg(flux,DATA_LOCK_READ,id);
	printf("msg envoyée %d \n",request);
	if(request<0)
	{
		perror("Lock en R");
		return -1;
	}
	reponse = rcv_msg(flux);
	printf("reponse %d \n",reponse);
	if(atoi(reponse) == SUCCES){
		d->flags = LOCK_R;
		printf("Fin lock R %d\n",pthread_self());
		return 0;
	}
	else
		printf("Erreur");
		return -1;
}

int release_lock_read(SOCKET flux,int id)
{
	printf("Debut unlock R %d\n",pthread_self());
	int request;
	data *d = search_data(id);
	if(request = send_msg(flux,DATA_UNLOCK_READ,id)<0){
		perror("release_lock_read");
	}
	d->flags = -1;
	printf("Fin unlock R %d\n",pthread_self());
	return request;
}

int get_lock_write(SOCKET flux,int id)
{
	int request;
	char *reponse;
	data* d = search_data(id);
	request = send_msg(flux,DATA_LOCK_WRITE,id);
	reponse = rcv_msg(flux);
	if(atoi(reponse) == SUCCES){
		d->flags = LOCK_W;
		return 0;
	}
	else{
		printf("ERREUR LOCK \n");
		return -1;
	}
}

int release_lock_write(SOCKET flux,int id)
{
	int request,tmp,aux;
	data* d = search_data(id);
	//write(flux, memory.adr_begin + d->page_update*page_size, page_size);
	
	if(d->page_update!=-1){
		request = send_msg(flux,UPDATE,d->page_update);
		aux = write(flux, memory.adr_begin + d->page_update*page_size, page_size);
	}
	tmp = send_msg(flux,DATA_UNLOCK_WRITE,id);
	remove_RW_all(d->adr_begin,d->nb_page);
	d->page_update = -1;
	d->flags = -1;
	return request;
}
