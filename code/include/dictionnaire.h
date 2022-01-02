#ifndef __DICTIONNAIRE__
#define __DICTIONNAIRE__

#define maxEnfants 30

typedef struct Noeud Noeud;
struct Noeud 
{ 
	char chaine[maxEnfants];
	struct Noeud *enfants[maxEnfants];
};

int min(int a, int b);

int min3(int a, int b, int c);

int max(int a, int b);

int lev(char chaine1[],char chaine2[]);

void initialiserNoeud(Noeud **node, char *chaine);

void inserer(char *chaine, Noeud **node) ;

void creerDico(Noeud **node, char *filename);

void lireDico(Noeud **node,char *filename);

void sauvegarderDico(Noeud *node, char *filename);

void libererDico(Noeud *node);


#endif


