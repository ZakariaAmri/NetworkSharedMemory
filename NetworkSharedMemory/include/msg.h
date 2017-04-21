#include "var.h" 


#ifndef MSG_H_
#define MSG_H_

void make_msg(char msg[],int type,int id);

int get_type(char *s);

int get_id(char *s);

#endif
