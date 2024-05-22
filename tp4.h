#ifndef TP4_H
#define TP4_H

typedef struct Sommet
{
    int borneInf;
    int borneSup;
    struct Sommet* filsGauche;
    struct Sommet* filsDroit;
}T_Sommet;

typedef T_Sommet* T_Arbre;

int estUnEntier(char input[]);

void printTree(T_Arbre root, int space);

void menu(T_Arbre abr);

T_Sommet *creerSommet(int element);

void printSommet(T_Sommet* sommet);

T_Arbre insererElement(T_Arbre abr, int element);

T_Sommet *rechercherElement(T_Arbre abr, int element);

void afficherSommets(T_Arbre abr);

void afficherElements(T_Arbre abr);

T_Arbre supprimerElement(T_Arbre abr, int element);

void tailleMemoire(T_Arbre abr);

int calculerTailleABR(T_Arbre abr);

int calculerTailleClassique(T_Arbre abr);

void libererAbr(T_Arbre abr);




#endif //TP4_H