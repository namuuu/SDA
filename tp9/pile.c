#include "pile.h"


void initPile(T_Pile * P) {
    P->nbElts = 0;
}

int pilepleine(const T_Pile * P) {
    return (P->nbElts == MAX);
}

int pilevide(const T_Pile * P) {
    return (P->nbElts == 0);
}

int empiler(T_Pile * P, T_Elt e) //renvoie 0 si pile pleine, sinon 1
{
    if(pilepleine(P)) {
        return 0;
    }

    affecterElt(&(P->Elts[P->nbElts]), &e);
    P->nbElts++;

    return 1;
}

int depiler(T_Pile * P, T_Elt * pelt) //renvoie 0 si pile vide, sinon 1
{
    if(pilevide(P)) {
        return 0;
    }

    P->nbElts--;

    *pelt = P->Elts[P->nbElts];

    

    return 1;
}

T_Elt sommet(const T_Pile * P) {


  return P->Elts[P->nbElts-1];
}

int hauteur(const T_Pile * P) {
  return P->nbElts;
}

void afficherPile(T_Pile * P) {
    printf("Pile : \n");
    for(int i = 0; i < P->nbElts; i++) {
        printf("\n[%d] - ", i);
        afficherElt(&(P->Elts[i]));
    }
}