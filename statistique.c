#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "statistique.h"
#include "readData.h"

// Fonction pour calculer le max d'un tableau
double max(double tab[300000], int k){
    double max=0;
    int i = 0;
    while(i<k){
        if(tab[i]>max){
            max = tab[i];
        }
        i++;
    }
    return max;
}

// Fonction qui renvoie le nom d'une variable selont un entier bien précis [1:20]
char* remonterNomVariable(int i){
    char *tab[] =  {"CHAMBER","USAGE_OF_BACKING_FILM","USAGE_OF_DRESSER","USAGE_OF_POLISHING_TABLE","USAGE_OF_DRESSER_TABLE","PRESSURIZED_CHAMBER_PRESSURE","MAIN_OUTER_AIR_BAG_PRESSURE","CENTER_AIR_BAG_PRESSURE","RETAINER_RING_PRESSURE","RIPPLE_IR_BAG_PRESSURE","USAGE_OF_MEMEBRANE","USAGE_OF_PRESSURIZED_SHEET","SLURRY_FLOW_LINE_A","SLURRY_FLOW_LINE_B","SLURRY_FLOW_LINE_C","WAFER_ROTATION","STAGE_ROTATION","HEAD_ROTATION","DRESSING_WATER_STATUS","EDGE_AIR_BAG_PRESSURE"};
    return tab[i-1];
}

// Fonction pour calculer le minimum d'un tableau
double min(double tab[300000],int k){
    double min = max(tab,k);
    int i = 0;
    while(i<k){
        if(tab[i] != -1){ // on ne prend pas en compte le cas des negatif à cause de la détection des valeurs atypiques
            if(tab[i]<min){
                min = tab[i];
            }
        }
        i++;
    }
    return min;
}

// Fonction pour calculer la moyenne
double moy(double tab[300000],int k){
    double sum = 0.0;
    int indice = 0;
    double *bonneVal; // on enleve tout les négatifs car ça veut que ce sont des valeurs anormales
    bonneVal = (double *) malloc(k*sizeof(double));
    for(int j=0;j<k;j++){
        if(tab[j] != -1){
            bonneVal[indice] = tab[j];
            indice ++;
        }
    }
    int i = 0;
    while(i<indice){
            sum = sum + bonneVal[i];
        i++;
    }
    double moy = sum/indice;
    free(bonneVal);
    return  moy;
}

// Fonction pour calculer l'écart type
double ecart(double tab[300000],int moy,int k){
    double sum = 0.0;
    int indice = 0;
    double *bonneVal;
    bonneVal = (double *) malloc(k*sizeof(double));
    for(int j=0;j<k;j++){
        if(tab[j] != -1){
            bonneVal[indice] = tab[j];
            indice ++;
        }
    }

    int i = 0;
    while(i<indice-1){
        sum = sum + ((bonneVal[i]-moy))*((bonneVal[i]-moy));
        i++;
    }
    double ecart = sqrt(sum/indice);
    free(bonneVal);
    return  ecart;
}

// Fonction pour calculer les Quartiles
double quartile25(double tab[300000],int k){
    qsort(tab,k,sizeof(double),CompareInts);
    double *val;
    val = (double *) malloc(k*sizeof(double));
    int i=0;
    for(int j=0;j<k;j++){
        if(tab[j]>0){
            val[i] = tab[j];
            i++;
        }
    }
    int rang = ceil(i/4);
    double r = val[rang];
    free(val);
    return r;
}
double quartile50(double tab[300000],int k){
    qsort(tab,k,sizeof(double),CompareInts);
    double *val;
    val = (double *) malloc(k*sizeof(double));
    int i=0;
    for(int j=0;j<k;j++){
        if(tab[j]>0){
            val[i] = tab[j];
            i++;
        }
    }
    int rang = ceil(i/2);
    double r = val[rang];
    free(val);
    return r;
}
double quartile75(double tab[300000],int k){
    qsort(tab,k,sizeof(double),CompareInts);
    double *val;
    val = (double *) malloc(k*sizeof(double));
    int i=0;
    for(int j=0;j<k;j++){
        if(tab[j]>0){
            val[i] = tab[j];
            i++;
        }
    }
    int rang = ceil(i*0.75);
    double r = val[rang];
    free(val);
    return r;
}

// focntion pour calculer la médiane
double mediane(double tab[300000],int k){
    qsort(tab,k,sizeof(double),CompareInts);
    double *val;
    val = (double *) malloc(k*sizeof(double));
    int i=0;
    for(int j=0;j<k;j++){ // on enlève les termes négatifs
        if(tab[j]>0){
            val[i] = tab[j];
            i++;
        }
    }
    int rang = ceil(i/2);
    double r = val[rang];
    return r;
}

// Cette fonction est nécessaire pour utiliser la fonction qsort()
int CompareInts(const void *p1, const void *p2){{
  return (*(double*)p1 - *(double*)p2);
}
}

// Fonction pour génerer les histogrammes
void histogramme(double *data,int taille){
    int taille2 =0;
    for(int i=0;i<taille;i++){
        if(data[i]!=-1){
            taille2++;
        }
    }
    double Max = max(data,taille);
    double Min = min(data,taille);
    int n = 10; // choix de 10 bin
    int k = 0;
    double pas = (Max-Min)/n; // taille de chaque bin
    double intervalle[11];
    double nombreElements[10] = {0,0,0,0,0,0,0,0,0,0};
    int nombreBatons[10];
    for(int i=0;i<n+1;i++){
        intervalle[i] = Min + i*pas;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<taille;j++){
            if((data[j]>=intervalle[i]) && (data[j]<intervalle[i+1])){
                nombreElements[i] = nombreElements[i] + 1;
            }

        }
    }
    printf("|         Intervalles          |    Valeur (pourcentage)     |\n");
    printf("--------------------------------------------------------------\n");
    intervalle[10] = Max;
    for(int i=0;i<n;i++){
        nombreBatons[i] =  (int) ceil((nombreElements[i]/taille2)*100); // Normalisation pour se ramener à un %
        printf(" [%-13lf,%13lf] : ",intervalle[i],intervalle[i+1]);
        printf("\033[0;32m"); 
        // 100% <=> 100 batonnet    
        printf("%.*s \n",nombreBatons[i],"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
        printf("\033[0;37m");
    }
    
}

// Fonction qui enléve les doublons dans un tableau
int remove_duplicate(double *arr, int n){
    double temp[n];
    int j = 0;
    for(int i=0;i<n;i++){
        
        for(int k=0;k<j;k++){
            if(arr[i]==temp[k]){
                goto suit56;
            }
        }
        temp[j] = arr[i];
        j++;
        suit56: ;
    }
    for(int i=0;i<j;i++){
        arr[i]=temp[i];
    }
    return j;
}
