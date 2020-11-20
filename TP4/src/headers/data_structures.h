#ifndef data_structures
#define data_structures

#define TAILLE_MAX 10

#include <stdlib.h>
#include <stdio.h>

/* Constrains */
typedef struct Constrains {
    float **lhs;
    float *rhs;
} Constrains;

/*
* Create a mxn constrain matrix
* @param int n
* @param int m
*/
Constrains *ConstrainsInit(int m, int n);


/*
* Abstraction of a vairable
*/
typedef struct Variable {
	int value;
	int frequency;
	int index;
	float PEN_F;
	float PEN_R;
    char name[TAILLE_MAX];
} Variable;


/*
* Variable list
*/
typedef  struct Variables {
	Variable *value;
} Variables;


/*
* Abstraction of a solution
*/
typedef struct Solution {
	int *value;
} Solution;


/*
* Selection, represents possible moves sorted in specified order
*/
typedef struct Selection {
	Solution *moves;
	int size;
} Selection;


/*
* Abstraction of the objective function
*/
typedef struct ObjectiveFunction {
    float *value;
} ObjectiveFunction;



/*
* Tabu list: fixed size queue
*/
typedef struct Tabulist {
	int size;
	int max_size;
	Solution *list;
} Tabulist;

/*
* Create a tabu list
* @param int size
* @return Tabulist*
*/
Tabulist *TabulistInit(int size);

/*
* Add solution to Tabu list
* @param Tabulist* q
*/
void TabulistPush(Tabulist *q, Solution a);

/*
* Get last solution in Tabu list
* @param Tabulist* q
* @return Solution*
*/
Solution *TabulistHead(Tabulist *q);

/*
* Delete Tabu list
* @param Tabulist q
*/
void TabulistFree(Tabulist *q);


#endif