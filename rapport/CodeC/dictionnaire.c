/**
 * \file dictionnaire.c
 * \brief dictionnaire.c de l'itispell.
 * \author Romain Petitalot
 * \version 2.0
 * \date 03/01/2022
 *
 * Programme permet de créer, sauvegarder et charger un dictionnaire
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionnaire.h"

/**
 * \brief Fonction qui renvoie le minimum entre 2 entiers
 *
 * \param[in] a  premier entier
 * \param[in] b  deuxième entier
 * \return Le minimum entre 2 entiers
 */
int min(int a, int b)
{
    if (a<b)
        return a;
    return b;
}

/**
 * \brief Fonction qui renvoie le maximum entre 2 entiers
 *
 * \param[in] a  premier entier
 * \param[in] b  deuxième entier
 * \return Le maximum entre 2 entiers
 */
int max(int a, int b)
{ 
    if (a>b)
        return a;
    return b;
}

/**
 * \brief Fonction qui renvoie le minimum entre 3 entiers
 *
 * \param[in] a  premier entier
 * \param[in] b  deuxième entier
 * \param[in] c  troisième entier
 * \return Le minimum entre 3 entiers
 */
int min3(int a, int b,int c)
{ 
    return min(a,min(b,c));
}


/**
 * \brief Fonction qui renvoie la distance de Damerau-Levenshtein entre 2 chaines de caractères
 *
 * \param[in] chaine1  première chaine
 * \param[in] chaine2  deuxième chaine
 * \return La distance
 */
int lev(char chaine1[],char chaine2[])
{
    int taille_s1 = strlen(chaine1);
    int taille_s2 = strlen(chaine2);
    
    int mat[taille_s1+1][taille_s2+1];
    int i=0;
    int j=0;
    int coutSubstitution=0;
    
    for (i=0;i<=taille_s1;i++)
    {
        for (j=0;j<=taille_s2;j++)
            mat[i][j] = 0;
    }
    
    for (i=0;i<=taille_s1;i++)
        mat[i][0] = i;
  
    for (i=0;i<=taille_s2;i++)
        mat[0][i] = i;
   
    for (i=1;i<=taille_s1;i++)
    {
        for (j=1;j<=taille_s2;j++)
        {
            if (chaine1[i-1] == chaine2[j-1])
                coutSubstitution = 0;
            else
                coutSubstitution = 1;

            mat[i][j] =  min3(mat[i-1][j]+1, mat[i-1][j-1]+coutSubstitution, mat[i][j-1]+1);
            
            if (i>1 && j>1 && chaine1[i-1]==chaine2[j-2] && chaine1[i-2]==chaine2[j-1])            
                mat[i][j] = min(mat[i][j] , mat[i-2][j-2]+coutSubstitution);
        }
    }
    return mat[taille_s1][taille_s2];
}


/**
 * \brief Procédure qui initialise la chaine et les enfants d'un noeud
 *
 * \param[in/out] noeud  Le noeud qu'on initialise 
 * \param[in] chaine La chaine qu'on va stocker dans le noeud
 */
void initialiserNoeud(Noeud **noeud, char *chaine) 
{
	int i = 0;
	strcpy((*noeud)->chaine, chaine);
	for(i = 0; i < maxEnfants; i++)
  		(*noeud)->enfants[i] = NULL;
}

/**
 * \brief Procédure qui insère une chaine de caractères dans le dictionnaire
 *
 * \param[in] chaine  La chaine qu'on insère
 * \param[in/out] noeud  Le noeud qu'on modifié
 */
void inserer(char *chaine, Noeud **noeud) 
{
	if(*noeud == NULL) 
    {
  		*noeud = (Noeud *)malloc(sizeof(Noeud));
  		initialiserNoeud(noeud, chaine);
  		return;
	}
	int ld = lev((*noeud)->chaine, chaine);
	inserer(chaine, &((*noeud)->enfants[ld]));
}


