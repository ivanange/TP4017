#ifndef utils
#define utils

#include "data_structures.h"
#include "vars.h"
#include <string.h>
/*
* Initialise algorithm
*/
void init();

/*
* Evaluates the S(j)s
*/
void eval();

/*
* Tinker around to find other trial solutions at critical events
* @param Solution* feasible 
* @param Solution* infeasible 
*/
void tinker(Solution* feasible, Solution* infeasible );

/*
* Tinker around to find other trial solutions from feasible solution
* @param Solution* feasible 
*/
void tinkerFeasible(Solution* feasible);

/*
* Tinker around to find other trial solutions from infeasible solution
* @param Solution* infeasible 
*/
void tinkerInfeasible(Solution* infeasible );

/*
* Construct new solution from current solution by inverting given variable
* @param Variable* variable 
*/
Solution makeMove(Variable *variable);

/*
* Construct new solution from a given solution by inverting given variable
* @param Variable* variable 
* @param Solution* move 
*/
Solution makeMoveFromSolution(Variable *variable, Solution *move);

/*
* Get a value for span : a random number between 1 and 6 
*/
int getSpan();

/*
* Check if specified solution is feasible
* @param Solution* move 
*/
int admissible(Solution *move);

/*
* Evaluate specified solution
* @param Solution* move 
*/
float evalObjective(Solution *move);

/*
* Add solution to Tabu list and update variables accordingly
* @param Solution solution 
*/
void addSolution(Solution solution);

/*
* Returns possible moves in order of their potential value in ASC or DESC order 
* depending on current phase ( contructive or destruvtive)
* @return Selection 
*/
Selection getSelection();

/*
* Procedure representing construcive phase
*/
void construct();

/*
* Procedure representing destrucive phase
*/
void destroy();

/*
* Procedure representing transfer phase
*/
void transfer();

/*
* Performs dot product of 2 vectors, one made of INTs the other of FLOATs
* @param int* v1
* @param int* v2
* @param int size
* @return float
*/
float scalaire( int *v1, float *v2, int size);

/*
* Count the number of occurences of a number (integer) in an array ( of integers)
* @param int* array 
* @param int size 
* @param int* val value to search 
*/
int count( int *array, int size, int val);


/*
* Change currentSolution to new solution
* @param Solution* move 
*/
void changeSolution( Solution *move);

#endif