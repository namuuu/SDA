// SDA1 TP 9 PILE de TAD (PILE d'ELEMENT)

#include "file.h"
#include "permut.h"

void testPile(T_Pile *pile);
void testfile(T_File * file);
void permut(T_Pile *pile, char *chaine);
void echiquier(T_Pile *pile, int taille);

int menu() {

  int choix;
  printf("\n\n\n SDA1 TP9");
  printf("\n\n\n 1 : Tester mon fichier pile.c");
  printf("\n 2 : Tester mon fichier file.c");
  printf("\n 3 : Afficher et compter les permutations d'une chaine");
  printf("\n 4 : Afficher et compter les solutions pour un échiquier ");
  printf("\n\t\t 0 :  QUITTER  \n");
  printf("\n Votre choix: ");
  scanf("%d", & choix);
  return choix;
}

int main() {
  T_File file;
  T_Pile pile;
  int chx;
  int taille;
  char chaine[20];

  do {
    chx = menu();
    switch (chx) {
    case 1:
      // Testez toutes vos fonctions par un jeu de test de votre choix
      testPile(&pile);
      break;
    case 2: //testez toutes vos fonctions par un jeu de test de votre choix
	  testfile(&file);
      break;
    case 3:
	  printf("Veuillez saisir la chaine à permuter : ");
      scanf("%s",chaine); //une chaine de longueur <=MAX
      permut(&pile,chaine); //TP9 partie 2: ecrire permut
      break;
    case 4:
      scanf("%d",&taille);//taille echiquier <=MAX
      echiquier(&pile,taille); //TP9 partie 3: ecrire echiquier
      break;

    }
  } while (chx != 0);

  printf("\nProgramme terminé !\n");
  return 0;
}


void testPile(T_Pile *pile) {

	int choix;
	T_Elt elt;
	
	while (choix != 0)
	{
		printf("\n\n\n Test Pile\n");
		printf("\n 1 : initPile");
		printf("\n 2 : pilePleine");
		printf("\n 3 : pileVide");
		printf("\n 4 : empiler");
		printf("\n 5 : depiler");
		printf("\n 6 : sommet");
		printf("\n 7 : hauteur");
		printf("\n 8 : afficherPile");
		printf("\n\t\t 0 :  QUITTER  \n");
		printf("\n Quel est votre choix ? ");
		scanf("%d", &choix);

		switch (choix)
		{
		case 1:
			initPile(pile);
			break;
		case 2:
			if(pilepleine(pile)) {
				printf("\nINFO > La pile est effectivement pleine !\n");
			} else {
				printf("\nINFO > La pile n'est pas pleine.");
			}
			getchar();
			break;
		case 3:
			if(pilevide(pile)) {
				printf("\nINFO > La pile est effectivement vide !\n");
			} else {
				printf("\nINFO > La pile n'est pas vide.");
			}
			getchar();
			break;
		case 4:
			printf("Quel élément souhaitez-vous ajouter (int) : ");
			saisirElt(&elt);

			empiler(pile, elt);
			printf("Élément empilé ! Celui-ci était : ");
			afficherElt(&elt);
			break;
		case 5:
			depiler(pile, &elt);
			printf("Élément dépilé ! Celui-ci était : ");
			afficherElt(&elt);
			break;
		case 6:
			if(pilevide(pile)) {
				printf("La pile est vide !");
				break;
			}
			elt = sommet(pile);
			printf("Le sommet est : ");
			afficherElt(&elt);
			break;
		case 7:
			int haut = hauteur(pile);
			printf("La hauteur est : ");
			afficherElt(&haut);
			break;
		case 8:
			afficherPile(pile);
			getchar();
			break;
		case 0:
		default:
			break;
		}
	}

}

void testfile(T_File * file) {
    int choix;
    T_Elt elt;
    initFile(file);
    while (choix != 0) {
        printf("\n\n\n Test File\n");
        printf("\n 1 : initFile");
        printf("\n 2 : FilePleine");
        printf("\n 3 : FileVide");
        printf("\n 4 : emfiler");
        printf("\n 5 : defiler");
        printf("\n 6 : premier");
        printf("\n 7 : afficherfile");
        printf("\n\t\t 0 :  QUITTER  \n");
        printf("\n Quel est votre choix ? ");
        scanf("%d", & choix);

        switch (choix) {
        case 1:
            initFile(file);
            break;
        case 2:
            if (filePleine(file)) {
                printf("\nINFO > La file est effectivement pleine !\n");
            } else {
                printf("\nINFO > La file n'est pas pleine.");
            }
            getchar();
            break;
        case 3:
            if (fileVide(file)) {
                printf("\nINFO > La file est effectivement vide !\n");
            } else {
                printf("\nINFO > La file n'est pas vide.");
            }
            getchar();
            break;
        case 4:
            printf("Quel élément souhaitez-vous ajouter (int) : ");
            saisirElt( & elt);

            if (ajouter(file, & elt) == 1) {
                printf("Élément enfilé ! Celui-ci était : ");
                afficherElt( & elt);
            } else {
                printf("Élément non enfilé !  ");
            }

            break;
        case 5:
            retirer(file, & elt);
            printf("Élément defilé  ");

            break;
        case 6:
            if (!premier(file)) {
                printf("La file est vide !");
                break;
            }

            break;
        case 7:
            afficherFile(file);
            break;
        case 0:
        default:
            break;
        }
    }
}

void permut(T_Pile *pile, char *chaine) {
	int taille = strlen(chaine);
	int nbPermu = 0;

	printf("\t");

	initPile(pile);

	do {
		while (noeudValide(pile))
		{
			if(noeudTerminal(pile, taille)) {
				// C'est un noeud terminal, la solution est donc correcte ! L'imprimer
				afficherSolution(pile, chaine);
				nbPermu++;
				goto noeudDeux;
			} else {
				passerAuPremierFils(pile, 1);
			}
		}

		noeudDeux:
		// Passer à la zone suivante à vérifier
		while (!rechercheTerminee(pile) && naPlusDeFrere(pile, taille)) 
		{
			remonterAuPere(pile);
		}
		if (!rechercheTerminee(pile))
		{
			passerAuFrereSuivant(pile, &(pile->Elts[pile->nbElts]));
		}
			
		
	} while(!rechercheTerminee(pile));

	printf("\nIl y a %d permutations.\n", nbPermu);
	
}	

void echiquier(T_Pile *pile, int taille) {
	initPile(pile);

	do {
		while (noeudValide(pile))
		{
			if(noeudTerminal(pile, taille)) {
				// C'est un noeud terminal, c'est une position possible, hormis les diagonales.
				verifierReine(pile);
				goto noeudDeux;
			} else {
				passerAuPremierFils(pile, 1);
			}
		}

		noeudDeux:
		// Passer à la zone suivante à vérifier
		while (!rechercheTerminee(pile) && naPlusDeFrere(pile, taille)) 
		{
			remonterAuPere(pile);
		}
		if (!rechercheTerminee(pile))
		{
			passerAuFrereSuivant(pile, &(pile->Elts[pile->nbElts]));
		}
			
		
	} while(!rechercheTerminee(pile));
	
}	

