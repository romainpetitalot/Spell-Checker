/**
 * \file correcteur.c
 * \brief correcteur.c de l'itispell.
 * \author Romain Petitalot
 * \version 2.0
 * \date 03/01/2022
 *
 * Programme qui permet de recherche si un mot est présent et de chercher des correspondances dans le cas contraire
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "correcteur.h"

/**
 * \brief Procédure qui recherche des correspondances avec la chaine donnée
 *
 * \param[in] noeud  Noeud dans lequel on cherche
 * \param[in] chaine  chaine qu'on cherche à corriger
 * \param[in] tolerance  La tolerance d'opération entre les 2 chaines de caractères qu'on va comparer
 * \param[in] counter  Le nombre de résultat qu'on a déjà trouver
 * \param[in/out] res  La chaine dans laquelle on stocke les résultats
 * 
 */
void rechercheMotRecur(Noeud *noeud, char *chaine, int tolerance, int *counter, char *res) 
{
    if (noeud == NULL)
        return;
    int j = lev(noeud->chaine, chaine);
    if ((j==tolerance)&&(*counter <(6+tolerance*4)) &&  (strlen(res)+strlen(noeud->chaine)<99))
    {
        if (tolerance>0)
        {
            char *bonMot = (char *)malloc(sizeof(noeud->chaine));
            strcpy(bonMot, noeud->chaine);
            int longueurMot = strlen(bonMot);
            for (int i = 0; i<longueurMot; i++)
            {
                if (bonMot[i]<0 && bonMot[i]>-33)
                {
                    int ancienneVal = bonMot[i];
                    bonMot[i++] = -61;
                    transformeAccentPourAffichage(bonMot,ancienneVal-64,i);
                    longueurMot++;    
                }
            }
            strcat(res, bonMot);
            strcat(res, " ");
            free(bonMot);
        }
        int oldval = *counter;
        *counter = oldval + 1;
    }
    if (*counter <(6+tolerance*4))
    {
    	int i = 0;
        for (i = max(0, j - tolerance); i< min(maxEnfants, j+tolerance + 1); i++)
            rechercheMotRecur(noeud->enfants[i], chaine, tolerance, counter, res);
    }
}

/**
 * \brief Procédure qui initialise la recherche pour un mot donné
 *
 * \param[in] noeud  Noeud dans lequel on commence à chercher
 * \param[in] mot  Mot qu'on cherche à corriger
 * \param[in] toleranceMax  La tolerance maximale d'opération
 * 
 */
void rechercheMot(Noeud *noeud, Mot mot, int toleranceMax)
{
    int tolerance = 1;
    int counter = 0;
    int i = 0;

    char *motAccentue=transformeAccentPourLev(mot.chaine);
    
    for (i = 1; i<strlen(motAccentue); i++)
    {
        if (motAccentue[i]>='A' && motAccentue[i]<='Z')
            motAccentue[i] += 32;
    }

    char res[101]={0};
    do
    {
        rechercheMotRecur(noeud, motAccentue, tolerance, &counter, res);
        tolerance ++;
    }
    while ((tolerance<= toleranceMax) && (counter < 14));
    if (counter==0)
    {
        counter = 15;
        rechercheMotRecur(noeud, motAccentue, 3, &counter, res); 
        counter -= 15;
    }
    printf("%d %d: %s\n",counter, mot.position, res);

    free(motAccentue);
}


/**
 * \brief Fonction qui recherche si un mot est présent dans le dictionnaire
 *
 * \param[in] noeud  Noeud dans lequel on commence à chercher
 * \param[in] mot  Mot qu'on cherche à prouver la présence
 * \return Vrai si le mot est présent sinon Faux
 */
int estPresent(Noeud *noeud, char *chaine)
{
    char *motAccentue=transformeAccentPourLev(chaine);

    int i = 0;
    for (i = 0; i<strlen(motAccentue); i++)
    {
        if (motAccentue[i]>='A' && motAccentue[i]<='Z')
            motAccentue[i] += 32;
    }

    char res[101]={0};

    int counter = 0;
    rechercheMotRecur(noeud, motAccentue, 0, &counter, res);
    free(motAccentue);
    return (counter == 1);
}
