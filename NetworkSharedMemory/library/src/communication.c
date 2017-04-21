#include "communication.h"
#include "verrou.h"
#include "msg.h"


int send_msg(SOCKET flux,int type,int id)
{
	char *tmp;
	int val;
	char msg[1023] = "";
	make_msg(msg,type,id);
	//printf(">> Envoie du message :: ");
	val = write(flux, msg, 1023);
	if(val < 0)
	{
	    perror("write()");
	    exit(errno);
	}
	//printf("[%s](nb_charactère :%d)\n",msg,val);

	//printf(">> Fin Envoie du message \n");
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

int envoie_page(SOCKET flux,int type,char *msg)
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


int process(SOCKET flux,char *buffer)
{
	char *id;
	int value = 0;
	int num_page = -1;
	long adr_req;
	data* d;
	id = malloc(sizeof(int)*2+sizeof(char)*2);
	strcpy(id,buffer);
	int send = 0;
	int tmp ;
	int r = page_size;
	switch(get_type(buffer))
	{
		case INIT_MPR		:
			value = memory.size;
			send_msg(flux,SUCCES,value);
			break;

		case DATA_LOCK_READ		:
			tmp= get_id(id);
			lock_read(tmp);
			d = search_data(tmp);
			printf("NTM 1\n");
			send_msg(flux,SUCCES,666);
			printf("NTM le retour\n");
			break;

		case DATA_UNLOCK_READ	:
			printf("NTP  \n");
			tmp = get_id(id);
			printf("NTP \n",tmp);
			d = search_data(tmp);
			printf("NTP %lx\n",d->adr_begin);
			unlock_read(tmp);
			break;

		case DATA_LOCK_WRITE	:
			tmp= get_id(id);
			d = search_data(tmp);
			lock_write(tmp);
			send_msg(flux,SUCCES,666);
			remove_RW_all(d->adr_begin,d->nb_page);
			break;

		case DATA_UNLOCK_WRITE	:
			tmp= get_id(id);
			d = search_data(tmp);
			get_RW_all(d->adr_begin,d->nb_page);
			unlock_write(tmp);
			break;


		case READ		:
			printf("\n>> read\n");
			num_page = get_id(id);
			adr_req = memory.adr_begin + num_page*page_size;
			//get_RW(adr_req);
			printf(">> erreur A???\n");
			if(write(flux, adr_req, page_size)<=0){
				printf("ERROR\n");
				perror("write");
			}
			//printf(">> erreur ???\n");
			//get_R(adr_req);
			break;

		case WRITE		:
			num_page = get_id(id);
			adr_req = memory.adr_begin + num_page*page_size;
			get_RW(adr_req);
			write(flux, adr_req, page_size);
			remove_RW(adr_req);
			break;

		case UPDATE		:
			num_page = get_id(id);
			get_RW(memory.adr_begin+num_page*page_size);
			if(r=read(flux, memory.adr_begin+num_page*page_size,page_size)<0){
				printf("ERREUR READ SERVEUR PAGE  :: %d \n",buffer);
				perror("read");
			}
			if(r==0){
				//printf("ALLO %d \n",r);
			}
			remove_RW(memory.adr_begin+num_page*page_size);
			break;
		case SUCCES		:
			//printf(" >>> SUCCES\n");
			break;

		default:
			printf("[Type de demande non traitée ]\n");
			break;
	}
	return 1;
	printf(">> >> Fin de process\n" );
}

char *rcv_msg(SOCKET flux)
{
	char buffer[1024]="",tmp[1024]="";
	//buffer = malloc(sizeof(int)*2+sizeof(char)*2);
	int n = 0;
	n = read(flux, buffer, sizeof buffer -1);

	printf("\n>>[%s]\n",buffer);
	if(n < 0)
	{
      		perror("recv()");
      		exit(errno);
	}

	if(n == 0)// Deconnexion forcée du client
		return NULL;
	buffer[n] = '\0';
	strcpy(tmp,buffer);
	if(process(flux,tmp) ==-1){
		return "";
	}
	//free(tmp);
	printf("BUFFER %s\n",tmp);
	return "";
}


