#define TAILLE 50
#define PROD_SIZE 100

#define  NB_MAX_PRODUITS 1000


typedef struct 
{
unsigned int reference;
char libelle[TAILLE];
float prixU;
} T_Produit;

typedef T_Produit T_TableauDeProduits[NB_MAX_PRODUITS];

int lireProchaineCommande();
void lireLesCommandes();
void lireCommande(char * nomCommande);




