#include "../include/msg.h"
#include "../include/connection.h"
#include "../include/data.h"

int main(){
	SOCKET cour;
	SOCKET_ACCEPT sa;
	init_mpr(sizeof(int *)*1026);
	int *a = malloc(sizeof(int *));
	int *b = malloc(1025*(sizeof(int)));
	b[0]=5;
	*a = 2;
	print_mpr(&memory);
	add_data(a, sizeof(int),0);
	add_data(b,1025*(sizeof(int)),1);
	
	print_mpr(&memory);
	print_data();

	printf("NB DATA : %d\n", nb_data(*store));
	data_to_char();	
	valider_connexion(PP);

	//close(sa);
}
