#include "./src/request.h"
#include "./src/mpr.h"
#include "./src/data.h"
#include <time.h>
#define N 10

int main(){
	float temps;
    clock_t t1, t2;
    t1 = clock();
	SOCKET co ;

	/*Initialisation de la mpr + connexion avec le serveur*/
	co = slave_mpr(co,PP,"127.0.0.1");

	print_mpr(memory); 

	typedef struct {
		int tab[N][N];
	} test;
	
	test *a,*b,*c;
	
	slave_add_data(&a, N*N*sizeof(int),0);
	slave_add_data(&b, N*N*sizeof(int),1);
	slave_add_data(&c, N*N*sizeof(int),2);

	int i = 0;
	while(i<=100){
		lock_data_write( co,0);
		a->tab[0][0] = (i++)%1024;
		printf("apres %d\n",a->tab[0][0]);
		//sleep(1);
		printf("%d\n",i++);
		unlock_data_write( co,0);	
	}
	

	close(co);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
	return 1;
}
