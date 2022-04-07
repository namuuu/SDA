////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "prod.h"
#include "util.h"


int main() {
    // Création d'un fichier d'un seul int nommé nextFact et contenant l'int 1
    // code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 

    
    /*FILE *fileFact = NULL;
	int size = 1;
    fileFact = fopen("nextFact.txt","w");
    fwrite(&size, 1, sizeof(int), fileFact);
    fclose(fileFact);*/


    lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt

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
        printf("\n\n==>%s<==", NbCommandeChar);
        ficCommande = NULL;
        strcat(nomCommande, NbCommandeChar);
        strcat(nomCommande, ".txt");

        printf("\n\tTraitement du fichier %s...",nomCommande);

        ficCommande = fopen(nomCommande, "rt");
        if (ficCommande != NULL) { // le fichier commandeNNNN.txt existe
            printf("\n\tLe fichier %s est présent !\n\tLecture...", nomCommande);
            lireCommande(nomCommande, NbCommandeChar); // à vous de coder cette fonction lors de ce TP9
            fclose(ficCommande);
        } else {
            printf("\n\tFichier non trouvé !\nToutes les commandes présentes ont été traitées.");
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
    return 1;
}

T_Commande lireCommande(char * nomCommande, char * nbCommande) {
	FILE * fileCommande;
    T_Commande commande;
	fileCommande = fopen(nomCommande, "r");

    char factureName[CHARA_MAX] = "./factures/facture";
    strcat(factureName, nbCommande);
    strcat(factureName, ".txt");

    FILE * fileFacture = fopen(factureName, "w");

    char line[CLIENT_SIZE];
    commande.tailleProduit = 0;

    // Création de la liste des produits.
    T_TableauDeProduits tabProd;
    int tabsize = 0;
    lireProduits(tabProd, &tabsize);

    // Enregistre le nom du client dans commande.client.
    fgets(line, CLIENT_SIZE, fileCommande);
    strcpy(commande.client, line);

    //printf("\n\nClient: %s", commande.client);
    fprintf(fileFacture, "Client: %s", commande.client);
    float total = 0;

    while(fgets(line, CLIENT_SIZE, fileCommande) != NULL) {
        char * strToken = strtok(line, " \n");
        commande.idProduit[commande.tailleProduit] = convertStringIntoInt(strToken);
        strToken = strtok(NULL, " \n");
        commande.nbProduit[commande.tailleProduit] = convertStringIntoInt(strToken);

        for(int i = 0; i < tabsize; i++) {
            if(tabProd[i].reference == commande.idProduit[commande.tailleProduit]) {

                // Enlève le stock et imprime dans la facture ou crée une alerte selon si la procédure a fonctionné ou non
                if(enleverStock(tabProd[i].reference, commande.nbProduit[commande.tailleProduit])) {
                    fprintf(fileFacture, "%d %s (P.U. = %.2feur) :: %.2feur\n", commande.nbProduit[commande.tailleProduit], tabProd[i].libelle, (tabProd[i].prixUnitaire), (tabProd[i].prixUnitaire)*commande.nbProduit[commande.tailleProduit]);
                    total += (tabProd[i].prixUnitaire)*commande.nbProduit[commande.tailleProduit];
                } else {
                    alert(tabProd[i].reference);
                }
            }
        }

        commande.tailleProduit++;
    }

    fprintf(fileFacture, "\nTotal: %.2feur", total);

	fclose(fileCommande);
    fclose(fileFacture);

    return commande;
}

void lireProduits(T_TableauDeProduits tabProd, int *tabSize) {
	FILE * fileProducts;
	fileProducts = fopen("produits.txt", "r");

	char line[PROD_SIZE];

	while (fgets(line, PROD_SIZE, fileProducts) != NULL) {
		T_Produit produit;
        // Lit la référence
		char * strToken = strtok(line, " \n");
		produit.reference = convertStringIntoInt(strToken);
        // Lit le libellé
		strToken = strtok(NULL, " \n");
		strcpy(produit.libelle, strToken);
        // Lit le prix
		strToken = strtok(NULL, " \n");
		produit.prixUnitaire = convertPriceStringIntoDouble(strToken);

        tabProd[*tabSize] = produit;
        *tabSize = *tabSize + 1;
	}
}

// Permet d'enlever le stock d'un produit id de quantité nb.
// Renvoie 0 s'il y a un problème de stock, 1 si tout s'est passé correctement.
int enleverStock(int id, int nb) {
    FILE * fileStockRead;
    FILE * fileStockWrite;

    int flag = 0;

    char line[CHARA_MAX];

    // Écrit dans un fichier temporaire le nouveau stock alors que l'on lit le stock actuel
    fileStockRead = fopen("stock.txt", "r");
    fileStockWrite = fopen("stock.tmp", "w");

    while((fgets(line, CHARA_MAX, fileStockRead)) != NULL) {
        char * strToken = strtok(line, " \n");
        int idRead = convertStringIntoInt(strToken);

        strToken = strtok(NULL, " \n");
        int oldStock = convertStringIntoInt(strToken);

        // Vérifie si l'ID du produit modifié et lu est identique
        if(idRead == id) {
            // Vérifie s'il y a assez de stock
            if(oldStock - nb >= 0) {
                fprintf(fileStockWrite, "%d %d\n", idRead, oldStock - nb);
                flag = 1;
            } else {
                fprintf(fileStockWrite, "%d %d\n", idRead, oldStock);
            }
        } else {
            fprintf(fileStockWrite, "%d %d\n", idRead, oldStock);
        }
    }

    fclose(fileStockRead);
    fclose(fileStockWrite);

    // Suppression du fichier de l'ancien stock pour le remplacer par le nouveau
    remove("stock.txt");
    rename("stock.tmp", "stock.txt");

    return flag;
}

// Permet de créer un fichier alertes.txt contenant tous les produits ayant un manque de stock comparé à la commande voulue.
void alert(int id) {
    FILE * fileAlert;

    fileAlert = fopen("alertes.txt", "a");

    fprintf(fileAlert, " %d ", id);
}