#include "var.h" 

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

int envoie_msg(SOCKET flux,int type,int id);

int traitement(SOCKET flux,char *buffer);

char *recevoir_msg(SOCKET flux);

int envoie_data(SOCKET flux,int type,char *msg);
#endif