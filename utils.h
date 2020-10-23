
#define NOMBRE_MAX_SOMMETS 10000

typedef struct Element Element;
struct Element
{
    int valeur;
    int poids;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *tete;
};

typedef struct Graph Graph;
struct Graph
{
    Liste *sommets[NOMBRE_MAX_SOMMETS];
    int taille;
};

Liste *parseLine( char *line );
Element *makeElement( char *item );