// IG2I / SDD 
// 2021-11-17
// Vincent Liard - P Kubiak

#include <time.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include "stack.h"


// Labyrinthe en anglais : maze.

// Représente un chemin sous la forme d'une chaîne de caractères
// composée des lettres u (up), d (down), l (left), r (right).
typedef char * path_t;

typedef struct {
    int valeur;
    bool visited;
    char direction; // u d r ou l 
    int nbDirections; // ou nbrVoisins : c'est à dire le nb de cases utiles dans directionsPossibles et QuatreVoisins
    char directionsPossibles[5];
    int QuatreVoisins[4]; // valeur des 4(ou-) voisins 
}
T_cellule;
typedef struct {
    //  v________ 
    // |   ______| ^
    // | |_____  | |
    // |  _|   | | |
    // |_|  _| | | row(6)
    // | __|___  | |es politiques, syndicaux et étudiants a appelé à une large manifestation à Ajaccio, dimanche 3 avril. Une décision qui n'a pas remporté les faveurs de l'ensemble des membres du collecti
    // |_______|v| v
    // <--col(5)->

    // Le labyrinthe comporte row lignes-couloirs horizontaux
    // (est-ouest) et col colonnes-couloirs verticaux (nord-sud).

    // Il y a implicitement des murs tout autour du labyrinthe.

    // L'entrée se trouve dans la cellule supérieure gauche
    // (nord-ouest), la sortie se trouve dans la cellule inférieure
    // droite (sud-est).

    // wallh[i][j] et wallv[i][j] encodent pour la cellule (i,j) le fait
    // qu'elle comporte un mur horizontal au dessous ou vertical à
    // droite (respectivement).

    // Nombre de lignes
    int row;
    // Nombre de colonnes
    int col;
    int num;
    // table de booléens murs horizontaux '_'
    bool * wallh;
    // table de booléens murs verticaux '|'
    bool * wallv;
    T_cellule * cells;

}
maze_t;

// Indique s'il y a un mur en dessous selon row / col
bool * wall_under(maze_t * m, int row, int col);
// Indique s'il y a un mur à droite selon row / col
bool * wall_right(maze_t * m, int row, int col);
// Initie un maze_t avec des valeurs aléatoires
maze_t * init_maze(int row, int col);
void free_maze(maze_t * m);
void print_maze_raw(maze_t
    const * m);
void print_maze(maze_t
    const * m, char * udlr, int t[200][2], int n);
void print_mazePLEIN(maze_t
    const * m);
void print_mazePLEINchemin(maze_t
    const * m, T_cellule * chemin, int t);
maze_t * compartmentalized_maze(int row, int col);
maze_t * random_maze(int row, int col);
void print_tab(int (*tab)[], int row, int col);
bool check_path(maze_t * m, path_t * p);
void printValeurs(maze_t * );
path_t solve_maze(maze_t * m);

void printValeurs(maze_t * m) {

    int i, j;
    for (i = 0; i < m -> row; i++) {
        printf("\n");
        for (j = 0; j < m -> col; j++)
            printf("%3d|", m -> cells[i * m -> col + j].valeur);
    }
    printf("\n");
    printf("\n");

}

int main(void) {

    int numberRow, numberCol;

    printf("\n quel sera le nombre de lignes de votre labyrinthe ? ");
    scanf("%d", & numberRow);
    printf("\n quel sera le nombre de colonnes de votre labyrinthe ? ");
    scanf("%d", & numberCol);
    maze_t * maze = random_maze(numberRow, numberCol);

    print_mazePLEIN(maze);  

    path_t p = solve_maze(maze); 

    printf("\n%s\n", p);

    check_path(maze, &p);

    free_maze(maze);

    return 0;
}


// Accès (en lecture et écriture) au mur vertical à droite de la
// cellule row, col du labyrinthe m
bool * wall_right(maze_t * m, int row, int col) {
    if (row > m -> row || col > m -> col - 1)
        return NULL;
    return &(m -> wallv[row * (m -> col - 1) + col]);
}

// Accès (en lecture et écriture) au mur horizontal au dessous de la
// cellule row, col du labyrinthe m
bool * wall_under(maze_t * m, int row, int col) {
    if (row > m -> row - 1 || col > m -> col)
        return NULL;
    return &(m -> wallh[row * m -> col + col]);
}

// Retourne un pointeur sur un maze_t complètement initialisé ou NULL
// si l'allocation a échoué.
maze_t * init_maze(int row, int col) {
    maze_t * m;
    m = malloc(sizeof(maze_t));
    if (!m)
        return NULL;
    m -> row = row;
    m -> col = col;

    m -> wallh = malloc((row - 1) * (col) * sizeof(int));
    m -> wallv = malloc((row) * (col - 1) * sizeof(int));
    m -> cells = malloc((row) * (col) * sizeof(T_cellule));
    if (!m -> wallh || !m -> wallv || !m -> cells)
        return NULL;
    return m;
}

