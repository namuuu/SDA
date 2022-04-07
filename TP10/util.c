#include "util.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

// Convertit la chaine int N en une chaîne de caractères N4.
//		Ex : N=1234  =>  N4="1234".
void convertIntIntoChar(int N, char * N4) {
    int m, c, d, u;
    char cm, cc, cd, cu;
    m = N / 1000;
    cm = 48 + m;
    N %= 1000;
    c = N / 100;
    cc = 48 + c;
    N %= 100;
    d = N / 10;
    cd = 48 + d;
    u = N % 10;
    cu = 48 + u;
    N4[0] = cm;
    N4[1] = cc;
    N4[2] = cd;
    N4[3] = cu;
    N4[4] = '\0';
}

// Convertit un string contenant des chiffres en Integer
int convertStringIntoInt(char * c) {
    int taille = strlen(c);
    int n = 0; // Converted int.

    for(int i = 1; i <= taille; i++) {
        n +=convertCharToInt(c[taille-i]) * (int)(pow(10, i-1));
    }

    return n;
}

// Convertit un prix en chaîne de caractères (ex: 3.50) en Double
double convertPriceStringIntoDouble(char * c) {
    int taille = strlen(c)-1;
    double price = 0;

    // Gère les chiffres après la virgule
    price += convertCharToInt(c[taille]) * pow(10,-2);
    taille--;
    price += convertCharToInt(c[taille]) * pow(10,-1);
    taille --;

    for(int i = 1; i <= taille; i++) {
        price += convertCharToInt(c[taille-i]) * (int)(pow(10, i-1));
    }

    return price;
}

// Convertit un seul caractère en int. Si le caractère n'était pas un int, alors renvoie 0.
int convertCharToInt(char c) {
    int n = c-'0';

    if(n<0 || n>9) {
        return 0;
    }
    return n;
}