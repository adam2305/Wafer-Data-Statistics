#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include "readData.h"
#include "interface.h"
#include "statistique.h"
#include "main.h"

//                    ---  AFFICHAGE  ---

// Cette fonction est le Menu principal du programme
void Menu(){
    int mode = 0;
    printf("\n");
    bandeau();
    printf("\n");
    while(1){
        blue();
        printf("--- Menu principal ---\n");
        white();
        printf("  1 : Statistiques descriptives sur une série temporelle\n");
        printf("  2 : Statistiques pour l'ensemble des données\n");
        printf("  3 : Détection des obsérvations atypiques \n"); // ajouter question parce que changement perm.
        printf("  4 : Histogrammes\n");
        printf("  5 : Aggrégation des données par Wafer\n");
        printf("  6 : Quitter le programme\n");
        purple();
        printf(">>> ");
        white();
        scanf("%d",&mode);
        switch(mode){
            case 1:
                sousMenu1();
                goto suite;
            case 2:
                sousMenu3();
                goto suite;
            case 3:
                sousMenu5();
                goto suite;
            case 4:
                sousMenu6();
                goto suite;
            case 5:
                sousMenu2();
                goto suite;
            case 6:
                blue();
                printf("--- Fermeture du programme ---\n");
                white();
                printf("\n");
                bandeau();
                goto exitloop;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable\n");
                white();
                goto suite;
        }
        suite: ;
    }
    exitloop: ;
}

