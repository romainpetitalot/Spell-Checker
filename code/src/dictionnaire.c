#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionnaire.h"


int min(int a, int b)
{
    if (a<b)
        return a;
    return b;
}

int max(int a, int b)
{ 
    if (a>b)
        return a;
    return b;
}

int min3(int a, int b,int c)
{ 
    return min(a,min(b,c));
}

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



void initialiserNoeud(Noeud **node, char *chaine) 
{
	int i = 0;
	strcpy((*node)->chaine, chaine);
	for(i = 0; i < maxEnfants; i++)
  		(*node)->enfants[i] = NULL;
}


void inserer(char *chaine, Noeud **node) 
{
	if(*node == NULL) 
    {
  		*node = (Noeud *)malloc(sizeof(Noeud));
  		initialiserNoeud(node, chaine);
  		return;
	}
	int ld = lev((*node)->chaine, chaine);
	inserer(chaine, &((*node)->enfants[ld]));
}

void creerDico(Noeud **node, char *filename)
{
    FILE * fp;
    fp = fopen(filename, "r");
    char word[30];
    while(fscanf(fp,"%s",word) != EOF)
        inserer(word, node);
    fclose(fp);
}

void lireDicoRecur(Noeud **node, FILE *fichier)
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
                if(*node == NULL) 
                {
                    *node = (Noeud *)malloc(sizeof(Noeud));
                    initialiserNoeud(node, mot);
                    free(mot);
                }
                for (i =0; i< maxEnfants; i++)
                    lireDicoRecur(&((*node)->enfants[i]),fichier);
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

void lireDico(Noeud **node, char *filename)
{
    FILE* fichier = NULL;
    fichier = fopen(filename, "r");

    if (fichier != NULL)
        lireDicoRecur(node, fichier);
    fclose(fichier);
}


void sauvegarderDicoRecur(Noeud *node, FILE *fichier)
{ 
    if (node==NULL)
        fprintf(fichier, "# ");           
    else
    {
    	int i = 0;
        fprintf(fichier, "%s ", node->chaine);
        for (i = 0; i < maxEnfants; i++)
            sauvegarderDicoRecur(node->enfants[i], fichier);    
    }
}

void sauvegarderDico(Noeud *node, char *filename)
{
    FILE* fichier = NULL;
    fichier = fopen(filename, "w");
 
    if (fichier != NULL)
        sauvegarderDicoRecur(node, fichier);
    fclose(fichier);
}


void libererDicoRecur(Noeud *node)
{
    if (node!=NULL)
    {
    	int i = 0;
        for (i=0; i<maxEnfants; i++)
            libererDicoRecur(node->enfants[i]);
        free(node);
    }
}

void libererDico(Noeud *node)
{
    libererDicoRecur(node);
}
