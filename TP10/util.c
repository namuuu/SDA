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

int convertStringIntoInt(char * c) {
    int taille = strlen(c);
    int n = 0; // Converted int.

    for(int i = 1; i <= taille; i++) {
        printf("n: %c  i: %d  pow:%lf  added:%lf\n", c[taille-i], i-1, pow(10, i-1),  c[taille-i] * pow(10, i-1));
        n += c[taille-i] * pow(10, i-1);
    }

    return n;
}