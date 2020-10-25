
#define NOMBRE_MAX_SOMMETS 10000
#define INFINITY 2147483647
#define TAILLE_MAX 1000

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

typedef struct Arete Arete;
struct Arete
{
    Noeud *source;
    Noeud *destination;
    int poids;
};

typedef struct Cellule Cellule;
struct Cellule
{
    Noeud *sommet;
    Cellule *suivant;
};

typedef struct File File;
struct File
{
    Cellule *premier;
};

void enfiler(File *file, Noeud *nvNoeud);
void afficherFile(File *file);
Noeud* extraireMin(File *file);
int rechercheFile(File *file, int n);

Noeud* creer_ensemble(int x);
Noeud* Trouver_ensemble(Noeud* n);
void Lier(Noeud* x,Noeud* y);
void Unifier(Noeud* x,Noeud* y);
void Tri(Arete *tableau, int taille);
void Kruskal(Arete *tab, int taille);

Liste *parseLine( char *line );
Element *makeElement( char *item );
Graph *makeGraph( const char *filename );
int countArcs( Graph *graph);
Noeud **makeSommets(Graph *graph);