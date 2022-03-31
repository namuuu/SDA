#include "permut.h"




// Vérifie qu'il n'y ait pas deux fois le même caractère dans une seule et même chaîne.
int noeudValide(T_Pile * pile) {
    for(int i = 0; i < hauteur(pile); i++) {
        for(int j = 0; j < hauteur(pile); j++) {
            if(pile->Elts[i] == pile->Elts[j] && i != j) {
                return 0;
            }
        }
    }
    return 1; 
}

int passerAuPremierFils(T_Pile * pile, T_Elt elt) {
    return empiler(pile,elt);
}

int remonterAuPere(T_Pile * pile) {
    T_Elt elt;
    return depiler(pile,&elt);
}

int passerAuFrereSuivant(T_Pile * pile, T_Elt * elt) {
    return(depiler(pile, elt) && empiler(pile, 1+ *elt));
}

int naPlusDeFrere(T_Pile * pile, int taille) {
    return (sommet(pile) == taille);
}

// Vérifie si le noeud est de taille maximale
int noeudTerminal(T_Pile * pile, int taille) {
    return (hauteur(pile) == taille); 
}

int rechercheTerminee(T_Pile * pile) {
    return pilevide(pile);
}

void afficherSolution(T_Pile * pile, char * chaine) {
    for(int i = 0; i < hauteur(pile); i++) {
        printf("%c", chaine[pile->Elts[i]-1]);
    }
    printf("  ");
}

void verifierReine(T_Pile * pile) {
    for(int i = 0; i < hauteur(pile); i++) {
        for(int j = 0; j < hauteur(pile); j++) {
            if(i!=j && abs(pile->Elts[i] - pile->Elts[j]) == abs(i-j)) {
                return;
            }
        }
    }

    printf("Succès pour : %d", pile->Elts[0]);
    for(int i = 1; i < hauteur(pile); i++) {
        printf("-%d", pile->Elts[i]);
    }
    printf("\n");
}
