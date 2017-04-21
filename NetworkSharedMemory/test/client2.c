#include "../include/msg.h"
#include "../include/connection.h"


int main(){
	SOCKET co ;

	/*Initialisation de la mpr + connexion avec le serveur*/
	co = slave_mpr(co,PP,"132.227.112.201");

	print_mpr(memory);
	int *a = malloc(sizeof(int *));
	int *b = malloc(1025*(sizeof(int)));
	printf(">> b :: %p\n", b);
	add_data(memory ,a, sizeof(int),0);
	add_data(&memory ,b,1025*(sizeof(int)),1);
	printf(">> b :: %p\n", b);
	if ( mprotect((char *)(caddr_t)memory.adr_begin, memory.size, 0) <0 ) {
		perror("mprotect");
		exit(1);
	} 		 
	printf(">> JE DORS %p\n",b);
	lock_data_write( co,1);
	b[0]=1;
	sleep(5);
	unlock_data_write( co,1);
	printf("ALLO \n");
	close(co);
	return 1;
}
