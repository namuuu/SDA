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

// Vérifie si le noeud est de taille maximale
int noeudTerminal(char noeud[], char chaine[]) {
    return (strlen(noeud) == strlen(chaine)); 
}

int rechercheTerminee(T_Pile * pile) {
    return 1;
}
