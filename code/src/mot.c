#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mot.h"


void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

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
