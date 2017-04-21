#include "data.h"

typedef struct test test;
struct test {
	int a;
	int b;
	int tab[4094];
};

int data_mpr(int taille_data,int mpr_size)
{
	if (taille_data % page_size )
		taille_data = (((unsigned) taille_data >> page_shift) << page_shift) + page_size;
	return taille_data;
}

data *init_data(int id,long adr,int size,int nb_page)
{
	data *tmp = malloc(sizeof(data));
	tmp->adr_begin = adr;
	tmp->next_data = NULL;
	tmp->size = size;
	tmp->id = id;
	tmp->nb_page = nb_page;
	tmp->page_update = -1;
	pthread_mutex_init (&(tmp->mutexlecture),NULL);
	pthread_mutex_init (&(tmp->mutexressource),NULL);
	pthread_mutex_init (&(tmp->fifo),NULL);
	tmp->nbl=0;
	return tmp;
}

void add_data(void **adr_data,int taille_data,int id)
{
	int nb_page = data_mpr(taille_data,memory.size)/page_size;
	printf("---------------/Ajout de donnée dans la MPR/------------------\n");
	/*	copie de la donnée dans la MPR	*/
	printf(">> LOCAL -> MPR [%p]\n",(void *)memory.adr_cur);
	memcpy((void *)memory.adr_cur, *adr_data, taille_data);
	/*	Maj struture store	*/
	printf(">> CREATE DATA TMP\n");
	data *tmp = malloc(sizeof(data));
	tmp = init_data(id,memory.adr_cur,taille_data,nb_page);

	data *aux = malloc(sizeof(data));
	aux = store;
	printf(">> DATA -> STORE\n");
	if(store == NULL){
		printf(">> PASSAGE STORE VIDE\n");
		store = tmp;
	}else{
		printf(">> PASSAGE STORE NON VIDE\n");
		while(aux->next_data!= NULL)
		{
			aux = aux->next_data;
		}
		
		aux->next_data = tmp;
	}
	/*	Maj pointeur => MPR et Donnée local	*/
	printf("%lx\n",*adr_data );	
	*adr_data = (void*)memory.adr_cur;
	printf("%lx\n",*adr_data );
	memory.adr_cur =  (long)(((long)*adr_data >> page_shift)+nb_page) << page_shift;
	printf("---------------/Fin Ajout dans la MPR/------------------------\n");
	print_data();
}

void slave_add_data(void **adr_data,int taille_data,int id)
{
	int nb_page = data_mpr(taille_data,memory.size)/page_size;
	printf("---------------/Ajout de donnée dans la MPR/------------------\n");
	/*	copie de la donnée dans la MPR	*/
	printf(">> LOCAL -> MPR [%p]\n",(void *)memory.adr_cur);
	//memcpy((void *)memory.adr_cur, *adr_data, taille_data);
	/*	Maj struture store	*/
	printf(">> CREATE DATA TMP\n");
	data *tmp = malloc(sizeof(data));
	tmp = init_data(id,memory.adr_cur,taille_data,nb_page);

	data *aux = malloc(sizeof(data));
	aux = store;
	printf(">> DATA -> STORE\n");
	if(store == NULL){
		printf(">> PASSAGE STORE VIDE\n");
		store = tmp;
	}else{
		printf(">> PASSAGE STORE NON VIDE\n");
		while(aux->next_data!= NULL)
		{
			aux = aux->next_data;
		}
		
		aux->next_data = tmp;
	}
	/*	Maj pointeur => MPR et Donnée local	*/
	printf("%lx\n",*adr_data );	
	*adr_data = (void*)memory.adr_cur;
	printf("%lx\n",*adr_data );
	memory.adr_cur =  (long)(((long)*adr_data >> page_shift)+nb_page) << page_shift;
	printf("---------------/Fin Ajout dans la MPR/------------------------\n");
	print_data();
}

void print_data()
{
	data *aux =malloc(sizeof(data));
	aux = store;
	printf(">> DONNEE \n");
	do
	{
		printf("%p\n",aux);
		printf("[id = %d |",aux->id);
		printf("adr = %p|",aux->adr_begin);
		printf("taille = %d|",aux->size);
		printf("nb page = %d]\n",aux->nb_page);
		aux = aux->next_data;
	}while(aux != NULL);
}


int nb_data()
{
	int cpt = 0;
	data *aux =malloc(sizeof(data));
	aux = store;
	do
	{
		cpt ++;
		aux = aux->next_data;
	}while(aux != NULL);
	return cpt;
}

int init_slave_data(int nb)
{
	int i ;
	data *d,aux;
	for (i = 0; i < nb; ++i)
	{	

		d = init_data(i,-1,0,0);
	}
	return 0;
	
}

char* data_to_char()
{
	char tmp[100];
	char *res=malloc(20*sizeof(int)+sizeof(tmp));
	data *aux =malloc(sizeof(data));
	aux = store;
	sprintf(tmp,"%d:", memory.size);
		strcat(res,tmp);
	do
	{
		
		sprintf(tmp,"%d",(int)aux->id);
		strcat(res,tmp);
		strcat(res,"&");
		sprintf(tmp,"%d:",aux->size);
		strcat(res,tmp);
		aux = aux->next_data;
	}while(aux != NULL);


	//printf("MSG :: [%s]\n", res);
	free(aux);
	return res;
}

data* search_data(int id){
	data* d = store;
	do
	{
		if(d->id==id){
			return d;
		}
		d = d->next_data;
	}while(d != NULL);
	return NULL;
}


data* search_data_by_addr(long *addr){
	data* d = store;


	while(d!=NULL){
		if(addr >= d->adr_begin && addr < d->adr_begin+ d->size){
			return d;
		}
		d=d->next_data;
	}

	return NULL;
}

/*
int main()
{
	//store = malloc(sizeof(data));
	int *a= malloc(sizeof(int));
	int *b= malloc(sizeof(int));
	init_mpr(4099);
	add_data(&a,sizeof(int),0);
	add_data(&b,sizeof(int),1);

	return 1;
}
*/
