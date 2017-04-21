#include "var.h"

#ifndef MPR_H_
#define MPR_H_

/*	Initialise la mémoire partagée répartie	*/
void init_mpr(int size);

/*	Affiche les donnée de la structure mpr	*/
void print_mpr(mpr m);

/**/
void get_RW(long adr_begin);

/**/
void get_RW_all(long adr_begin,int size);

/**/
void get_R(long adr_begin);

/**/
void remove_RW(long adr_begin);

void remove_RW_all(long adr_begin,int size);
#endif

