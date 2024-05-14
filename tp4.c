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
    printf("S = [%d, %d]\n", sommet->borneInf, sommet->borneSup);
}

T_Arbre insererElement(T_Arbre abr, int element)
{
    if (abr == NULL) {
        return creerSommet(element);
    }

    // Fusionner avec un intervalle existant si possible
    if (element >= abr->borneInf - 1 && element <= abr->borneSup + 1) {
        abr->borneInf = (element < abr->borneInf) ? element : abr->borneInf;
        abr->borneSup = (element > abr->borneSup) ? element : abr->borneSup;

        // Vérifier la fusion avec les fils
        if (abr->filsGauche && abr->borneInf == abr->filsGauche->borneSup + 1) {
            abr->borneInf = abr->filsGauche->borneInf;
            T_Sommet *tmp = abr->filsGauche;
            abr->filsGauche = tmp->filsGauche;
            free(tmp);
        }
        if (abr->filsDroit && abr->borneSup == abr->filsDroit->borneInf - 1) {
            abr->borneSup = abr->filsDroit->borneSup;
            T_Sommet *tmp = abr->filsDroit;
            abr->filsDroit = tmp->filsDroit;
            free(tmp);
        }
    } else if (element < abr->borneInf) {
        abr->filsGauche = insererElement(abr->filsGauche, element);
    } else {
        abr->filsDroit = insererElement(abr->filsDroit, element);
    }

    return abr;
}

T_Sommet *rechercherElement(T_Arbre abr, int element) 
{
    if (!abr)
        return NULL;
    else if (element >= abr->borneInf && element <= abr->borneSup)
        return abr;
    else if (element < abr->borneInf-1)
        return rechercherElement(abr->filsGauche, element);
    else 
        return rechercherElement(abr->filsDroit, element);
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

void afficherElements(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherElements(abr->filsGauche);
        
        for (int i=abr->borneInf; i <=abr->borneSup; i++)
        {
            printf("%d\t", i);
        }

        afficherElements(abr->filsDroit);
    }
}
/*
void tailleMemoire(T_Arbre abr)
{
    if (abr == NULL)
        printf("L'ABR est vide !\n");
    while (abr != NULL)
    {

    }
}
*/

void libererAbr(T_Arbre abr)
{
    if (abr != NULL)
    {
        libererAbr(abr->filsGauche);
        libererAbr(abr->filsDroit);
        free(abr);
    }
}