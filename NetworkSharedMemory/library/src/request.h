#include "var.h"
#ifndef REQUEST_H_
#define REQUEST_H_

SOCKET slave_mpr(SOCKET flux,int port,const char * addr);

int lock_data_read(SOCKET flux,int id);

int unlock_data_read(SOCKET flux,int id);

int lock_data_write(SOCKET flux,int id);

int unlock_data_write(SOCKET flux,int id);


#endif