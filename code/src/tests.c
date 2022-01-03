/**
 * \file tests.c
 * \brief Tests unitaires de l'itispell.
 * \author Mohammed Mamoun Ibn-abdeljalil
 * \version 1.0
 * \date 03/01/2022
 *
 * Programme qui permet de réaliser les tests unitaires liés à l'itispell
 *
 */

#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "mot.h"
#include "dictionnaire.h"
#include "correcteur.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}


Noeud *racineCreer = NULL;
Noeud *racineCharger = NULL;

void test_Minimum_Deux_Valeurs(void)
{
	CU_ASSERT_TRUE(min(2,4)==2)
}

void test_Minimum_Trois_Valeurs(void)
{
	CU_ASSERT_TRUE(min3(1,2,3)==1)
}

void test_Maximum(void)
{
	CU_ASSERT_TRUE(max(4,6)==6)
}

void test_Distance1(void)
{
	CU_ASSERT_TRUE(lev("bonjour","bonjoue")==1)
}

void test_Distance2(void)
{
		CU_ASSERT_TRUE(lev("bonjour","bonjoure")==1)
}

void test_Distance3(void)
{
		CU_ASSERT_TRUE(lev("bonjour","bojnour")==1)
}

void test_Distance4(void)
{
		CU_ASSERT_TRUE(lev("bonjour","anticonstitutionellement")==21)
}

void test_Distance5(void)
{
		CU_ASSERT_TRUE(lev("","bonjour")==7)
}

void test_Creation_Dico(void)
{
	Noeud *node = (Noeud *)malloc(sizeof(Noeud));
	Noeud **noeud;
	noeud=&node;
	initialiserNoeud(noeud,"bonjour");
	CU_ASSERT_TRUE(strcmp((*noeud)->chaine,"bonjour")==0);
	libererDico(node);
}
	
void test_Inserer_Mot1(void)
{
	Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
	initialiserNoeud(&noeud,"voix");
	inserer("voie",&noeud);
	int ld = lev("voix","voie");
	CU_ASSERT_TRUE( (strcmp(((noeud)->enfants[ld])->chaine, "voie")==0))
	libererDico(noeud);
}

void test_Inserer_Mot2(void)
{
	Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
	initialiserNoeud(&noeud,"voix");
	int ld1 = lev("voix","voit");
	inserer("voit",&noeud);
	int ld2 = lev("voit","vois");
	inserer("vois",&noeud);
	CU_ASSERT_TRUE( (strcmp(((noeud)->enfants[ld1])->chaine, "voit")==0) && (strcmp((((noeud)->enfants[ld1])->enfants[ld2])->chaine, "vois")==0) )
	libererDico(noeud);
}


void test_Est_Dans_Dico1(void)
{
	Noeud *noeud;
	noeud = NULL;
	CU_ASSERT_TRUE(estPresent(noeud,"bonjour") == 0);
}

void test_Est_Dans_Dico2(void)
{
	Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
	initialiserNoeud(&noeud,"voix");
	inserer("voit",&noeud);
	inserer("vois",&noeud);
	inserer("voler",&noeud);
	CU_ASSERT_TRUE((estPresent(noeud,"voler")) && (estPresent(noeud,"manger") == 0) )
	libererDico(noeud);
}

int test_Dico_Egaux_Recur(Noeud* racine1, Noeud* racine2)
{
	if (racine1==NULL && racine2==NULL)
		return 1;
	else if (strcmp(racine1->chaine, racine2->chaine)>0)
		return 0;
	else
	{
		int i = 0;
		for (i=0; i<maxEnfants; i++)
		{
			if (test_Dico_Egaux_Recur(racine1->enfants[i], racine2->enfants[i])==0)
				return 0;
		}
		return 1;
	}
}

void test_Dico_Egaux(void)
{
	CU_ASSERT_TRUE(test_Dico_Egaux_Recur(racineCreer, racineCharger));
}

