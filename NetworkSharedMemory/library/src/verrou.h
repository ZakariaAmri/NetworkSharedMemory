#include "var.h" 

#ifndef VERROU_H_
#define VERROU_H_

/*		Verouille une donnée en lecture		*/
void lock_read(int id);


/*		Déverouille une donnée en lecture		*/
void unlock_read(int id);

/*		Verouille une donnée en écriture		*/
void lock_write(int id);

/*		Deverouille une donnée en écriture		*/
void unlock_write(int id); 

#endif