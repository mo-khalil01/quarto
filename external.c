#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "external.h"
#include "board.h"

	
	
// fonction peremettent de verifier si le nom de la ligne est le meme que celui du gagnant
bool is_same_name(FILE *ft , FILE* tmp, int *ch, char const *p_name)
{
	// creation d'une variable char qui se remplis du nom de la ligne actuelle
	char name_tab[10];
	
	int i = 0;
	
	// copie le nom dans le tableau 
	while (((*ch) = fgetc(ft)) != ':')
	{
		name_tab[i] = (*ch);
		fputc((*ch), tmp);
		i++;
	}
	fputc((*ch), tmp);
	name_tab[i] = '\0';
	
	// si le nom de la ligne est egale a celui du gagnant retourne true
	if ((strcmp(p_name, name_tab) == 0))
	{
		return true;
	}
	// sinon retourne false
	return false;
	
}


// fonction permettent de lire le contenue du hall_of_fame 
void hall_read(char const *f_name)
{
	// ouverture du fichier hall en mode lecture
	FILE *ft;
	int ch;
	ft = fopen(f_name, "r");
	
	// si le fichier est null affiche une erreur
	if (ft == NULL)
	{
		fprintf(stderr, "erreur ficher: %s ne s'ouvre pas\n", f_name);
		exit(1);
	}
	
	// print le contenue entier du fichier 
	while ((ch = fgetc(ft)) != EOF)
	{
		printf("%c", ch);
	}
	
	// !***!         fermeture du fichier en mode free car fclose         !***!
	// !***! empeche le lancement d'une partie apres avoir visite le hall !***!
	free(ft);
}


// fonction permettent d'ecrire dans le hall_of_fame apres une victoire
void hall_write(char const *p_name)
{
	// ouverture du fichier hall
	FILE *ft;
	char const *f_name = "hall_of_fame.txt";
	ft = fopen(f_name, "a+");
	
	int ch;
	
	// si le fichier est null affiche erreur
	if (ft == NULL)
	{
		fprintf(stderr, "erreur ficher: %s ne s'ouvre pas\n", f_name);
		exit(1);
	}
	
	// creation d'un fichier temporaire
	FILE* tmp = tmpfile();
	// si le fichier temporaire est null affiche erreur
	if (tmp == NULL)
	{
		fprintf(stderr, "erreur ficher temporaire ne s'ouvre pas\n");
		exit(1);
	}
	
	// copie le debut du hall dans le fichier tmp
	for (int i = 0; i < 146; i++) 
	{
		ch = fgetc(ft);
		fputc(ch, tmp);
	}
	
	// variable permettent de savoir si le nom du gagnant a été trouvé
	bool found = false;
	
	// tant que la fin du hall n'a pas été atteinte
	while ((ch = fgetc(ft)) != EOF)
	{
		// recule d'un cran dans le hall car ch n'est pas egal a EOF 
		// ch est donc egale au debut du nom d'un joueur
		fseek(ft, -1L, SEEK_CUR);
		
		// si le nom du gagnant n'a pas ete trouve 
		if (found == false)
		{
			// si le nom de la ligne est egale au nom du gagnant
			// ajoute 1 a son score
			if (is_same_name(ft, tmp, &ch, p_name))
			{
				// 
				found = true;
				
				ch = fgetc(ft);
				fputc(ch, tmp);
				
				ch = fgetc(ft);
				fputc((ch + 1), tmp);
			}
			// sinon recopie le reste jusqu'a la fin de la ligne
			else
			{
				while ((ch = fgetc(ft)) != '\n' && ch != '\0')
				{
					fputc(ch, tmp);
				}
				fputc(ch, tmp);
			}
		}
		// si le nom du gagnant a ete trouvé recopie le reste du hall dans tmp
		else
		{
			while ((ch = fgetc(ft)) != '\n' && ch != '\0')
			{
				printf("3:%c\n", ch);
				fputc(ch, tmp);
			}
			fputc(ch, tmp);
		}
	}
	
	// si le nom n'a pas ete trouve dans le hall alors ajout du nouveau nom
	if (found == false && ch == EOF)
	{
		fprintf(tmp, "%s: 1 victoire\n", p_name);
	}
	
	// reouverture du fichier en mode write 
	fclose(ft);
	ft = fopen(f_name, "w");
	rewind(tmp);
	
	// recopie du fichier temporaire dans le fichier hall
	while( ( ch = fgetc(tmp) ) != EOF ) 
	{
		fputc(ch, ft);
	}
	
	// fermeture des fichier cree
	fclose(tmp);
	fclose(ft);
}
	
	

	




