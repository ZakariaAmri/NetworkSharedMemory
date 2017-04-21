#include "../library/lib/libMPR.a"


int main(){
	SOCKET co ;

	/*Initialisation de la mpr + connexion avec le serveur*/
	co = slave_mpr(co,PP,"132.227.112.204");

	print_mpr(memory); 
/*	if ( mprotect((caddr_t)memory.adr_begin, memory.size, PROT_READ | PROT_WRITE) <0 ) {
				perror("mprotect");
				pthread_exit ((void*)EXIT_FAILURE);
	}*/
	int *a ;
	int *b ;
	printf("\n>> [%lx] / a : %p b : %p \n",memory.adr_begin,a,b);

	add_data(&a, sizeof(int),0);
	add_data(&b,1025*(sizeof(int)),1);

	if ( mprotect((caddr_t)memory.adr_begin, memory.size, 0) <0 ) {
				perror("mprotect");
				pthread_exit ((void*)EXIT_FAILURE);
	}
	
	get_lock_read( co,0);
	printf("\n>> [%d ]\n",*a);
	sleep(5);
	release_lock_read( co,0);
	printf("ALLO \n");
	close(co);
	return 1;
}
