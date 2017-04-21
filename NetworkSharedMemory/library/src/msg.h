#include "var.h" 

#ifndef MSG_H_
#define MSG_H_

/*		Créer un message	*/
void make_msg(char msg[],int type,int id);

/*		Récupère le type du message		*/
int get_type(char *s);

/*		Recupere l'id du message		*/
int get_id(char *s);

#endif
