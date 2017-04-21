#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])

{

	FILE* fichier = NULL;

	int caractereActuel = 0;

	fichier = fopen("test.txt", "w");


 

    if (fichier != NULL)

    {

        do

        {

            caractereActuel = fgetc(stdin); // On lit le caractère

            fputc(caractereActuel,fichier);

        } while (caractereActuel != '\n'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

 

        fclose(fichier);

    }

 

    return 0;

}
