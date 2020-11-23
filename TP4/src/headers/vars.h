#ifndef vars
#define vars

#define INFINITE 2147483647
#define false 0
#define true 1

#include <stdlib.h>
#include <stdio.h>
#include "data_structures.h"

/* Global variables */

/*
* @var double 
* constant used in calculating penalty
*/
const double C = 100000;


/*
* @var int 
* variable representing current iteration
*/
int curIter = 0;


/*
* @var int 
* constant representing maximum number of iterations
*/
const int maxIter = 150;


/*
* @var int 
* Number of variables
*/
int N;


/*
* @var int 
* Number of constrains
*/
int M;


/*
* @var int 
* span (amplitude)
*/
int span;


/*
* @var int 
* counter for number of moves already made
*/
int spanCount;


/*
* @var int 
* Var for managing frequency scaling
*/
int K = 1;


/*
* @var int 
* Max value for K
*/
const int KMAX = 4;


/*
* @var int 
* Length of Tabu List
*/
const int TabuTenure = 3;


/*
* calculated PEN_F value
*/
double PEN_F;


/*
* calculated PEN_R value
*/
double PEN_R;


/*
* @var Solution 
* Current solution
*/
Solution curSolution;

/*
* @var Constrain 
* Contrains of the problem
*/
Constrains *constrains;


/*
* @var ObjectiveFunction 
* Objective function of the problem
*/
ObjectiveFunction objectiveFunction;


/*
* @var *Variables 
* Variables of the problem
*/
Variable *variables;


/*
* @var Tabulist 
* Current solution
*/
Tabulist *tabulist;


/*
* @var boolean 
* Wether the current solution is feasible
*/
int feasible = 1;

/*
* @var boolean 
* Wether we are in a constructive phase or not
*/
int constructive = 1;


#endif