void free_maze(maze_t * m) {
    free(m -> wallv);
    free(m -> wallh);
    free(m);
}

// Crée un labyrinthe dont tous les murs sont complets. 
// « Labyrinthe dans lequel toutes les cellules sont fermées.
// Exemple : Le « labyrinthe » compartimenté 6 lignes, 5 colonnes
// ._________.
// |_|_|_|_|_|
// |_|_|_|_|_|
// |_|_|_|_|_|
// |_|_|_|_|_|
// |_|_|_|_|_|
// |_|_|_|_|_|
maze_t * compartmentalized_maze(int row, int col) {
    maze_t * m;
    if (!(m = init_maze(row, col)))
        return NULL;
    //print_maze_raw(m);
    // Lignes et colonnes internes
    for (int i = 0; i < m -> row - 1; ++i)
        for (int j = 0; j < m -> col - 1; ++j) {
            * wall_under(m, i, j) = 1;
            * wall_right(m, i, j) = 1;
        }
    // Dernière colonne (murs horizontaux) :
    for (int i = 0; i < m -> row - 1; ++i)
        *
        wall_under(m, i, m -> col - 1) = 1;
    // Dernière ligne (murs verticaux) :
    for (int j = 0; j < m -> col - 1; ++j)
        *
        wall_right(m, m -> row - 1, j) = 1;

    for (int i = 0; i < m -> row; ++i)

        for (int j = 0; j < m -> col; ++j)
            m -> cells[i * col + j].valeur = i * col + j;
    return m;
}

void print_maze_raw(maze_t
    const * m) {
    printf("\trow : %d, col : %d\n", m -> row, m -> col);
    printf("\twallh %d lignes x %d colonnes :\n\t", m -> row - 1, m -> col);
    for (int i = 0; i < m -> row - 1; ++i) {
        for (int j = 0; j < m -> col; ++j)
            printf("%d ", m -> wallh[i * m -> col + j]);
        printf("\n\t");
    }

    printf("\twallv %d lignes x %d colonnes :\n\t", m -> row, m -> col - 1);
    for (int i = 0; i < m -> row; ++i) {
        for (int j = 0; j < m -> col - 1; ++j)
            printf("%d ", m -> wallv[i * (m -> col - 1) + j]);
        printf("\n\t");
    }
}

// Affiche sur stdout le labyrinthe fourni en argument.

// Les caractères utilisés pour l'affichage sont
// '_' pour un mur en dessous de la cellule considérée,
// '|' pour un mur à droite de la cellule considérée.
// ----------------------------------------------------------------------------------------------------------------
void print_maze(maze_t
    const * m, char * udlr, int t[200][2], int n) {
    print_maze_raw(m);
    // int pos = 0;
    //Mur supérieur
    printf(" v");
    for (int i = 0; i < m -> col - 1; ++i)
        printf("__");
    printf(" \n");

    for (int i = 0; i < m -> row - 1; i++) {
        printf("|");
        for (int j = 0; j <= m -> col - 1; j++) {
            printf(m -> wallh[i * m -> col + j] ? "_" : " ");

            printf(m -> wallv[i * (m -> col - 1) + j] ? "|" : " ");
            printf("|");
        }
        printf("\n");
        printf("%s|\n", m -> wallh[(i + 1) * m -> col - 1] ? "_" : " ");
        // "|" : m->wallh[(i + 1) * m->col + j] ? "_" : " "
    }

    // Mur inférieur
    printf("|");
    for (int i = 0; i < m -> col - 1; ++i) {
        printf("_|");
    }

    //printf(m->wallv[(m->row - 1) * (m->col - 1) + i] ? "_|" : "__");
    printf("v|\n");
}

void print_mazePLEIN(maze_t const * m) {
    // printf("Preview colonnes / lignes :");
    // print_maze_raw(m);
    // printf("\n");

    //Mur supérieur
    printf(" v");
    for (int i = 0; i < m -> col - 1; ++i)
        printf("__");
    printf(" \n");

    for (int i = 0; i < m -> row - 1; ++i) {
        printf("|");
        for (int j = 0; j < m -> col - 1; ++j) {
            printf(m -> wallh[i * m -> col + j] ? "_" : " ");

            printf(m -> wallv[i * (m -> col - 1) + j] ? "|" : " ");
        }
        printf("%s|\n", m -> wallh[(i + 1) * m -> col - 1] ? "_" : " ");
        // "|" : m->wallh[(i + 1) * m->col + j] ? "_" : " "
    }

    // Mur inférieur
    printf("|");
    for (int i = 0; i < m -> col - 1; ++i)
        printf(m -> wallv[(m -> row - 1) * (m -> col - 1) + i] ? "_|" : "__");
    printf("v|\n");
}

