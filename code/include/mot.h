#ifndef __MOT__
#define __MOT__

typedef struct Mot Mot;
struct Mot
{
    char chaine[30];
    int position;
};

void lire(char *chaine, int longueur);

void transformeAccentPourAffichage(char motInitial[], const char insert, int pos);

char *transformeAccentPourLev(char* mot);

#endif


