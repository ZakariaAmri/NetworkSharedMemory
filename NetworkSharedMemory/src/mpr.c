#include "../include/mpr.h"

void init_mpr(int size)
{

	printf("---------------/Initialisation de la MPR/---------------------\n");
	int fd;
	int flags = MAP_PRIVATE| MAP_FILE;
 	page_size = getpagesize();
  	page_shift = 12;
  	mpr m ;
  	/* Initialiser le segment a 0 */
  	if ((fd = open("/dev/zero", O_RDWR)) == -1) {
  		perror("open");
    		exit(1);
  	}
    	/* Aligner la taille sur un multiple de pages */
	if (size % page_size )
		size = (((unsigned) size >> page_shift) << page_shift) + page_size;
	/*	sauvegarde la taille de la mpr et l'adresse du debut	*/
 	m.size = size;
  	m.adr_begin = (long)mmap(0, size, PROT_READ|PROT_WRITE, flags, fd, 0);  
  	if ( (caddr_t)m.adr_begin == (caddr_t)-1L) {
     	 	perror("mmap");
      		exit(1);
   	}
  	m.adr_cur = m.adr_begin;
  	memory = m;
  	print_mpr(memory);
  	printf("---------------/MPR Prêt/------------------------------------------\n");
}

void print_mpr(mpr m){
	printf(">>MPR INFORMATION \n");
	printf("	taille mpr:: %d\n",m.size);
	printf("	pt debut  :: %p\n",m.adr_begin);
	printf("	pt cur    :: %p\n",m.adr_cur);
}

/*
int main()
{
	init_mpr(4096);
	
}
*/

