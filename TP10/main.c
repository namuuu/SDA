////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prod.h"
#include "util.h"


int main() {
    // Création d'un fichier d'un seul int nommé nextFact et contenant l'int 1
    // code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 

    
    // FILE *fileFact = NULL;
	// int size = 1;
    // fileFact = fopen("nextFact.txt","w");
    // fwrite(&size, 1, sizeof(int), fileFact);
    // fclose(fileFact);

    //PARTIE 1 du TP : sans Gestion de stock
    //lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	printf("%d", convertStringIntoInt("145"));

    //PARTIE 2 du TP : avec Gestion de stock
    //copiez coller votre travail précédent puis modifiez le  
    //lireLesCommandes2(); 	

    return 0;
}

void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
    FILE * ficCommande = NULL;
    int flag = 0;
    int NbCommande = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
    char NbCommandeChar[5];
    char nomCommande[29];

    do // Ce do while prend fin dès que fichier commandeXXXX.txt est absent 
    {
		
        strcpy(nomCommande, "./commandes/commande");
        convertIntIntoChar(NbCommande, NbCommandeChar);
        //printf("\n==>%s<==",NNNN);
        ficCommande = NULL;
        strcat(nomCommande, NbCommandeChar);
        strcat(nomCommande, ".txt");

        printf("\n traitement de  %s",nomCommande);

        ficCommande = fopen(nomCommande, "rt");
        if (ficCommande != NULL) { // le fichier commandeNNNN.txt existe
            printf("\n fichier %s present", nomCommande);
            lireCommande(nomCommande); // à vous de coder cette fonction lors de ce TP9
            fclose(ficCommande);
        } else {
            printf("\n Toutes les commandes presentes ont ete traitées.");
            FILE * fileFact = fopen("nextFact", "w"); // on va ecrire la valeur de N dans nextFact 
            // pour 
            fwrite(&NbCommande, 1, sizeof(int), fileFact);
            fclose(fileFact);
            flag = 1;
        }

        NbCommande++;
    } while (flag == 0);

}

int lireProchaineCommande() { //pour lire l'int contenu dans nextFact
    FILE * file;
    int Nb;
    file = fopen("nextFact", "r");
    fread( &Nb, sizeof(int), 1, file);
    fclose(file);
    //printf("\n--->lu N=%d",N);
    return Nb;
}

void lireCommande(char * nomCommande) {
	FILE * fileCommande;
	fileCommande = fopen(nomCommande, "r");

	fclose(fileCommande);
}

void lireProduits() {
	FILE * fileProducts;
	fileProducts = fopen("produits.txt", "r");

	char line[PROD_SIZE];

	while (fgets(line, PROD_SIZE, fileProducts) != NULL) {
		T_Produit produit;
		char * strToken = strtok(line, " ");
		
		strToken = strtok(NULL, " ");
	}
}