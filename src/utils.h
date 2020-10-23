
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



typedef struct Noeud Noeud;
struct Noeud
{
    int valeur;
    int rang;
    Noeud *parent;
};

Noeud* creer_ensemble(int x);
Noeud* Trouver_ensemble(Noeud* n);
void Lier(Noeud* x,Noeud* y);
void Unifier(Noeud* x,Noeud* y);


typedef struct Arete Arete;
struct Arete
{
    Noeud *source;
    Noeud *destination;
    int poids;
};

void Kruskal(Arete *tab, int taille);

Liste *parseLine( char *line );
Element *makeElement( char *item );
Graph *makeGraph( const char *filename );