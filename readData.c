#include "readData.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


// Cette fonction lis un fchier et cree une structure line pour chaque ligne de fichier
void dataOneSerie(char *fich ,head *tete){
    FILE *fichier;
    fichier = fopen(fich,"r");
    double MACHINE_ID;
    double MACHINE_DATA = 1;
    double TIMESTAMP;
    double WAFER_ID;
    char STAGE;
    double CHAMBER;
    double USAGE_OF_BACKING_FILM;
    double USAGE_OF_DRESSER;
    double USAGE_OF_POLISHING_TABLE;
    double USAGE_OF_DRESSER_TABLE;
    double PRESSURIZED_CHAMBER_PRESSURE;
    double MAIN_OUTER_AIR_BAG_PRESSURE;
    double CENTER_AIR_BAG_PRESSURE;
    double RETAINER_RING_PRESSURE;
    double RIPPLE_IR_BAG_PRESSURE;
    double USAGE_OF_MEMEBRANE;
    double USAGE_OF_PRESSURIZED_SHEET;
    double SLURRY_FLOW_LINE_A;
    double SLURRY_FLOW_LINE_B;
    double SLURRY_FLOW_LINE_C;
    double WAFER_ROTATION;
    double STAGE_ROTATION;
    double HEAD_ROTATION;
    double DRESSING_WATER_STATUS;
    double EDGE_AIR_BAG_PRESSURE;
if(fichier!=NULL){
        int test = 0;
        char *buffer = (char *)malloc(1024 * sizeof(char));
	    fgets(buffer, 1024, fichier);
        while(fscanf(fichier,"%lf",&MACHINE_ID)==1){ // on repète l'action pour chaque ligne du fichier
            fscanf(fichier,"%lf\t%lf\t%lf\t%c\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf",&MACHINE_DATA,&TIMESTAMP,&WAFER_ID,&STAGE,&CHAMBER,&USAGE_OF_BACKING_FILM,&USAGE_OF_DRESSER,&USAGE_OF_POLISHING_TABLE,&USAGE_OF_DRESSER_TABLE,&PRESSURIZED_CHAMBER_PRESSURE,&MAIN_OUTER_AIR_BAG_PRESSURE,&CENTER_AIR_BAG_PRESSURE,&RETAINER_RING_PRESSURE,&RIPPLE_IR_BAG_PRESSURE,&USAGE_OF_MEMEBRANE,&USAGE_OF_PRESSURIZED_SHEET,&SLURRY_FLOW_LINE_A,&SLURRY_FLOW_LINE_B,&SLURRY_FLOW_LINE_C,&WAFER_ROTATION,&STAGE_ROTATION,&HEAD_ROTATION,&DRESSING_WATER_STATUS,&EDGE_AIR_BAG_PRESSURE);
            line *a; // nouvelle structure
            a = (line *) malloc(sizeof(line));
            strcpy(a->fichier,fich);
            a->MACHINE_ID = MACHINE_ID;
            a->MACHINE_DATA = MACHINE_DATA; 
            a->TIMESTAMP =TIMESTAMP;
            a->WAFER_ID = WAFER_ID;
            a->STAGE = STAGE;
            a->CHAMBER = CHAMBER;
            a->USAGE_OF_BACKING_FILM = USAGE_OF_BACKING_FILM;
            a->USAGE_OF_DRESSER = USAGE_OF_DRESSER;;
            a->USAGE_OF_POLISHING_TABLE = USAGE_OF_POLISHING_TABLE;
            a->USAGE_OF_DRESSER_TABLE = USAGE_OF_DRESSER_TABLE;
            a->PRESSURIZED_CHAMBER_PRESSURE = PRESSURIZED_CHAMBER_PRESSURE;
            a->MAIN_OUTER_AIR_BAG_PRESSURE = MAIN_OUTER_AIR_BAG_PRESSURE;
            a->CENTER_AIR_BAG_PRESSURE = CENTER_AIR_BAG_PRESSURE;
            a->RETAINER_RING_PRESSURE = RETAINER_RING_PRESSURE;
            a->RIPPLE_IR_BAG_PRESSURE = RIPPLE_IR_BAG_PRESSURE;
            a->USAGE_OF_MEMEBRANE = USAGE_OF_MEMEBRANE;
            a->USAGE_OF_PRESSURIZED_SHEET = USAGE_OF_PRESSURIZED_SHEET;
            a->SLURRY_FLOW_LINE_A = SLURRY_FLOW_LINE_A;
            a->SLURRY_FLOW_LINE_B = SLURRY_FLOW_LINE_B;
            a->SLURRY_FLOW_LINE_C = SLURRY_FLOW_LINE_C;
            a->WAFER_ROTATION = WAFER_ROTATION;
            a->STAGE_ROTATION = STAGE_ROTATION;
            a->HEAD_ROTATION = HEAD_ROTATION;
            a->DRESSING_WATER_STATUS = DRESSING_WATER_STATUS;
            a->EDGE_AIR_BAG_PRESSURE = EDGE_AIR_BAG_PRESSURE;
            a->suivant = tete->tete;
            tete->tete = a;
        }
       fclose(fichier);
       free(buffer);
    }
    else{
        printf("erreur lors de l'ouverture de ce fichier");
    }
}

