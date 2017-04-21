#include "var.h"
#ifndef REQUEST_H_
#define REQUEST_H_

/*		Initialise le systeme			*/
SOCKET slave_mpr(SOCKET flux,int port,const char * addr);

/*		Demande un verrou en lecture	*/
int get_lock_read(SOCKET flux,int id);

/*		Demande de libérer son verrou en lecture	*/
int release_lock_read(SOCKET flux,int id);

/*		Demande un verrou en écriture	*/
int get_lock_write(SOCKET flux,int id);

/*		Demande de libérer son verrou en écriture	*/
int release_lock_write(SOCKET flux,int id);


#endif