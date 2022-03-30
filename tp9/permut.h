#include "es.h"
#include "pile.h"
#include <stdlib.h>

int passerAuPremierFils(T_Pile * pile, T_Elt elt);

int remonterAuPere(T_Pile * pile);

int passerAuFrereSuivant(T_Pile * pile, T_Elt * elt);

// Vérifie si le dernier élément a un frère
int naPlusDeFrere(T_Pile * pile, int taille);

// Vérifie qu'il n'y ait pas deux fois le même caractère dans une seule et même chaîne.
int noeudValide(T_Pile * pile);

// Vérifie si la longueur du noeud est égale à la longueur de la chaîne initiale
int noeudTerminal(T_Pile * pile, int taille);

int rechercheTerminee(T_Pile * pile);

void afficherSolution(T_Pile * pile, char * chaine);

void verifierReine(T_Pile * pile);