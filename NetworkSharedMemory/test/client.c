#include "../include/msg.h"
#include "../include/connection.h"


int main(){
	SOCKET co ;

	/*Initialisation de la mpr + connexion avec le serveur*/
	co = slave_mpr(co,PP,"132.227.112.227");

	print_mpr(memory);
	int *a = malloc(sizeof(int *));
	int *b = malloc(1025*(sizeof(int)));
	add_data(&memory ,a, sizeof(int),0);
	add_data(&memory ,b,1025*(sizeof(int)),1);
	printf(">> JE DORS\n");
	get_lock_read( co,0);
	//printf("\n>> [%d]\n",(int)memory.adr_begin);
	sleep(5);
	release_lock_read( co,0);
	printf("ALLO \n");
	close(co);
	return 1;
}
