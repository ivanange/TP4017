#ifndef data_structures
#define data_structures

#define TAILLE_MAX 10

#include <stdlib.h>
#include <stdio.h>

/* 
* Representation of Constrains 
*/
typedef struct Constrains {
	// matrix representing left hand side of containt equations (Aij)
    float **lhs;

	// vector representing right hand side of containt equations (Bi)
    float *rhs;
} Constrains;

/*
* Create a mxn constrain lhs matrix
* @param int n
* @param int m
*/
Constrains *ConstrainsInit(int m, int n);


/*
* Abstraction of a vairable
*/
typedef struct Variable {
	// current value of variable ( in current solution)
	int value;

	// frequency of the variable at cuurent itération
	int frequency;

	// recency of the variable at cuurent itération
	int recency;
	
	/* 
	* position of the variable in the different 
	* representations ( solution, contrains, objective function ...)
	*/
	int index;

	// optional variable name
    char name[TAILLE_MAX];
} Variable;


/*
* Variable list
*/
typedef  struct Variables {
	Variable *value;
} Variables;


/*
* Abstraction of a solution : a vector of solution values
* example : {
*	value: (0, 0, 1, 0, 1, 1)
* }
*/
typedef struct Solution {
	int *value;
} Solution;


/*
* Selection, represents possible moves sorted in specified order
*/
typedef struct Selection {
	// possible moves
	Solution *moves;

	// size of the selection
	int size;
} Selection;


/*
* Abstraction of the objective function : a vector of objective function coeficients
* example : {
*	value: (3.5, 80, 12, 7, 16, 9)
* }
*/
typedef struct ObjectiveFunction {
    float *value;
} ObjectiveFunction;



/*
* Tabu list: fixed size queue
*/
typedef struct Tabulist {
	/* // position of Tabulist head */
	int size;

	// max size of the list
	int max_size;

	// the list itself ( vector of solutions)
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