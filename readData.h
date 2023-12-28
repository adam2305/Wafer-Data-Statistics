// Lire toutes les données contenues dans les fichiers


/*-------------------------------------------------------------------------------------------------------*/
//                              +++ PARTIE À MODIFIER PAR L'UTILISATEUR +++

// *** Chemin vers le dossier ou sont stockées toutes les données ***
#define CHEMIN "/home/adam/Documents/ISMIN/AlgoProg/SEBTI_ZBIRI_PROJET/training/"
// *** CHemin vers l'endroit où on veut sauvegarder les résultats
#define CHEMIN2 "/home/adam/Documents/ISMIN/AlgoProg/SEBTI_ZBIRI_PROJET/output/"

/*--------------------------------------------------------------------------------------------------------*/



// On utilisera une liste chainee dont chaque élement caractérise une ligne du fichier
// Structure de l'acquisition des données (liste chainée)
typedef struct Line{
    char fichier[100];
    double MACHINE_ID;
    double MACHINE_DATA;
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
    struct Line *suivant;
}line;
// Structure pour stocker la tete de la liste chainée
typedef struct Head{
    struct Line *tete ;
}head;

// Prototype
void dataOneSerie(char *fich,head *tete);
void nomFichiers(head *tete);
void tri_iteratif(char *tableau[], int taille);
void valeursAtypiques(int coefficient,head *tete,double ecartType[21]);
