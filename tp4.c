#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

// Fonction pour vérifier si un utilisateur saisit bien un entier
int saisirEntier() {
    int entier;
    char buffer[100];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &entier) == 1) {
                return entier;
            } else {
                printf("Saisie incorrecte. Veuillez saisir un entier :\n");
            }
        } else {
            printf("Erreur de lecture. Veuillez reessayer :\n");
        }
    }
}

void printTree(T_Arbre root, int space) {
    int COUNT = 5;  // Adjust space between levels
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    printTree(root->filsDroit, space);

    // Print current node after space count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("[%d, %d]\n", root->borneInf, root->borneSup);

    // Process left child
    printTree(root->filsGauche, space);
}

// Fonction pour le menu
void menu(T_Arbre abr) {
    int entier;
    int N, element;

    while (1) {
        printf("1. Inserer N elements \n");
        printf("2. Rechercher un element \n");
        printf("3. Afficher tous les sommets \n");
        printf("4. Afficher tous les elements \n");
        printf("5. Supprimer un element \n");
        printf("6. Afficher la taille en memoire \n");
        printf("7. Quitter \n");
        printf("Veuillez saisir une option du menu (entre 1 et 7) :\n");
        int input = saisirEntier();
        
        switch (input) {
            case 1:
                printf("Insertion de N elements...\n");
                do
                {
                    printf("Combien d'elements voulez-vous inserer dans l'ABR ?\n");
                    N = saisirEntier();
                } while (N <= 0);
                for (int i = 1; i <= N; i++) {
                    printf("\nVeuillez saisir l'element n°%d a inserer :\n", i);
                    element = saisirEntier();
                    abr = insererElement(abr, element);
                }
                printTree(abr, 4);
                break;
            case 2:
                printf("Recherche d'un element dans l'ABR...\n");
                printf("Veuillez saisir l'entier que vous cherchez : ");
                entier = saisirEntier();
                T_Sommet* intervalle_recherche = rechercherElement(abr, entier);
                if (intervalle_recherche) {
                    printf("L'entier recherche est un element de l'intervalle ");
                    printSommet(intervalle_recherche);
                } else {
                    printf("Element introuvable !\n");
                }
                printTree(abr, 4);
                break;
            case 3:
                printf("Affichage de tous les sommets...\n");
                if (abr) {
                    afficherSommets(abr);
                } else {
                    printf("L'ABR est vide.\n");
                }
                break;
            case 4:
                printf("Affichage de tous les elements...\n");
                if (abr) {
                    afficherElements(abr);
                    printf("\n");
                } else {
                    printf("L'ABR est vide.\n");
                }
                break;
            case 5:
                printf("Suppression d'un element...\n");
                printf("Veuillez saisir l'element que vous voulez supprimer : ");
                element = saisirEntier();
                abr = supprimerElement(abr, element);
                break;
            case 6:
                // Implémenter l'affichage de la taille en mémoire ici
                break;
            case 7:
                libererAbr(abr);
                exit(0);
            default:
                printf("Option non valide. Veuillez choisir une option entre 1 et 7.\n");
                break;
        }
    }
}


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

// A REVOIR
T_Arbre supprimerElement(T_Arbre abr, int element)
{
    if (!abr)
        return NULL; // L'élément n'est pas présent dans l'ABR


    if (element < abr->borneInf) // L'élément est dans le sous-arbre gauche
    {
        abr->filsGauche = supprimerElement(abr->filsGauche, element);
    }
    else if (element > abr->borneSup) // L'élément est dans le sous-arbre droit
    {
        abr->filsDroit = supprimerElement(abr->filsDroit, element);
    }
    else
    {
        // On a trouvé l'intervalle qui contient la valeur à supprimer

        if (abr->borneInf == abr->borneSup) // L'intervalle ne contient qu'un seul élément
        {
            // On doit supprimer le noeud en entier de l'ABR

            if (!abr->filsGauche) // Cas 1 : le noeud n'a pas de fils gauche
            {
                T_Sommet* tmp = abr->filsDroit; // Le fils droit devient la nouvelle racine
                free(abr); 
                return tmp;
            }
            else if (!abr->filsDroit) // Cas 2 : le noeud n'a pas de fils droit
            {
                T_Sommet* tmp = abr->filsGauche; // Le fils gauche devient la nouvelle racine
                free(abr);
                return tmp;
            }
            else // Cas 3 : le noeud a deux fils
            {
                // Remplacer le noeud par son successeur
                T_Sommet* successeur = abr->filsDroit;
                while (successeur->filsGauche != NULL)
                    successeur = successeur->filsGauche;

                // Copier les valeurs du successeur dans le noeud courant
                abr->borneInf = successeur->borneInf;
                abr->borneSup = successeur->borneSup;

                // Supprimer le successeur de son emplacement d'origine
                abr->filsDroit = supprimerElement(abr->filsDroit, successeur->borneInf);

            }

            //free(tmp); // Libérer la mémoire du noeud supprimé
        }
        else // L'intervalle contient plusieurs éléments
        {
            if (element == abr->borneInf) // Supprimer le premier élément de l'intervalle
            {
                abr->borneInf++;
            }
            else if (element == abr->borneSup) // Supprimer le dernier élément de l'intervalle
            {
                abr->borneSup--;
            }
            else // L'élément est au milieu, il faut diviser l'intervalle en deux
            {
                T_Sommet* nouveauNoeud = creerSommet(element + 1); // Créer un nouveau noeud pour la partie supérieure
                nouveauNoeud->borneSup = abr->borneSup;
                abr->borneSup = element - 1; // Mettre à jour la borne supérieure du noeud courant
                nouveauNoeud->filsGauche = abr->filsDroit; // Rattacher le sous-arbre droit au nouveau abr
                abr->filsDroit = nouveauNoeud; // Rattacher le nouveau noeud au noeud courant
            }
        }
    }

    return abr;
}

//TO DO
void tailleMemoire(T_Arbre abr)
{

}

void libererAbr(T_Arbre abr)
{
    if (abr != NULL)
    {
        libererAbr(abr->filsGauche);
        libererAbr(abr->filsDroit);
        free(abr);
    }
}