// cette fonction ouvre le dossier et récupère les noms de tous les fichiers
void nomFichiers(head *tete){
    char **tab;
    tab = (char**) malloc(300*sizeof(char*));
    for(int k=0;k<300;k++){
        tab[k] = (char*) malloc(100*sizeof(char));
    }
    char nom_fichier[25];
    char chemin[100];
    DIR *d;
    struct dirent *dir;
    d = opendir("training");
    int i=0;
    if(d!=NULL){
        for(dir=readdir(d); dir!=NULL; dir=readdir(d)){ // pour chaque fichier on appel la fonction précédente
            strcpy(nom_fichier,dir->d_name);
            if(nom_fichier[0]!='.'){
                strcpy(chemin,CHEMIN);
                strcat(chemin,nom_fichier);
                strcpy(tab[i],chemin);
                i++;
            }
        }
        closedir(d);
    }
    tri_iteratif(tab,i);
    for(int k=0;k<i;k++){
        dataOneSerie(tab[k],tete);
    }
    free(tab);

}

// cette fonction sert à trier par ordre alphabétique
// elle est utilisée pour trier ls noms des fichiers, pourque le temps soit lineiare tout au long de la liste chainée
void tri_iteratif(char *tableau[], int taille){
   char *temp; 
   int i, j;
    for (i = 0; i < taille; i++) 
        for (j = 0; j < taille; j++)
        if (strcmp(tableau[i], tableau[j]) < 0)
            {
            temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
            }
  }


// cette fonction tries les valeurs et remplace les valeurs anormales par -1
// en effet toute les valeurs sont positives ; ainsi pour traivailler avec ces valeurs filtrées il suffira 
// de négliger les valeurs négatives
void valeursAtypiques(int coefficient,head *tete,double ecartType[21]){
    line *courant;
    courant = tete->tete;
    while(courant != NULL){
        if(courant->CHAMBER > (coefficient*ecartType[1])){
            courant->CHAMBER = -1;
        }
        else if(courant->USAGE_OF_BACKING_FILM > (coefficient*ecartType[2])){
            courant->USAGE_OF_BACKING_FILM = -1;
        }
        else if(courant->USAGE_OF_DRESSER > (coefficient*ecartType[3])){
            courant->USAGE_OF_DRESSER = -1;
        }
        else if(courant->USAGE_OF_POLISHING_TABLE > (coefficient*ecartType[4])){
            courant->USAGE_OF_POLISHING_TABLE = -1;
        }
        else if(courant->USAGE_OF_DRESSER_TABLE > (coefficient*ecartType[5])){
            courant->USAGE_OF_DRESSER_TABLE = -1;
        }
        else if(courant->PRESSURIZED_CHAMBER_PRESSURE > (coefficient*ecartType[6])){
            courant->PRESSURIZED_CHAMBER_PRESSURE = -1;
        }
        else if(courant->MAIN_OUTER_AIR_BAG_PRESSURE > (coefficient*ecartType[7])){
            courant->MAIN_OUTER_AIR_BAG_PRESSURE = -1;
        }
        else if(courant->CENTER_AIR_BAG_PRESSURE > (coefficient*ecartType[8])){
            courant->CENTER_AIR_BAG_PRESSURE = -1;
        }
        else if(courant->RETAINER_RING_PRESSURE > (coefficient*ecartType[9])){
            courant->RETAINER_RING_PRESSURE = -1;
        }
        else if(courant->RIPPLE_IR_BAG_PRESSURE > (coefficient*ecartType[10])){
            courant->RIPPLE_IR_BAG_PRESSURE = -1;
        }
        else if(courant->USAGE_OF_MEMEBRANE > (coefficient*ecartType[11])){
            courant->USAGE_OF_MEMEBRANE = -1;
        }
        else if(courant->USAGE_OF_PRESSURIZED_SHEET > (coefficient*ecartType[12])){
            courant->USAGE_OF_PRESSURIZED_SHEET = -1;
        }
        else if(courant->SLURRY_FLOW_LINE_A > (coefficient*ecartType[13])){
            courant->SLURRY_FLOW_LINE_A = -1;
        }
        else if(courant->SLURRY_FLOW_LINE_B > (coefficient*ecartType[14])){
            courant->SLURRY_FLOW_LINE_B = -1;
        }
        else if(courant->SLURRY_FLOW_LINE_C > (coefficient*ecartType[15])){
            courant->SLURRY_FLOW_LINE_C = -1;
        }
        else if(courant->WAFER_ROTATION > (coefficient*ecartType[16])){
            courant->WAFER_ROTATION = -1;
        }
        else if(courant->STAGE_ROTATION > (coefficient*ecartType[17])){
            courant->STAGE_ROTATION = -1;
        }
        else if(courant->HEAD_ROTATION > (coefficient*ecartType[18])){
            courant->HEAD_ROTATION = -1;
        }
        else if(courant->DRESSING_WATER_STATUS > (coefficient*ecartType[19])){
            courant->DRESSING_WATER_STATUS = -1;
        }
        else if(courant->EDGE_AIR_BAG_PRESSURE> (coefficient*ecartType[20])){
            courant->EDGE_AIR_BAG_PRESSURE = -1;
        }
         
        courant = courant->suivant;
    }
}