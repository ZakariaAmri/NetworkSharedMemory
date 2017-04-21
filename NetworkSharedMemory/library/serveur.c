#include "./src/mpr.h"
#include "./src/data.h"
#include "./src/connection.h"

#define N 100

typedef struct {
		int tab[N][N];
	} test;

int main(){
	SOCKET cour;
	SOCKET_ACCEPT sa;

	init_mpr(409600*3);
	
	test *a,*b,*c;
	a=(test*)malloc(sizeof(test));
	b=(test*)malloc(sizeof(test));
	c=(test*)malloc(sizeof(test));
	
	int i,j,k;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a->tab[i][j]= i;
			b->tab[i][j]= i+j;
		}
	}
	/*
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			c->tab[i][j]=0;
			for(k=0;k<N;k++){
				c->tab[i][j]+=a->tab[i][k]*b->tab[k][j];
			}
		}
		
	}
	*/
	
	print_mpr(memory);
	add_data(&a, N*N*sizeof(int),0);
	add_data(&b, N*N*sizeof(int),1);
	add_data(&c, N*N*sizeof(int),2);
	printf(">>>>> %p\n",b);
	print_mpr(memory);
	print_data();

	printf("NB DATA : %d\n", nb_data(*store));
	data_to_char();	
	valider_connexion(PP);
	//close(sa);
	return 0;
}
