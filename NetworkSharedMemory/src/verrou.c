#include "../include/verrou.h"


void l_data_read(int id)
{
	data *d = search_data(id);

	pthread_mutex_lock(&(d->fifo));
	pthread_mutex_lock(&(d->mutexlecture));
	printf("LOCK NBL %d\n",d->nbl);
	if(d->nbl==0)
		pthread_mutex_lock(&(d->mutexressource));
	d->nbl++;
	pthread_mutex_unlock(&(d->mutexlecture));
	pthread_mutex_unlock(&(d->fifo));
}

void unl_data_read(int id)
{
	data *d = search_data(id);
	pthread_mutex_lock(&(d->mutexlecture));
		
	d->nbl--;
	
	if(d->nbl==0)
		pthread_mutex_unlock(&(d->mutexressource));
	
	pthread_mutex_unlock(&(d->mutexlecture));

}


void l_data_write(int id)
{
	data *d = search_data(id);
	pthread_mutex_lock(&(d->fifo));
	pthread_mutex_lock(&(d->mutexressource));
	pthread_mutex_unlock(&(d->fifo));

}

void unl_data_write(int id)
{
	data *d = search_data(id);
		
	pthread_mutex_unlock(&(d->mutexressource));
}