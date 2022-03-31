#define TAILLE 50
#define PROD_SIZE 100

#define  NB_MAX_PRODUITS 1000


typedef struct {
    unsigned int reference; // ID (référence) du produit.
    char libelle[TAILLE]; // Nom du produit
    float prixUnitaire; // Prix unitaire du produit
} T_Produit;

typedef struct {
    char client[50]; // Nom du client
    unsigned int idProduit[PROD_SIZE]; // ID (Référence) du produit.
    int nbProduit[PROD_SIZE]; // Nombre d'achats sur un produit
    int tailleProduit; // Nombre de produits différents dans le tableau.
} T_Commande;

typedef T_Produit T_TableauDeProduits[NB_MAX_PRODUITS];

// Permet de donner l'int de la prochaine commande.
int lireProchaineCommande();
// Permet d'effectuer lireCommande() pour chaque commande.
void lireLesCommandes();
// Lit la commande et la renvoie dans le T_Commande donné par la fonction.
T_Commande lireCommande(char * nomCommande, char * nbCommande);
// Permet de faire le tableau des produits renvoyé dans tabProd.
void lireProduits(T_TableauDeProduits tabProd, int *tabSize);
// Permet d'enlever un certain nombre de produits dans le stock. Si l'ID est incorrect ou le stock n'est plus displonible, la fonction renverra 0.
// Sinon, elle renverra 1.
int enleverStock(int id, int nb);
// Crée un fichier alertes.txt dans lequel sera indiqué la référénce des objets manquants
void alert(int id);




