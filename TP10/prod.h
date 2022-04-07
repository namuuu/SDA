
// Nombre maximum de caractères dans un String, tel que le nom du client, le libellé du produit...
#define CHARA_MAX 300
// Taille maximale d'une ligne dans le fichier produits.txt
#define PROD_SIZE 200
// Taille maximale d'une ligne dans les fichiers commandeXXXX.txt
#define CLIENT_SIZE 200

// Nombre maximum de produits différents disponibles
#define NB_MAX_PRODUITS 1000


typedef struct {
    unsigned int reference; // ID (référence) du produit.
    char libelle[CHARA_MAX]; // Nom du produit
    float prixUnitaire; // Prix unitaire du produit
} T_Produit;

typedef struct {
    char client[CHARA_MAX]; // Nom du client
    unsigned int idProduit[NB_MAX_PRODUITS]; // ID (Référence) du produit.
    int nbProduit[NB_MAX_PRODUITS]; // Nombre d'achats sur un produit
    int tailleProduit; // Nombre de produits différents dans le tableau.
} T_Commande;

// Tableau contenant tout les T_Produits différents
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
void createNewCommand(char * nbCommande);




