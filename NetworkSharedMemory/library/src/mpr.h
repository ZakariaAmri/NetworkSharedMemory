#include "var.h"

#ifndef MPR_H_
#define MPR_H_

/*	Initialise la mémoire partagée répartie	*/
void init_mpr(int size);

/*	Affiche les donnée de la structure mpr	*/
void print_mpr(mpr m);

/*	Recupère les droits lecture/ecriture au niveau d'une page*/
void get_RW(long adr_begin);

/*	Recupère les droits lecture ecriture au niveau d'une donnée		*/
void get_RW_all(long adr_begin,int size);

/*		Recupère les droits en lecture		*/
void get_R(long adr_begin);

/*		Enleve les droit en lecture/écriture sur une page 	*/
void remove_RW(long adr_begin);

/*		Enleve les droits en lecture/ecriture sur une donnée*/
void remove_RW_all(long adr_begin,int size);
#endif