// Sous menu pour traiter les données d'un seul fichier
void sousMenu1(){
    char nom[30]; // nom du fichier choisi
    int action = 0;
    outputcolor();
    printf("--- Inserez le nom de la série temporelle à analyser ---\n");
    purple();
    printf(">>> ");
    white();
    scanf("%s",nom);
    char chemin[100];
    strcpy(chemin,CHEMIN);
    strcat(chemin,nom); // chemin exacte du fichier
    int taille=0;
    while(1){
        blue();
        printf("--- Selectionnez statistique à calculer ---\n");
        white();
        printf("  1 : Moyenne\n");
        printf("  2 : Min\n");
        printf("  3 : Max\n");
        printf("  4 : Écart type\n");
        printf("  5 : Mediane\n");
        printf("  6 : Quartiles\n");
        printf("  7 : Revenir au menu\n");
        purple();
        printf(">>> ");
        white();
        scanf("%d",&action);
        double *tab;
        tab = (double*) malloc(300000*sizeof(double)); // table où seront stockées les données
        switch(action){
            case 1: 
                outputcolor();
                printf("*** MOYENNE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i); // selection des Données relatives à la variable i
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),moy(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite1;
            case 2:
                outputcolor();
                printf("*** MINIMUM ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),min(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite1;
            case 3:
                outputcolor();
                printf("*** MAXIMUM ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),max(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite1;
            case 4:
                double m = 0.0;
                outputcolor();
                printf("*** ECART TYPE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i);
                    m = moy(tab,taille);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),ecart(tab,m,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite1;
            case 5:
                outputcolor();
                printf("*** MEDIANE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),mediane(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite1;
            case 6:
                outputcolor();
                printf("*** QUARTILES ***\n");
                white();
                printf("-------------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = dataSelect(chemin,tab,i);
                    printf("| %-30s | Premier quartile   %10lf  |\n",remonterNomVariable(i),quartile25(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("| %-30s | Deuxième quartile  %10lf  |\n",remonterNomVariable(i),quartile50(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("| %-30s | Troisième quartile %10lf  |\n",remonterNomVariable(i),quartile75(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("|   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * |\n");
                    printf("-------------------------------------------------------------------\n");
                }
                goto suite1;
            case 7:
                free(tab);
                goto exitloop1;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable\n");
                white();
                goto suite1;
        }
        suite1: ;
        free(tab);
    }
    exitloop1: ;
}

// Sous menu pour aggréger données selon les wafer
void sousMenu2(){
    int action = 0;
    while(1){
        blue();
        printf("--- Menu Wafer ---\n");
        white();
        printf("  1 : Afficher tous les wafer\n");
        printf("  2 : Afficher les moyennes pour un wafer précis\n");
        printf("  3 : Sauvegarder les statistiques par wafer dans un fichier\n");
        printf("  4 : Revenir au menu\n");
        purple();
        printf(">>> ");
        white();
        scanf("%d",&action);
        switch(action){
            case 1:
                blue();
                printf("--- Liste exhaustive de tous les wafer ---\n");
                white();
                printf("---------------------------------------\n");
                double *tab9;
                tab9 = (double *) malloc(300000*sizeof(double));
                int number;
                int number2;
                number = allDataSelect(tab9,22);
                number2 = remove_duplicate(tab9,number); // on enlève ici les doublons
                for(int i=0;i<number2;i++){
                    outputcolor();
                    printf("| WAFER_ID ");
                    white();
                    printf("  = %-20lf   |\n",tab9[i]);
                    printf("---------------------------------------\n");
                }
                goto suit2;
            case 2: // on selectionne ici un wafer précis
                double *tab1;
                tab1 = (double*) malloc(300000*sizeof(double));
                double wafer = 0;
                int taille3 = 0;
                blue();
                printf("--- Statistiques pour un wafer ---\n");
                outputcolor();
                printf("*** Écrire l'ID du wafer à étudier ***\n");
                purple();
                printf(">>> ");
                white();
                scanf("%lf",&wafer);
                printf("---------------------------------------\n");
                outputcolor();
                printf("*** WAFER_ID = ");
                white();
                printf("%lf ***\n",wafer);
                for (int i=1;i<21;i++){
                        taille3 = dataSelectByWafer(wafer,tab1,i); // données triées selon le wafer
                        outputcolor();
                        printf("+ %s\n",remonterNomVariable(i));
                        white(); 
                        printf("\t Maximum = %-20lf\n",max(tab1,taille3));
                        printf("\t Minimum = %-20lf\n",min(tab1,taille3));
                        printf("\t Moyenne = %-20lf\n",moy(tab1,taille3));
                }
                printf("---------------------------------------\n");
                free(tab1);
                goto suit2;
            case 3:
                double *tab2;
                tab2 = (double*) malloc(300000*sizeof(double));
                double wafer1 = 327446714;
                int taille4 = 0;
                char nom[50];
                char chemin[100];
                outputcolor();
                red();
                printf("ATTENTION: ");
                white();
                printf("Cette opération peut prendre quelques minutes (< 1min)\n ");
                outputcolor();
                printf("*** Écrivez le nom à donner au ficheir ***\n");
                purple();
                printf(">>> ");
                white();
                scanf("%s",nom);
                strcpy(chemin,CHEMIN2);
                strcat(chemin,nom); // chemin pour fichier de sortie
                FILE *fichier;
                fichier = fopen(chemin,"w+");
                if(fichier==NULL){
                    red();
                    printf("ERROR: Impossible d'ouvrir le fichier");
                    white();
                    goto suit2;
                }
                int nombreWafer;
                int tailleReduite;
                double *toutWafer;
                toutWafer = (double *) malloc(300000*sizeof(double));
                nombreWafer = allDataSelect(toutWafer,22);
                tailleReduite = remove_duplicate(toutWafer,nombreWafer); // liste contenant tous les wafer
                fprintf(fichier,"WAFER_ID\tCHAMBER\tUSAGE_OF_BACKING_FILM\tUSAGE_OF_DRESSER\tUSAGE_OF_POLISHING_TABLE\tUSAGE_OF_DRESSER_TABLE\tPRESSURIZED_CHAMBER_PRESSURE\tMAIN_OUTER_AIR_BAG_PRESSURE\tCENTER_AIR_BAG_PRESSURE\tRETAINER_RING_PRESSURE\tRIPPLE_IR_BAG_PRESSURE\tUSAGE_OF_MEMEBRANE\tUSAGE_OF_PRESSURIZED_SHEET\tSLURRY_FLOW_LINE_A\tSLURRY_FLOW_LINE_B\tSLURRY_FLOW_LINE_C\tWAFER_ROTATION\tSTAGE_ROTATION\tHEAD_ROTATION\tDRESSING_WATER_STATUS\tEDGE_AIR_BAG_PRESSURE\n");
                for(int i=0;i<tailleReduite;i++){ // pour chaque wafer on calcule les stat pour les 20 variables
                    wafer1 = toutWafer[i];
                    fprintf(fichier,"%lf\t",wafer1);
                    for (int k=1;k<21;k++){
                        taille4 = dataSelectByWafer(wafer1,tab2,k);
                        fprintf(fichier,"%lf\t",moy(tab2,taille4));
                    }
                    fprintf(fichier,"\n");
                }
                fclose(fichier);
                free(tab2);
                free(toutWafer);
                goto suit2;
            case 4:
                goto exitloop2;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable");
                white();
                goto suit2;
        }
        suit2: ;
    }
    exitloop2: ;
}

// Sous menu pour traiter et étudier toutes les données au même temps
void sousMenu3(){
    int action = 0;
    char variable[50];
    while(1){
        blue();
        printf("--- Statistiques de l'ensemble des variables ---\n");
        white();
        printf("  1 : Min\n");
        printf("  2 : Max\n");
        printf("  3 : Moyenne\n");
        printf("  4 : Mediane\n");
        printf("  5 : ecart type\n");
        printf("  6 : Quartiles\n");
        printf("  7 : sauvegarder statistiques dans un fichier\n");
        printf("  8 : Revenir au menu principal\n");
        purple();
        printf(">>> ");
        white();
        scanf("%d",&action);
        double *tab;
        tab = (double*) malloc(300000*sizeof(double));
        switch(action){
            case 1:
                outputcolor();
                printf("*** MINIMUM ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    int taille;
                    taille = allDataSelect(tab,i)-1;
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),min(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite3;
            case 2:
                outputcolor();
                printf("*** MAXIMUM ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    int taille;
                    taille = allDataSelect(tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),max(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite3;
            case 3:
                int taille =0;
                outputcolor();
                printf("*** MOYENNE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),moy(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite3;
            case 4:
                outputcolor();
                printf("*** MEDIANE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),mediane(tab,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite3;
            case 5:
                double m = 0.0;
                outputcolor();
                printf("*** ECART TYPE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    m = moy(tab,taille);
                    printf("| %-30s | %-25lf |\n",remonterNomVariable(i),ecart(tab,m,taille));
                    printf("--------------------------------------------------------------\n");
                }
                goto suite3;
            case 6:
                outputcolor();
                printf("*** QUARTILES ***\n");
                white();
                printf("-------------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    printf("| %-30s | Premier quartile   %10lf  |\n",remonterNomVariable(i),quartile25(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("| %-30s | Deuxième quartile  %10lf  |\n",remonterNomVariable(i),quartile50(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("| %-30s | Troisième quartile %10lf  |\n",remonterNomVariable(i),quartile75(tab,taille));
                    printf("-------------------------------------------------------------------\n");
                    printf("|   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * |\n");
                    printf("-------------------------------------------------------------------\n");
                }
                goto suite3;
            case 7:
                char chemin[100];
                char nom[50];
                blue();
                printf("--- Écrivez le nom qu'il faut donner au fichier de savegarde ---\n");
                purple();
                printf(">>> ");
                white();
                scanf("%s",nom);
                strcpy(chemin,CHEMIN2);
                strcat(chemin,nom);
               
                FILE *fichier;
                fichier = fopen(chemin,"w+");
                if(fichier==NULL){
                    red();
                    printf("ERROR: Impossible d'ouvrir le fichier\n");
                    white();
                    goto suite3;
                } // on écrit les statistiques pour chaque variable
                fprintf(fichier,"\t\t\t\t STATISTIQUES \n");
                fprintf(fichier,"\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    fprintf(fichier,"***   %20s   *** \n",remonterNomVariable(i));
                    fprintf(fichier,"Minimum = %lf \t",min(tab,taille));
                    fprintf(fichier,"Maximum = %lf \t",max(tab,taille));
                    fprintf(fichier,"Moyenne = %lf \t",moy(tab,taille));
                    fprintf(fichier,"Médiane = %lf \t",mediane(tab,taille));
                    fprintf(fichier,"Écart Type = %lf \t",ecart(tab,moy(tab,taille),taille));
                    fprintf(fichier,"Quartile 25 = %lf \t",quartile25(tab,taille));
                    fprintf(fichier,"Quartile 75 = %lf \t",quartile75(tab,taille));
                    fprintf(fichier,"\n");
                    fprintf(fichier,"\n");
                }
                fclose(fichier);
                
                goto suite3;
            case 8:
                free(tab);
                goto exitloop3;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable\n");
                white();
                goto suite3;
        }
    suite3: ;
    free(tab);
    }
    
    exitloop3: ;
}

// Sous menu pour la détection des valeurs atypiques
void sousMenu5(){
    int action = 0;
    int coefficient=0;
    while(1){
        blue();
        printf("--- Détection des valeurs atypiques ---\n");
        red();
        printf("ATTENTION: ");
        white();
        printf("Les changements seronts permanents jusqu'à la fermeture du programme\n");
        printf("  1 : Continuer\n");
        printf("  2 : Revenir au menu principal\n");
        purple();
        printf(">>> ");
        white();
        scanf("%d",&action);
        switch(action){
            case 1:
                double *tab;
                tab = (double*) malloc(300000*sizeof(double));
                int taille = 0;
                outputcolor();
                printf("--- Inserez le coefficient (généralement {2,3}) ---\n");
                purple();
                printf(">>> ");
                white();
                white();
                scanf("%d",&coefficient);
                double *ecartType;
                ecartType = (double * ) malloc(21*sizeof(double));
                double m = 0.0;
                outputcolor();
                printf("*** ECART TYPE ***\n");
                white();
                printf("--------------------------------------------------------------\n");
                for(int i=1;i<21;i++){
                    taille = allDataSelect(tab,i);
                    m = moy(tab,taille);
                    ecartType[i] = ecart(tab,m,taille); // on cree une liste avec tout les ecart types
                }
                valeursAtypiques(coefficient,&tete,ecartType); // cette fonction remplace les valeurs atypiques par -1
                
                printf("++ Les valeurs anormales ont été supprimées avec succés ++\n");
                printf("--------------------------------------------------------------\n");
                free(ecartType);
                free(tab);
                goto suite78;
            case 2:
                goto exitloop78;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable\n");
                white();
                goto suite78;
        }
        suite78: ;
    }
    exitloop78: ;
}

// Sous menu pour dessiner les histogrammes
void sousMenu6(){
    char *variables[] =  {"CHAMBER","USAGE_OF_BACKING_FILM","USAGE_OF_DRESSER","USAGE_OF_POLISHING_TABLE","USAGE_OF_DRESSER_TABLE","PRESSURIZED_CHAMBER_PRESSURE","MAIN_OUTER_AIR_BAG_PRESSURE","CENTER_AIR_BAG_PRESSURE","RETAINER_RING_PRESSURE","RIPPLE_IR_BAG_PRESSURE","USAGE_OF_MEMEBRANE","USAGE_OF_PRESSURIZED_SHEET","SLURRY_FLOW_LINE_A","SLURRY_FLOW_LINE_B","SLURRY_FLOW_LINE_C","WAFER_ROTATION","STAGE_ROTATION","HEAD_ROTATION","DRESSING_WATER_STATUS","EDGE_AIR_BAG_PRESSURE"};
    int action = 0;
    while(1){
        blue();
        printf("--- Selectionnes la varibale dont vous voulez afficher l'histogramme ---\n");
        white(); //possibilié de choisir la varibale à affihcher
        for(int i=0;i<20;i++){
            printf("  %-2d : %s\n",i+1,variables[i]);
        }
        printf("  21 : Revenir au menu principal\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&action);
        switch(action){
            case 1:
                goto suite35;
            case 2:
                goto suite35;
            case 3:
                goto suite35;
            case 4:
                goto suite35;
            case 5:
                goto suite35;
            case 6:
                goto suite35;
            case 7:
                goto suite35;
            case 8:
                goto suite35;
            case 9:
                goto suite35;
            case 10:
                goto suite35;
            case 11:
                goto suite35;
            case 12:
                goto suite35;
            case 13:
                goto suite35;
            case 14:
                goto suite35;
            case 15:
                goto suite35;
            case 16:
                goto suite35;
            case 17:
                goto suite35;
            case 18:
                goto suite35;
            case 19:
                goto suite35;
            case 20:
                goto suite35;
            case 21:
                goto exitloop35;
            default:
                red();
                printf("ERROR: Cette opération n'est pas valable\n");
                white();
                goto suite351;

        }
        suite35: ;
        double *data;
        data = (double * ) malloc(300000*sizeof(double));
        int taille = 0;
        taille = allDataSelect(data,action);
        outputcolor();
        printf("--- Histrogramme de \'%s\' ---\n",variables[action]);
        white();
        printf("--------------------------------------------------------------\n");
        histogramme(data,taille); // appel à une fonction externe pour créer l'histogramme
        printf("--------------------------------------------------------------\n");
        suite351: ;
    }
    exitloop35: ;
}


//            ---  SELECTEUR DE DONNÉES  ---

// Ces 3 fonctions permettent de récuperer les données à partir de la liste chainée
// elles permettent aussi de choisir la variable dont on veut les données.
// elles prennent en argument un tableau le modifient; eles renvient aussi la taille de ce tableau

// Cette fonction ne recupére que les données relatives à un fichier précis
int dataSelect(char fichier[100],double *tab,int variable){
    int i=0;
    line *courant;
    courant = tete.tete;
    while(courant!=NULL){
        //printf("test\n");
        if(strcmp(courant->fichier,fichier)==0){
            switch(variable){
                case 1:
                    tab[i]= courant->CHAMBER;
                    i++;
                    goto loop;
                case 2:
                    tab[i]= courant->USAGE_OF_BACKING_FILM;
                    i++;
                    goto loop;
                case 3:
                    tab[i]= courant->USAGE_OF_DRESSER;
                    i++;
                    goto loop;
                case 4:
                    tab[i] = courant->USAGE_OF_POLISHING_TABLE;
                    i++;
                    goto loop;
                case 5:
                    tab[i] = courant->USAGE_OF_DRESSER_TABLE;
                    i++;
                    goto loop;
                case 6:
                    tab[i] = courant->PRESSURIZED_CHAMBER_PRESSURE;
                    i++;
                    goto loop;
                case 7:
                    tab[i] = courant->MAIN_OUTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 8:
                    tab[i] = courant->CENTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 9:
                    tab[i] = courant->RETAINER_RING_PRESSURE;
                    i++;
                    goto loop;
                case 10:
                    tab[i] = courant->RIPPLE_IR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 11:
                    tab[i] = courant->USAGE_OF_MEMEBRANE;
                    i++;
                    goto loop;
                case 12:
                    tab[i] = courant->USAGE_OF_PRESSURIZED_SHEET;
                    i++;
                    goto loop;
                case 13:
                    tab[i] = courant->SLURRY_FLOW_LINE_A;
                    i++;
                    goto loop;
                case 14:
                    tab[i] = courant->SLURRY_FLOW_LINE_B;
                    i++;
                    goto loop;
                case 15:
                    tab[i] = courant->SLURRY_FLOW_LINE_C;
                    i++;
                    goto loop;
                case 16:
                    tab[i] = courant->WAFER_ROTATION;
                    i++;
                    goto loop;
                case 17:
                    tab[i] = courant->STAGE_ROTATION;
                    i++;
                    goto loop;
                case 18:
                    tab[i] = courant->HEAD_ROTATION;
                    i++;
                    goto loop;
                case 19:
                    tab[i] = courant->DRESSING_WATER_STATUS;
                    i++;
                    goto loop;
                case 20:
                    tab[i] = courant->EDGE_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 21:
                    tab[i] = courant->TIMESTAMP;
                    i++;
                    goto loop;
            }
            
        }
        loop: ;
        courant = courant->suivant;
    }
    return i;
}

// cette fonction récupére la Data de tous les fichiers, cette Data est relative à une varible
int allDataSelect(double *tab,int variable){
    line *courant;
    int i =0;
    courant = tete.tete;
    while(courant!=NULL){
        switch(variable){
                case 1:
                    tab[i]= courant->CHAMBER;
                    i++;
                    goto loop14;
                case 2:
                    tab[i]= courant->USAGE_OF_BACKING_FILM;
                    i++;
                    goto loop14;
                case 3:
                    tab[i]= courant->USAGE_OF_DRESSER;
                    i++;
                    goto loop14;
                case 4:
                    tab[i] = courant->USAGE_OF_POLISHING_TABLE;
                    i++;
                    goto loop14;
                case 5:
                    tab[i] = courant->USAGE_OF_DRESSER_TABLE;
                    i++;
                    goto loop14;
                case 6:
                    tab[i] = courant->PRESSURIZED_CHAMBER_PRESSURE;
                    i++;
                    goto loop14;
                case 7:
                    tab[i] = courant->MAIN_OUTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop14;
                case 8:
                    tab[i] = courant->CENTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop14;
                case 9:
                    tab[i] = courant->RETAINER_RING_PRESSURE;
                    i++;
                    goto loop14;
                case 10:
                    tab[i] = courant->RIPPLE_IR_BAG_PRESSURE;
                    i++;
                    goto loop14;
                case 11:
                    tab[i] = courant->USAGE_OF_MEMEBRANE;
                    i++;
                    goto loop14;
                case 12:
                    tab[i] = courant->USAGE_OF_PRESSURIZED_SHEET;
                    i++;
                    goto loop14;
                case 13:
                    tab[i] = courant->SLURRY_FLOW_LINE_A;
                    i++;
                    goto loop14;
                case 14:
                    tab[i] = courant->SLURRY_FLOW_LINE_B;
                    i++;
                    goto loop14;
                case 15:
                    tab[i] = courant->SLURRY_FLOW_LINE_C;
                    i++;
                    goto loop14;
                case 16:
                    tab[i] = courant->WAFER_ROTATION;
                    i++;
                    goto loop14;
                case 17:
                    tab[i] = courant->STAGE_ROTATION;
                    i++;
                    goto loop14;
                case 18:
                    tab[i] = courant->HEAD_ROTATION;
                    i++;
                    goto loop14;
                case 19:
                    tab[i] = courant->DRESSING_WATER_STATUS;
                    i++;
                    goto loop14;
                case 20:
                    tab[i] = courant->EDGE_AIR_BAG_PRESSURE;
                    i++;
                    goto loop14;
                case 21:
                    tab[i] = courant->TIMESTAMP;
                    i++;
                    goto loop14;
                case 22:
                    tab[i] = courant->WAFER_ID;
                    i++;
                    goto loop14;
        }
        loop14: ;
        courant = courant->suivant;
    }
    return i;
}

// Récupère la Data reaive à un wafer precis
int dataSelectByWafer(double wafer,double *tab,int variable){
    int i=0;
    line *courant;
    courant = tete.tete;
    while(courant!=NULL){
        //printf("test\n");
        if(courant->WAFER_ID==wafer){
            switch(variable){
                case 1:
                    tab[i]= courant->CHAMBER;
                    i++;
                    goto loop;
                case 2:
                    tab[i]= courant->USAGE_OF_BACKING_FILM;
                    i++;
                    goto loop;
                case 3:
                    tab[i]= courant->USAGE_OF_DRESSER;
                    i++;
                    goto loop;
                case 4:
                    tab[i] = courant->USAGE_OF_POLISHING_TABLE;
                    i++;
                    goto loop;
                case 5:
                    tab[i] = courant->USAGE_OF_DRESSER_TABLE;
                    i++;
                    goto loop;
                case 6:
                    tab[i] = courant->PRESSURIZED_CHAMBER_PRESSURE;
                    i++;
                    goto loop;
                case 7:
                    tab[i] = courant->MAIN_OUTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 8:
                    tab[i] = courant->CENTER_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 9:
                    tab[i] = courant->RETAINER_RING_PRESSURE;
                    i++;
                    goto loop;
                case 10:
                    tab[i] = courant->RIPPLE_IR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 11:
                    tab[i] = courant->USAGE_OF_MEMEBRANE;
                    i++;
                    goto loop;
                case 12:
                    tab[i] = courant->USAGE_OF_PRESSURIZED_SHEET;
                    i++;
                    goto loop;
                case 13:
                    tab[i] = courant->SLURRY_FLOW_LINE_A;
                    i++;
                    goto loop;
                case 14:
                    tab[i] = courant->SLURRY_FLOW_LINE_B;
                    i++;
                    goto loop;
                case 15:
                    tab[i] = courant->SLURRY_FLOW_LINE_C;
                    i++;
                    goto loop;
                case 16:
                    tab[i] = courant->WAFER_ROTATION;
                    i++;
                    goto loop;
                case 17:
                    tab[i] = courant->STAGE_ROTATION;
                    i++;
                    goto loop;
                case 18:
                    tab[i] = courant->HEAD_ROTATION;
                    i++;
                    goto loop;
                case 19:
                    tab[i] = courant->DRESSING_WATER_STATUS;
                    i++;
                    goto loop;
                case 20:
                    tab[i] = courant->EDGE_AIR_BAG_PRESSURE;
                    i++;
                    goto loop;
                case 21:
                    tab[i] = courant->TIMESTAMP;
                    i++;
                    goto loop;
            }
            
        }
        loop: ;
        courant = courant->suivant;
    }
    return i;
}



//    ---  PROGRAMME PRINCIPAL MAIN  ---
int main(){
    tete.tete = NULL;
    nomFichiers(&tete);
    Menu();
    return 0;


}
