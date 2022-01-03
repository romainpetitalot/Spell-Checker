#include "mot.h"
#include "dictionnaire.h"

#ifndef __CORRECTEUR__
#define __CORRECTEUR__

void rechercheMot(Noeud *noeud, Mot mot, int toleranceMax);

int estPresent(Noeud *noeud, char *chaine);


#endif

