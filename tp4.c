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
void afficherABR(T_Arbre abr, int space) {
    int fg, fd ;
    if (abr == NULL) return;

    if(abr->filsGauche !=NULL )
    {
        fg=abr->filsGauche->borneInf;
        printf("[%d;%d] , fg=%d ; ",abr->borneInf, abr->borneSup, fg);
    }
    else
    {
        char* fg_c= "nil";
        printf("[%d;%d] , fg=%s ; ", abr->borneInf, abr->borneSup, fg_c);
    }
    if (abr->filsDroit != NULL )
    {
        fd=abr->filsDroit->borneInf;
        printf("fd:%d\n", fd);
    }
    else
    {
        char* fd_c= "nil";
        printf("fd:%s\n", fd_c);
    }

    afficherABR(abr->filsGauche, space-5);
    afficherABR(abr->filsDroit, space+5);
}


// Fonction pour le menu
void menu(T_Arbre *abr) {
    int entier;
    int N, element;

    while (1) {
        printf("1. Inserer N elements \n");
        printf("2. Rechercher un element \n");
        printf("3. Afficher tous les sommets \n");
        printf("4. Afficher tous les elements \n");
        printf("5. Supprimer un element \n");
        printf("6. Afficher la taille en memoire \n");
        printf("7. Afficher l'ABR \n");
        printf("8. Quitter \n");
        printf("Veuillez saisir une option du menu (entre 1 et 8) :\n");
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
                    printf("\nVeuillez saisir l'element n%d a inserer :\n", i);
                    element = saisirEntier();
                    abr = insererElement(abr, element);
                }
                break;
            case 2:
                printf("Recherche d'un element dans l'ABR...\n");
                printf("Veuillez saisir l'entier que vous cherchez : ");
                entier = saisirEntier();
                T_Sommet* intervalle_recherche = rechercherElement(abr, entier);
                if (intervalle_recherche) {
                    printf("L'entier recherche est dans l'arbre et est un element de l'intervalle ");
                    printf("S = [%d, %d].\n", intervalle_recherche->borneInf, intervalle_recherche->borneSup);
                } else {
                    printf("Element introuvable !\n");
                }
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
                if (abr) {
                    printf("Veuillez saisir l'element que vous voulez supprimer : ");
                    element = saisirEntier();
                    abr = supprimerElement(abr, element);
                } else {
                    printf("L'ABR est vide.\n");
                }
                afficherABR(abr, 0);
                break;
            case 6:
                printf("Affichage de la taille en memoire...\n");
                tailleMemoire(abr);
                break;
            case 7:
                if (abr){
                    printf("Affichage de l'ABR...\n");
                    afficherABR(abr,0);
                    break;
                } else {
                    printf("L'ABR est vide.\n");
                }
            case 8:
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

T_Arbre insererElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return creerSommet(element);
    }

    if (element < abr->borneInf - 1) {
        abr->filsGauche = insererElement(abr->filsGauche, element);
        // Fusion avec le fils gauche si nécessaire
        if (abr->filsGauche && abr->filsGauche->borneSup + 1 >= abr->borneInf) {
            abr->borneInf = abr->filsGauche->borneInf;
            T_Sommet *tmp = abr->filsGauche;
            abr->filsGauche = tmp->filsGauche;
            free(tmp);
        }
    } else if (element > abr->borneSup + 1) {
        abr->filsDroit = insererElement(abr->filsDroit, element);
        // Fusion avec le fils droit si nécessaire
        if (abr->filsDroit && abr->filsDroit->borneInf - 1 <= abr->borneSup) {
            abr->borneSup = abr->filsDroit->borneSup;
            T_Sommet *tmp = abr->filsDroit;
            abr->filsDroit = tmp->filsDroit;
            free(tmp);
        }
    } else {
        // Élargir l'intervalle du sommet actuel
        abr->borneInf = (element < abr->borneInf) ? element : abr->borneInf;
        abr->borneSup = (element > abr->borneSup) ? element : abr->borneSup;
        // Vérifier la fusion avec les fils après l'élargissement
        if (abr->filsGauche && abr->borneInf <= abr->filsGauche->borneSup + 1) {
            abr->borneInf = abr->filsGauche->borneInf;
            T_Sommet *tmp = abr->filsGauche;
            abr->filsGauche = tmp->filsGauche;
            free(tmp);
        }
        if (abr->filsDroit && abr->borneSup >= abr->filsDroit->borneInf - 1) {
            abr->borneSup = abr->filsDroit->borneSup;
            T_Sommet *tmp = abr->filsDroit;
            abr->filsDroit = tmp->filsDroit;
            free(tmp);
        }
    }
    return abr;
}

