#include "var.h" 

#ifndef CONNECTION_H_
#define CONNECTION_H_

SOCKET connection(int port,const char * addr);
void deconnection(SOCKET sock);
void valider_connexion(int port);

#endif
