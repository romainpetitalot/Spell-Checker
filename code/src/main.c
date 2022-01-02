#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "mot.h"
#include "dictionnaire.h"
#include "correcteur.h"


void afficherAide()
{
    printf("Aide de itispell :\n");
    printf("    itispell -h : cette aide\n");
    printf("    itispell -d dico : correction de l'entree standard a l'aide du dictionnaire dico\n");
    printf("    itispell -d dico -f fic : compléter le dictionnaire dico a l'aide des mots du fichier fic (un mot par ligne)\n");
}


int main(int argc, char *argv[])
{
    char optstring[]="d:f:h";
    int c = 0;
    int dflag = 0; 
    int fflag = 0;

    Noeud *racine = NULL;

    char nom_dico[30];
    char nom_fichier[30];
    
    if (argc<2)
        afficherAide();

    while( (c=getopt (argc, argv, optstring)) != -1 )
    {
        switch(c)
        {
            case 'd':
                dflag = 1;
                strcpy(nom_dico, optarg );
                break;
            case 'h':
                afficherAide();
                break;
            case 'f':
                fflag = 1;
                strcpy(nom_fichier, optarg );
                break;
            default:
                afficherAide();
                break;
        }    
    } 

    if (fflag)
    {
        if (dflag)
        {
            creerDico(&racine, nom_fichier);
              
            sauvegarderDico(racine, nom_dico);
              
            libererDico(racine);
        }    
        else
        {
            printf("Il faut rentré le nom du dico à créer\n");
            afficherAide();
		}        
    }

    else if (dflag)
    {
        lireDico(&racine, nom_dico);
        
        char phrase[5000];
        lire(phrase, 5000);

        int i=0;
        char separateur[] = " ',!:.?()[]{}";
        Mot mots = {0};
        while(phrase[i] != '\0') 
        { 
            char c = phrase[i];
            if (strchr(separateur, c) == NULL)
            {
                if (strlen(mots.chaine)==0)
                    mots.position = i;
                if (strlen(mots.chaine)<30)
                {
                    char *p = mots.chaine + strlen(mots.chaine);
                    *p++ = c;
                    *p = '\0';
                }
            }
            else
            {
                if (strlen(mots.chaine)>0)
                {
                    if (estPresent(racine, mots.chaine))
                        printf("*\n");
                    else
                    {
                        printf("& %s ",mots.chaine);
                        rechercheMot(racine, mots,2);
                    }
                    strcpy(mots.chaine,"");
                }                
            }
            i++;
        }

        if (strlen(mots.chaine)>0)
        {
            if (estPresent(racine, mots.chaine))
                printf("*\n");
            else
            {
                printf("& %s ",mots.chaine);
                rechercheMot(racine, mots,2);
            }
            strcpy(mots.chaine,"");
        }

        libererDico(racine);
    }
    return 0;
}
