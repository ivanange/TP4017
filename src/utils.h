
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
    int taille;
};

typedef struct Graph Graph;
struct Graph
{
    Liste **sommets;
    int taille;
};

Liste *parseLine( char *line );
Element *makeElement( char *item );
Graph *makeGraph( const char *filename );