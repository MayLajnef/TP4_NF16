#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main() {

    T_Arbre abr = NULL;
    /*
    T_Sommet* sommet = creerSommet(8);
    printSommet(sommet);
    abr = insererElement(abr, 7);
    abr = insererElement(abr, 6);
    abr = insererElement(abr, 1);
    afficherSommets(abr);
    */
    
    while (1) {
        printf("1. Inserer N elements \n");
        printf("2. Rechercher un element \n");
        printf("3. Afficher tous les sommets \n");
        printf("4. Afficher tous les elements \n");
        printf("5. Supprimer un element \n");
        printf("6. Afficher la taille en memoire \n");
        printf("7. Quitter \n");
        printf("Veuillez saisir une option du menu (entre 1 et 7) :\n");
        int input;
        scanf("%d", &input);
        switch (input) {
            case 1:
                int N, element;
                printf("Insertion de N elements...\n");
                printf("Combien d'elements voulez-vous inserer dans l'ABR ?\n");
                scanf("%d", &N);
                for (int i = 1; i <= N; i++)
                {
                    printf("\nVeuillez saisir l'element n°%d a inserer :\n", i);
                    scanf("%d", &element);
                    while (getchar() != '\n');
                    abr = insererElement(abr, element);
                }
                break;
            case 2:
                break;
            case 3:
                printf("Affichage de tous les sommets...\n");
                if (abr)
                    afficherSommets(abr);
                else
                    printf("L'ABR est vide.\n");
                break;
            case 4:
                printf("Affichage de tous les elements...\n");
                if (abr)
                {
                    afficherElements(abr);
                    printf("\n");
                }
                else
                    printf("L'ABR est vide.\n");
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
    

    return 0;
}
