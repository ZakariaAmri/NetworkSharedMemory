#define _GNU_SOURCE
#define _SVID_SOURCE 1
#define _XOPEN_SOURCE 700 


#include "../include/default.h"
#include "../include/mpr.h"

static void tsigsegv(int sig, siginfo_t *si, void *context)
{
	if(sig == SIGSEGV){
	
		/* adresse de la page qui a fait le defaut alignée  */    
		long addr = ((long) si->si_addr >> next_page) << next_page ; 
		/* type de l'erreur */
		int err = ((ucontext_t*)context)->uc_mcontext.gregs[REG_ERR];

		printf("Faute de protection sur la page(%p) Ox%lx !\n", addr, addr >> next_page);
		sleep(5);
		
		data* d = search_data_by_addr(addr);

		if (err & 0x2){
			printf("ECRITURE\n");
		
			envoie_msg(sockac,WRITE,d->id);

			if(atoi(recevoir_msg(sockac))==SUCCES){
				if ( mprotect((char *)(caddr_t)d->adr_begin, (d->nb_page)*page_size, PROT_READ | PROT_WRITE) <0 ) {
					perror("mprotect");
					exit(1);
				}
			}else{
				printf("ALLO C PAS OK\n");
			}
		}else{/*
			printf("LECTURE\n");
			
			strcpy(req.type,"read");
			req.page = (addr - (long int)data)/page_size;
			if(write(sock,&req,sizeof(req))<0){
				perror("write");
				exit(1);
			}
			
			if ( mprotect((char *)(caddr_t)addr, page_size, PROT_READ | PROT_WRITE) <0 ) {
				perror("mprotect");
				exit(1);
			}
		
			if(read(sock,(void*)addr,page_size)<0){
				perror("read");
				exit(1);
			}
		
		
			if ( mprotect((char *)(caddr_t)addr, page_size, PROT_READ) <0 ) {
				perror("mprotect");
				exit(1);
			}*/
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
