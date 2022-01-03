/**
 * \file mot.c
 * \brief mot.c de l'itispell.
 * \author Mohammed Mamoun Ibn-abdeljalil
 * \version 2.0
 * \date 03/01/2022
 *
 * Programme qui permet de lire l'entrée standard et permet de recherche et d'afficher correctement les mots avec des caractères spéciaux
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mot.h"

/**
 * \brief Permet de vider le buffer si trop de caractères sont rentrés.
 *
 * \param 
 * \return
 */
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

/**
 * \brief Procédure qui permet de lire l'entrée standard
 *
 * \param[in/out] chaine  La chaine qui va stocker l'entrée standard
 * \param[in] longueur  La longueur maximale de la chaine
 */
void lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) 
            *positionEntree = '\0'; 
        else
            viderBuffer();
    }
}


/**
 * \brief Procédure qui est utilisée lorsqu'on veut tranformer les accents d'une chaine de caractères, elle permet d'insérer un caractère dans une chaine
 *
 * \param[in/out] chaine  La chaine à transformer
 * \param[in] insert  Le caractère à insérer
 * \param[in] pos  La position dans la chaine à laquelle on va insérer le caractère 
 * 
 */
void transformeAccentPourAffichage(char motInitial[], const char insert, int pos)
{
    char insertChaine[2];
    
    insertChaine[0] = insert;
    insertChaine[1] = '\0';
    
    char buf[100] = {0};

    strncpy(buf, motInitial, pos);
    int len = strlen(buf);
    strcpy(buf+len, insertChaine);
    len += strlen(insertChaine);
    strcpy(buf+len, motInitial+pos); 

    strcpy(motInitial, buf);
}


/**
 * \brief Procédure qui est utilisée lorsqu'on veut tranformer les accents d'une chaine de caractères, elle permet d'avoir la bonne valeur ASCII pour avoir un bon affichage
 *
 * \param[in/out] chaine  La chaine à transformer
 * 
 */
char *transformeAccentPourLev(char* mot)
{ 
	int i = 0;
    int counter = 0;
    int taille = strlen(mot);

    for (i = 0; i<taille; i++)
    {
        if ((mot[i]>=0) || (mot[i]<-64 && mot[i]>-97))
            counter++;
    }    

    char *motAccentue = (char*)malloc((counter+1)*sizeof(char));

    counter = 0;

    for (int i = 0; i<taille; i++ )
    {
        if (mot[i]>=0)
        {
            motAccentue[counter] = mot[i];
            counter ++;
        }
        else if (mot[i]<-64 && mot[i]>-97)
        {
            motAccentue[counter] = mot[i]+64;
            counter ++;
        }
    }
    motAccentue[counter] = '\0';
    return motAccentue;
}
