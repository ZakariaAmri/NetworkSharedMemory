#include "var.h" 

#ifndef DATA_H_
#define DATA_H_

/*	donne la taille a allouer dans la mémoire partagée	*/
int data_mpr(int taille_data,int mpr_size);

/*	initialise une structure data	*/
data *init_data(int id,long adr,int size,int nb_page);

/*	Affiche les différentes information de la structure data	*/
void print_data();

/*	Ajoute une donnée dans la mémoire partagée répartie	*/
void add_data(void *adr_data,int taille_data,int id);

/* Retourne le nombre de donnée contenu dans la mpr*/
int nb_data();

/* initialise la structure data pour un esclave*/
int init_slave_data(int nb);

char* data_to_char();

/* Recherche la structure data qui gère la donnée d'identifiant id*/
data* search_data(int id);

/* Recherche l'id de la donnée accédée sans permission*/
int search_id(long *addr);

#endif
