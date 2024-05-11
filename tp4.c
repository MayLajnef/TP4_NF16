#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

T_Sommet *creerSommet(int element)
{
    T_Sommet* nouveau_sommet = (T_Sommet*) malloc(sizeof(T_Sommet));
    if (nouveau_sommet == NULL)
    {
        printf("Echec de l'allocation memoire\n");
        return NULL;
    }
    nouveau_sommet->borneInf = nouveau_sommet->borneSup = element;
    nouveau_sommet->filsDroit = nouveau_sommet->filsGauche = NULL;
    return nouveau_sommet;
}

void printSommet(T_Sommet* sommet)
{
    printf("Infos du sommet : \n");
    printf("S = [%d, %d]\n", sommet->borneInf, sommet->borneSup);
}

T_Arbre insererElement(T_Arbre abr, int element)
{
    if (abr == NULL)
        return creerSommet(element);
    /*
    if (rechercherElement(abr, element) != NULL)
    {
        printf("L'element existe deja dans l'abr !\n");
        return abr;
    }
    */

    if (element < abr->borneInf)
        abr->filsGauche = insererElement(abr->filsGauche, element);
    else
        abr->filsDroit = insererElement(abr->filsDroit, element);

    // Après insertion, on fusionne les noeuds si nécessaire
    if (abr->filsGauche && abr->borneInf == abr->filsGauche->borneSup + 1) {
        abr->borneInf = abr->filsGauche->borneInf;
        T_Sommet* tmp = abr->filsGauche;
        abr->filsGauche = tmp->filsGauche;
        tmp->filsGauche = NULL;
        free(tmp);
    }
    if (abr->filsDroit && abr->borneSup == abr->filsDroit->borneInf - 1) {
        abr->borneSup = abr->filsDroit->borneSup;
        T_Sommet* tmp = abr->filsDroit;
        abr->filsDroit = tmp->filsDroit;
        tmp->filsDroit = NULL;
        free(tmp);
    }

    return abr;
}

void afficherSommets(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherSommets(abr->filsGauche);
        
        printf("[%d ;%d]\n", abr->borneInf, abr->borneSup);

        afficherSommets(abr->filsDroit);
    }
}