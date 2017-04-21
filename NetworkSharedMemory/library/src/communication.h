#include "var.h" 

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

int send_msg(SOCKET flux,int type,int id);

int process(SOCKET flux,char *buffer);

char *rcv_msg(SOCKET flux);

#endif