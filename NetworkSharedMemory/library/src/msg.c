#include "msg.h"
#include "data.h"

void make_msg(char msg[],int type,int id)
{	
	char tmp[10];
	sprintf(msg, "%d", type);
	strcat(msg, ":");
	sprintf(tmp, "%d", id);
	strcat(msg, tmp);
}

int get_type(char *s)
{	
	char *result = NULL;
	result = strtok(s, ":");
	return atoi(result);
}

int get_id(char *s)
{
	char *result = NULL;
	result = strtok(s, ":");
	result = strtok(NULL,  ":");
	return atoi(result);
}

int get_data_id(char *s)
{
	char *result = NULL;
	result = strtok(s, "&");
	return atoi(result);
}

int get_data_size(char *s)
{
	char *result = NULL;
	result = strtok(s, "&");
	result = strtok(NULL,  "&");
	return atoi(result);
}

void extract_data(char *s)
{
	int j=0;
	char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;


    char *mot= NULL;
    char *data= NULL;
    char *ss_mot= NULL;
    mot = strtok(s,":");
    //mot = strtok(NULL,":");
	for(mot ;mot != NULL;mot = strtok(NULL,":")){
        
        ss_mot = malloc(sizeof(char)*strlen(mot));
        strcpy(ss_mot,mot);
        
        for(data = strtok_r(ss_mot,"&",mot);data != NULL;data = strtok_r(NULL,"&",mot)){
        } 
        j++;
        free(ss_mot);
    } 
}