maze_t * random_maze(int row, int col) {
    maze_t * m = compartmentalized_maze(row, col);
    int tab[row][col];

    srand(time(NULL));

    // Initie le tableau tab
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            tab[i][j] = i*col + j; 
    

    bool flag = 1;

    while(flag) {

        // Random
        int randRow = rand() % row;
        int randCol = rand() % col;
        // printf("Random case: %d (row: %d ; col: %d)\n\n", randRow * col + randCol, randRow, randCol);

        // Choisis un mur aléatoirement
        bool wall = rand()%2;
        // Wall = 1 : Mur du dessous
        // Wall = 0 : Mur sur la droite
        if(wall == 1) {
            if(randRow == row-1) {
                wall = 0;
                if(randCol == col-1)
                    continue;
            }
        } else {
            if(randCol == col-1) {
                wall = 1;
                if(randRow == row-1)
                    continue;
            }
        }

        // Détermine les chiffres de destination et origine dans Tab
        int orig = tab[randRow][randCol];
        int dest;
        if(wall == 1) {
            dest = tab[randRow+1][randCol];
        } else {
            dest = tab[randRow][randCol+1];
        }

        //printf("Merge de %d vers les %d.\n", dest, orig);

        // Vérifie si l'emplacement est correct
        if(orig == dest) {
            continue;
        }

        // Enlève le mur
        if(wall == 1) {
            m->wallh[(randRow)*(col) + randCol] = 0;
            //printf("Mur enlevé : %d.", (randRow)*col + randCol);
        } else {
            m->wallv[(randRow)*(col-1) + randCol] = 0;
            //printf("Mur enlevé : %d.", (randRow)*(col-1) + randCol);
        }
       
        

        
        // Propagation
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if(tab[i][j] == dest) {
                    tab[i][j] = orig;
                }
            }   
        }

        // Affiche le tableau
        // printf("\nAffichage du tableau :\n");
        // for (int i = 0; i < row; ++i) {
        //     for (int j = 0; j < col; ++j)
        //         printf("%d ", tab[i][j]);
        //     printf("\n");
        // }
        // printf("\n");

        // Affiche le visited
        // printf("\nAffichage du tableau :\n");
        // for (int i = 0; i < row; ++i) {
        //     for (int j = 0; j < col; ++j)
        //         printf("%d ", visited[i][j]);
        //     printf("\n");
        // }
        // printf("\n");

        // Vérifie le tableau;
        flag = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if(tab[i][j] != tab[0][0])
                    flag = 1;
            }
        }
    }

    return m;
}   

