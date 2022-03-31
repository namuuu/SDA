#include "file.h"

// Fonction qui sert à initialiser la file à -1
void initFile(T_File * ptrF) //mettre Tete et Queue à -1
{
  ptrF -> Tete = -1;
  ptrF -> Queue = -1;
}

// fonction retirer un élément dans la file 
/*il y a 3 conditions:
  tete vaut queue
  tete vaut max-1
  le reste
*/
int retirer(T_File * ptrF, T_Elt * ptrE) //si pas vide, en tete de file
{
  if (!fileVide(ptrF)) {
    affecterElt(ptrE, & (ptrF -> Elts[ptrF -> Tete]));
    if (ptrF -> Tete == ptrF -> Queue) {
      initFile(ptrF);
    } else if (ptrF -> Tete == MAX - 1) {
      ptrF -> Tete = 0;
    } else {
      ptrF -> Tete = ptrF -> Tete + 1;
    }
    return 1;
  }
  return 0;
}
/*fonction pour rajouter un element dans la file
il y a 2 cas : quand on arrive au début de la file et que la file n'est pas pleine .on remet Queue à 0 
Et le reste Ou on met queue à + 1*/
int ajouter(T_File * ptrF, T_Elt * ptrE) // si espace libre, ajout en queue
{
  if (!filePleine(ptrF)) {
    if (ptrF -> Queue == MAX - 1) {
      ptrF -> Queue = 0;
    } else {
      ptrF -> Queue = ptrF -> Queue + 1;
    }
    affecterElt( & (ptrF -> Elts[ptrF -> Queue]), ptrE);
    return 1;
  }
  return 0;
}
/* Fonction pour verifier si la file est vide 
Pour que la file est vide il faut que queue vaut -1*/
int fileVide(const T_File * prtF) // qd Tete == 0 
{
  return (prtF -> Queue == -1);
}
/* fonction pour verifier si la file est pleine pour cela nous avons décider que si tete vaut - et queue vaut max-1 ou que queue vaut tete dans le cas ou queue et tete est different de -1
 */
int filePleine(const T_File * ptrF) // qd MAX elts dans la file 
{
  return ((ptrF -> Tete == -1 && ptrF -> Queue == MAX - 1) || (ptrF -> Queue == ptrF -> Tete && (ptrF -> Tete != -1 && ptrF -> Queue != -1)));

}
/* Cette fonction affiche la premiere valeur de la file */
T_Elt premier(T_File * ptrF) //valeur en tete de file
{
  if (fileVide(ptrF) == 0) {
    afficherElt( & (ptrF -> Elts[ptrF -> Tete + 1]));
    return 1;
  }
  return 0;
}
/* Cette fonction affiche la file affiche dans 3 cas differents l'un si la file est vide et l'autre si la tete est plus petite que la queue et l'inverse */
void afficherFile(T_File * ptrF) {
  if (fileVide(ptrF)) {} else if (ptrF -> Tete < ptrF -> Queue) {
    for (int i = ptrF -> Tete + 1; i <= ptrF -> Queue; i++) {
      afficherElt( & (ptrF -> Elts[i]));
    }
  } else {
    for (int i = 0; i <= ptrF -> Queue; i++) {
      afficherElt( & (ptrF -> Elts[i]));
    }
    for (int i = ptrF -> Tete + 1; i < MAX; i++) {
      afficherElt( & (ptrF -> Elts[i]));
    }

  }
}