T_Sommet *rechercherElement(T_Arbre abr, int element)
{
    T_Sommet *courant = abr;

    if (!courant)
        return NULL;
    else if (element >= courant->borneInf && element <= courant->borneSup)
        return courant;
    else if (element < courant->borneInf-1)
        return rechercherElement(courant->filsGauche, element);
    else
        return rechercherElement(courant->filsDroit, element);
}

void afficherSommets(T_Arbre abr)
{
    T_Sommet *courant = abr;

    if (abr != NULL)
    {
        afficherSommets(courant->filsGauche);

        printf("[%d ;%d]\n", courant->borneInf, courant->borneSup);

        afficherSommets(courant->filsDroit);
    }
}

void afficherElements(T_Arbre abr)
{
    T_Sommet *courant = abr;

    if (courant!= NULL)
    {
        afficherElements(courant->filsGauche);

        for (int i=courant->borneInf; i <=courant->borneSup; i++)
        {
            printf("%d\t", i);
        }

        afficherElements(courant->filsDroit);
    }
}

T_Arbre supprimerElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return NULL;
    }

    if (element < abr->borneInf) {
        // L'élément est dans le sous-arbre gauche
        abr->filsGauche = supprimerElement(abr->filsGauche, element);
    } else if (element > abr->borneSup) {
        // L'élément est dans le sous-arbre droit
        abr->filsDroit = supprimerElement(abr->filsDroit, element);
    } else {
        // On a trouvé l'intervalle qui contient la valeur à supprimer
        if (abr->borneInf == abr->borneSup) {
            // L'intervalle ne contient qu'un seul élément
            // On doit supprimer le noeud en entier de l'ABR
            if (!abr->filsGauche) {
                // Cas 1 : le noeud n'a pas de fils gauche
                T_Sommet* tmp = abr->filsDroit; // Le fils droit devient la nouvelle racine
                free(abr);
                return tmp;
            } else if (!abr->filsDroit) {
                // Cas 2 : le noeud n'a pas de fils droit
                T_Sommet* tmp = abr->filsGauche; // Le fils gauche devient la nouvelle racine
                free(abr);
                return tmp;
            } else {
                // Cas 3 : le noeud a deux fils
                // Remplacer le noeud par son successeur
                T_Sommet* successeur = abr->filsDroit;
                while (successeur->filsGauche != NULL) {
                    successeur = successeur->filsGauche;
                }

                // Copier les valeurs du successeur dans le noeud courant
                abr->borneInf = successeur->borneInf;
                abr->borneSup = successeur->borneSup;

                // Supprimer le successeur de son emplacement d'origine
                abr->filsDroit = supprimerElement(abr->filsDroit, successeur->borneInf);
            }
        } else {
            // L'intervalle contient plusieurs éléments
            if (element == abr->borneInf) {
                // Supprimer le premier élément de l'intervalle
                abr->borneInf++;
            } else if (element == abr->borneSup) {
                // Supprimer le dernier élément de l'intervalle
                abr->borneSup--;
            } else {
                // L'élément est au milieu, il faut diviser l'intervalle en deux
                T_Sommet* nouveauNoeud = creerSommet(element + 1);
                nouveauNoeud->borneSup = abr->borneSup;
                nouveauNoeud->filsDroit = abr->filsDroit;
                abr->borneSup = element - 1;
                abr->filsDroit = nouveauNoeud;
            }
        }
    }

    return abr;
}

void tailleMemoire(T_Arbre abr) {
    int tailleABR = calculerTailleABR(abr); // Calculer la taille de l'ABR actuel
    int tailleClassique = calculerTailleClassique(abr); // Calculer la taille d'un ABR classique
    int gainMemoire = tailleClassique - tailleABR;

    printf("Taille de l'ABR actuel : %d octets\n", tailleABR);
    printf("Taille d'un ABR classique : %d octets\n", tailleClassique);
    printf("Gain de memoire : %d octets\n", gainMemoire);
}

int calculerTailleABR(T_Arbre abr) {
    if (abr == NULL)
        return 0;

    // Taille du sommet actuel
    int tailleSommet = sizeof(T_Sommet);

    // Calcul de la taille des sous-arbres gauche et droit
    int tailleGauche = calculerTailleABR(abr->filsGauche);
    int tailleDroite = calculerTailleABR(abr->filsDroit);

    return tailleSommet + tailleGauche + tailleDroite;
}

int calculerTailleClassique(T_Arbre abr) {
    if (abr == NULL)
        return 0;

    // Nombre d'éléments dans l'intervalle de ce sommet
    int nbElements = abr->borneSup - abr->borneInf + 1;

    // Taille des éléments de ce sommet convertis en nœuds classiques
    int tailleSommet = nbElements * (sizeof(T_Sommet)-4);

    // Calcul de la taille des sous-arbres gauche et droit
    int tailleGauche = calculerTailleClassique(abr->filsGauche);
    int tailleDroite = calculerTailleClassique(abr->filsDroit);

    return tailleSommet + tailleGauche + tailleDroite;
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


