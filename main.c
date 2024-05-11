#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main() {

    T_Arbre abr = NULL;
    /*
    T_Sommet* sommet = creerSommet(8);
    printSommet(sommet);
    */
    abr = insererElement(abr, 7);
    abr = insererElement(abr, 6);
    abr = insererElement(abr, 1);
    afficherSommets(abr);
    /*
    while (1) {
        printf("1. . Inserer N elements \n");
        printf("2. Rechercher un element \n");
        printf("3. Afficher tous les sommets \n");
        printf("4. Afficher tous les elements \n");
        printf("5. Supprimer un element \n");
        printf("6. Afficher la taille en memoire \n");
        printf("7. Quitter \n");
        int input;
        scanf("%d", &input);
        switch (input) {
            case 1:
                printf("Insertion de N elements...\n");
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                libererAbr(abr); 
                exit(1);
            default:
                printf("Option non valide. Veuillez choisir une option entre 1 et 7.\n");
                break;
        }
    }
    */

    return 0;
}