// Return the path from 0,0 to (row - 1, col - 1).
path_t solve_maze(maze_t * m) {
    // Le plus long chemin sans recouvrement sur une grille row x col
    // mesure row x col.
    int row = m->row;
    int col = m->col;
    path_t p = malloc(row * col);

    // Repères
    int north = 0;
    int east = 1;
    int south = 2;
    int west = 3;
    //dstack_t s;

    // 0 = free
    // 1 = visited
    // 2 = path
    int trace[row*col][4];
    
    // Nombre de pas effectués
    int path = 0;

    // Position de notre curseur
    char currRow = 0;
    char currCol = 0;

    // Initie le tableau trace
    for (int iniRow = 0; iniRow < row; ++iniRow) {
        for (int iniCol = 0; iniCol < col; ++iniCol) {
            for(int dir = 0; dir < 4; ++dir) {
                trace[iniRow*col+iniCol][dir] = 0;
            }
            if(iniRow == 0)
                trace[iniRow*col+iniCol][north] = 1;
                
            if(iniCol == 0)
                trace[iniRow*col+iniCol][west] = 1;

            if(iniRow == row-1)
                trace[iniRow*col+iniCol][south] = 1;

            if(iniCol == col-1)
                trace[iniRow*col+iniCol][east] = 1;

            // wall_right(maze_t * m, int row, int col)
            if(*wall_right(m, iniRow, iniCol)) {
                trace[iniRow*col+iniCol][east] = 1;
            }
            if(*wall_right(m, iniRow, iniCol-1)) {
                trace[iniRow*col+iniCol][west] = 1;
            }
            if(*wall_under(m, iniRow, iniCol)) {
                trace[(iniRow*col)+iniCol][south] = 1;
            }
            if(*wall_under(m, iniRow-1, iniCol)) {
                trace[(iniRow*col)+iniCol][north] = 1;
            }
        }
    }
            


    while (currRow != row-1 || currCol != col-1) {

    //     // Print le tableau trace
    //     for (int iniRow = 0; iniRow < row; ++iniRow) {
    //         for (int iniCol = 0; iniCol < col; ++iniCol)
    //             printf("%d ", trace[iniRow*col+iniCol][east] + trace[iniRow*col+iniCol][west] + trace[iniRow*col+iniCol][north] + trace[iniRow*col+iniCol][south]);
    //     printf("\n");
    //     }  

    // getchar();  

        ////// TENTE DE TROUVER UN CHEMIN POSSIBLE
        if(trace[currRow*col+currCol][north] == 0) {
            trace[currRow*col+currCol][north] = 2;
            currRow--;
            trace[currRow*col+currCol][south] = 2;
            p[path] = 'u';
            path++;
            continue;
        }
        if(trace[currRow*col+currCol][east] == 0) {
            trace[currRow*col+currCol][east] = 2;
            currCol++;
            trace[currRow*col+currCol][west] = 2;
            p[path] = 'r';
            path++;
            continue;
        }
        if(trace[currRow*col+currCol][south] == 0) {
            trace[currRow*col+currCol][south] = 2;
            currRow++;
            trace[currRow*col+currCol][north] = 2;
            p[path] = 'd';
            path++;
            continue;
        }
        if(trace[currRow*col+currCol][west] == 0) {
            trace[currRow*col+currCol][west] = 2;
            currCol--;
            trace[currRow*col+currCol][east] = 2;
            p[path] = 'l';
            path++;
            continue;
        }

        ////////// PAS DE CHEMIN POSSIBLE À PARTIR D'ICI
        if(trace[currRow*col+currCol][north] == 2) {
            trace[currRow*col+currCol][north] = 1;
            currRow--;
            trace[currRow*col+currCol][south] = 1;
            path--;
            continue;
        }
        if(trace[currRow*col+currCol][east] == 2) {
            trace[currRow*col+currCol][east] = 1;
            currCol++;
            trace[currRow*col+currCol][west] = 1;
            path--;
            continue;
        }
        if(trace[currRow*col+currCol][south] == 2) {
            trace[currRow*col+currCol][south] = 1;
            currRow++;
            trace[currRow*col+currCol][north] = 1;
            path--;
            continue;
        }
        if(trace[currRow*col+currCol][west] == 2) {
            trace[currRow*col+currCol][west] = 1;
            currCol--;
            trace[currRow*col+currCol][east] = 1;
            path--;
            continue;
        }
    }

    p[path] = '\0';

    return p;
}

bool check_path(maze_t * m, path_t * p) {
    bool flag = false;

    int currRow = 0;
    int currCol = 0;

    int row = m->row;
    int col = m->col;

    int path = 0;

    char tab[row][col];

    for (int iniRow = 0; iniRow < row; ++iniRow) {
        for (int iniCol = 0; iniCol < col; ++iniCol) {
            tab[iniRow][iniCol] = 0;
        }
    }


    while((*p)[path] != '\0') {

        switch ((*p)[path])
        {
        case 'u':
            tab[currRow][currCol] = 'u'; 
            currRow--; 
            break;
        case 'l':
            tab[currRow][currCol] = 'l'; 
            currCol--;
            break;
        case 'r':    
            tab[currRow][currCol] = 'r'; 
            currCol++;
            break;
        case 'd':
            tab[currRow][currCol] = 'd'; 
            currRow++;
            break;
        default:
            break;
        }
        path++;
    }   

    if(currRow == row && currCol == col)
        flag = true;
    for (int iniRow = 0; iniRow < row; ++iniRow) {
        printf("__");
    }
    printf("\n");
    for (int iniRow = 0; iniRow < row; ++iniRow) {
        for (int iniCol = 0; iniCol < col; ++iniCol) {
            if(iniCol == 0)
                printf("|");

            if(iniCol == col-1 && iniRow == row-1) {
                printf("v|");
                continue;
            }

            switch (tab[iniRow][iniCol])
            {
            case 'u':
                printf("u");
                break;
            case 'l':
                printf("l");
                break;
            case 'r':    
                printf("r");
                break;
            case 'd':
                printf("d");
                break;
            default:
                if(*wall_under(m, iniRow, iniCol) || iniRow == row-1) {
                    printf("_");
                } else {
                    printf(" ");
                }
                
                break;
            }
            if(*wall_right(m, iniRow, iniCol) || iniCol == col-1) {
                printf("|");
            } else {
                if(iniRow == row-1) {
                    printf("_");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    return flag;
}