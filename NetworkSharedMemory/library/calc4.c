#include "./src/request.h"
#include "./src/mpr.h"
#include "./src/data.h"
#include <time.h>
#define N 100

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


 
    
 
    // Ton programme
     
    
    
		
		
		
		int i,j,k;
		int tmp,tmp2,tmp3;
		for(i=N/2;i<N;i++){
			for(j=N/2;j<N;j++){
				tmp=0;
				for(k=0;k<N;k++){
					printf("%d %d %d\n",i,j,k);
					get_lock_read( co,0);
					tmp2=a->tab[i][k];
					release_lock_read( co,0);

					get_lock_read( co,1);
					tmp3=b->tab[k][j];					
					release_lock_read( co,1);

					tmp+=tmp2*tmp3;
				}
				get_lock_write( co,2);
				c->tab[i][j]=tmp;
				release_lock_write( co,2);

			}
			
		}
		
		
		
		get_lock_read( co,2);
		for(i=N/2;i<N;i++){
			for(j=N/2;j<N;j++){
				printf("%d ",c->tab[i][j]);
			}
			printf("\n");
		}
		printf("\n ALLO %d",c->tab[N-1][1]);

		release_lock_read( co,2);	
	

	close(co);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
	return 1;
}
