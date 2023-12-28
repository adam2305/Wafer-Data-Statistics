#include "interface.h"
#include "statistique.h"
#include "readData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//     --- COULEUR DU TEXTE  ---
// Ces fonctions permettent de modifier la couleur du texte
void red () {
  printf("\033[1;31m");
}

void white() {
  printf("\033[0;37m");
}

void purple() {
  printf("\033[0;32m");
}

void blue() {
  printf("\033[0;36m");
}

void outputcolor(){
  printf("\033[0;35m");
}


//  affiche le bandeau au debut et à la fin du programme
void bandeau(){
    int  i, j;
    int rows = 1;
    int cols = 40;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("/\\");
        }
        printf("\n");
    }
}