void afficherAideTest()
{ //main.c
    printf("Aide des tests unitaires:\n");
    printf("    testUnit -d dico -f fic : pour tester si le dictionnaire créé depuis fic puis sauvegardé dans dico est le même que celui chargé depuis la sauvegarde dico\n");
}


int main(int argc, char** argv)
{
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();


	char optstring[]="d:f:h";
    int c = 0;
    int dflag = 0;
    int fflag = 0;


    char nom_dico[30];
    char nom_fichier[30];
    
    while( (c=getopt (argc, argv, optstring)) != -1 )
    {
        switch(c)
        {
            case 'd':
                dflag = 1;
                strcpy(nom_dico, optarg );
                break;
            case 'f':
                fflag = 1;
                strcpy(nom_fichier, optarg );
                break;
			case 'h':
				afficherAideTest();
                break;
            default:
                afficherAideTest();
                break;
        }    
    } 


    if (fflag)
    {
        if (dflag)
        {
            clock_t t1, t2;
            t1 = clock();
            creerDico(&racineCreer, nom_fichier);
            t2 = clock();;
            double temps = (double)(t2-t1)/CLOCKS_PER_SEC;  
        
            printf( "Création finie en %fs sec\n", temps );  
            t1 = clock();
            sauvegarderDico(racineCreer, nom_dico);
            t2 = clock();
            temps = (double)(t2-t1)/CLOCKS_PER_SEC;  
            printf( "Ecriture finie en %fs sec\n", temps );  
	        t1 = clock(); 
	        lireDico(&racineCharger, nom_dico);
	        t2 = clock(); 
	    
	        temps = (double)(t2-t1)/CLOCKS_PER_SEC;  
	        
	        printf( "Chargement fini en %fs sec\n\n", temps );  
        }    
        else
        {
        	printf("Il faut rentré le nom du dico à créer\n");        
    		afficherAideTest();
        }
            
    }


	pSuite= CU_add_suite("Tests", init_suite_success, clean_suite_success);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite,"test minimum de deux valeurs",test_Minimum_Deux_Valeurs))
		|| (NULL == CU_add_test(pSuite,"test minimum de trois valeurs",test_Minimum_Trois_Valeurs))
		|| (NULL == CU_add_test(pSuite,"test maximum de deux valeurs",test_Maximum))
		|| (NULL == CU_add_test(pSuite,"test Distance 1",test_Distance1))
		|| (NULL == CU_add_test(pSuite,"test Distance 2",test_Distance2))
		|| (NULL == CU_add_test(pSuite,"test Distance 3",test_Distance3))
		|| (NULL == CU_add_test(pSuite,"test Distance 4",test_Distance4))
		|| (NULL == CU_add_test(pSuite,"test Distance 5",test_Distance5))
		|| (NULL == CU_add_test(pSuite,"test creation d'un dico",test_Creation_Dico))
		|| (NULL == CU_add_test(pSuite,"test insertion d'un élément dans un dico 1", test_Inserer_Mot1))
		|| (NULL == CU_add_test(pSuite,"test insertion d'un élément dans un dico 2", test_Inserer_Mot2))
		|| (NULL == CU_add_test(pSuite,"test présence d'un éléments dans un dico 1", test_Est_Dans_Dico1))
		|| (NULL == CU_add_test(pSuite,"test présence d'un éléments dans un dico 2", test_Est_Dans_Dico2))
		|| (NULL == CU_add_test(pSuite,"test dico créé et chargé sont égaux les mêmes", test_Dico_Egaux))
		)
	{
			CU_cleanup_registry();
			return CU_get_error();
		}

		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();
		printf("\n");
		CU_basic_show_failures(CU_get_failure_list());
		printf("\n\n");

		CU_cleanup_registry();
		libererDico(racineCreer);
		libererDico(racineCharger);

		return CU_get_error();
}


