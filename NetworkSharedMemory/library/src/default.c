#define _GNU_SOURCE
#define _SVID_SOURCE 1
#define _XOPEN_SOURCE 700 


#include "default.h"
#include "mpr.h"

static void tsigsegv(int sig, siginfo_t *si, void *context)
{	
	char buffer[page_size];
	int num_page = -1;
	if(sig == SIGSEGV)
	{
		/* adresse de la page qui a fait le defaut alignée  */    
		long addr = ((long) si->si_addr >> page_shift) << page_shift ; 
		/* type de l'erreur */
		int err = ((ucontext_t*)context)->uc_mcontext.gregs[REG_ERR];
		//printf("Faute de protection sur la page(%lx) Ox%lx !\n", addr, addr >> page_shift);
		data* d = search_data_by_addr(addr);
		num_page = (addr - memory.adr_begin)/page_size;
		//ECRITURE
		
		if (err & 0x2){
			//printf("ECRITURE\n");
			if(d->flags != LOCK_W){
				printf("ERREUR : Demande de page sans avoir demander le verrou en W\n");
				exit(1);
			}
			if(d->page_update >= 0){
				send_msg(sockac,UPDATE,d->page_update);
				write(sockac, memory.adr_begin + d->page_update*page_size, page_size);
			}
			d->page_update = num_page;
			get_RW(addr);
			send_msg(sockac,WRITE,num_page);
			//Maj de la page actuelle 	
			if(read(sockac, addr,page_size)<0){
				printf("ERREUR WRITE DEFAULT PAGE  :: %lx \n",addr);
				perror("read");
			}
			//printf(">>   Page A jour \n");
		}else{
		//Lecture
			if(d->flags != LOCK_R){
				printf("ERREUR : Demande de page sans avoir demander le verrou en R\n");
				exit(1);
			}
			//printf("LECTURE  >>		%lx \n",addr);
			get_RW(addr);
			send_msg(sockac,READ,num_page);
			
			//MAJ de la page Actuelle
			printf(">>   Page A jour :: ");
			if(read(sockac, addr,page_size)<0){ 
				printf("ERREUR READ DEFAULT PAGE  :: %lx \n",addr);
				//rcv_msg(sockac);
				perror("read");
			}
			printf("OK\n");
			get_R(addr);
		}
	}
}

void init_sig(SOCKET flux){

    /* definir le handler de SIGSEGV */
	sockac = flux;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = tsigsegv;
	if (sigaction(SIGSEGV, &sa, NULL) == -1){
		perror("sigaction");
		exit(1);
	}
}