/**
 * \brief Procédure qui créé un Dictionnaire à partir d'un fichier texte
 *
 * \param[in/out] noeud  La racine du dictionnaire
 * \param[in] filename  Le nom du fichier texte
 */
void creerDico(Noeud **noeud, char *filename)
{
    FILE * fp;
    fp = fopen(filename, "r");
    char chaine[30];
    while(fscanf(fp,"%s",chaine) != EOF)
        inserer(chaine, noeud);
    fclose(fp);
}


/**
 * \brief Procédure qui un noeud du dictionnaire
 *
 * \param[in/out] noeud  Le noeud qui va stocker la chaine de caractère
 * \param[in] fichier  Le fichier texte qui stocke le dictionnaire préalablement enregistré
 */
void lireDicoRecur(Noeud **noeud, FILE *fichier)
{
    char *mot;
    size_t n = 0;
    char c;
    int i =0;
    mot = malloc(30*sizeof(char));

    while (( c = (char) fgetc(fichier)) != EOF )
    {
        if (c == ' ' )
        {
            mot[n] = '\0';
            if (strcmp(mot,"#")>0)
            {
                if(*noeud == NULL) 
                {
                    *noeud = (Noeud *)malloc(sizeof(Noeud));
                    initialiserNoeud(noeud, mot);
                    free(mot);
                }
                for (i =0; i< maxEnfants; i++)
                    lireDicoRecur(&((*noeud)->enfants[i]),fichier);
                return;
            }
            else
            {
                free(mot);
                return;
            }   
        }
        else
            mot[n++] = c;    
    } 
}


/**
 * \brief Procédure qui commence la lecture du dictionnaire à partir d'un fichier texte où a été enregistré préalablement le dictionnaire 
 *
 * \param[in] noeud  La racine du dictionnaire
 * \param[in] filename Le nom du fichier texte
 */
void lireDico(Noeud **noeud, char *filename)
{
    FILE* fichier = NULL;
    fichier = fopen(filename, "r");

    if (fichier != NULL)
        lireDicoRecur(noeud, fichier);
    fclose(fichier);
}



/**
 * \brief Procédure qui sauvergarde un noeud dans un fichier texte
 *
 * \param[in] noeud  Le noeud qu'on va sauvegarder
 * \param[in/out] fichier  Le fichier texte qui stocke le noeud
 */
void sauvegarderDicoRecur(Noeud *noeud, FILE *fichier)
{ 
    if (noeud==NULL)
        fprintf(fichier, "# ");           
    else
    {
    	int i = 0;
        fprintf(fichier, "%s ", noeud->chaine);
        for (i = 0; i < maxEnfants; i++)
            sauvegarderDicoRecur(noeud->enfants[i], fichier);    
    }
}


/**
 * \brief Procédure qui commence la sauvegarde du dictionnaire préalablement créé
 *
 * \param[in] noeud  La racine du dictionnaire qu'on va sauvegarder
 * \param[in] filename  Le nom de fichier qui va servir de sauvegarde
 */
void sauvegarderDico(Noeud *noeud, char *filename)
{
    FILE* fichier = NULL;
    fichier = fopen(filename, "w");
 
    if (fichier != NULL)
        sauvegarderDicoRecur(noeud, fichier);
    fclose(fichier);
}


/**
 * \brief Procédure qui libère un noeud
 *
 * \param[in] noeud  Le noeud qu'on va libérer
 */
void libererDicoRecur(Noeud *noeud)
{
    if (noeud!=NULL)
    {
    	int i = 0;
        for (i=0; i<maxEnfants; i++)
            libererDicoRecur(noeud->enfants[i]);
        free(noeud);
    }
}


/**
 * \brief Procédure qui libère le dictionnaire qu'on a alloué dynamiquement
 *
 * \param[in] noeud  La racine du dictionnaire qu'on va libérer
 */
void libererDico(Noeud *noeud)
{
    libererDicoRecur(noeud);
}
