#include <string.h>
#include <math.h>
#include "headers/utils.h"
#include "headers/vars.h"



void init(FILE *file) {

    int i, j;

    parseFile(file);

    // create initial solution
    curSolution.value = malloc(sizeof(int)*N);
    variables = malloc(sizeof(Variable)*N);
    for(i=0; i<N; i++) {
        Variable variable;
        variable.frequency = 0;
        variable.recency = 0;
        variable.value = 0;
        variable.index = i;
        variable.name = malloc(sizeof(char)*(ceil(log10(i))+1));
        sprintf(variable.name+1, "%d", i);
        variable.name[0] = 'X';

        variables[i] = variable;

        curSolution.value[i] = 0;
    }

    // create tabu list
    tabulist = TabulistInit(TabuTenure);


    // calculate PEN_R and PEN_F
    PEN_R = 0;

    for (j = 0; j < N; j++)
    {
        float sum = 0;
        for (i = 0; i < M; i++)
        {
            sum += constrains.lhs[i][j] / constrains.rhs[i];
        }

        PEN_R = PEN_R < sum ? sum : PEN_R;
        
    }
     

    PEN_F = PEN_R/C;
}

void construct(){
    if(spanCount < span) {

        // increment span counter
        spanCount++;

        // get moves in descending order
        Selection selection = getSelection();
        Solution *moves = selection.moves;
        Solution *move;
        Solution *infeasible;
        if(feasible) {
            // if solution still feasible ( step C1)

            // find a feasible move
            for(int i = 0; i < selection.size; i++) {
                if(admissible(moves+i)) {
                    move = moves+i;
                    break;
                }
                else if(infeasible == NULL) infeasible = moves+i;
            }

            if(move != NULL) {
                // found feasible move, update current solution
                changeSolution(move);
            }
            else {
                // no feasible move, check if current solution is a new best then go to C2

                Solution *lastBest = TabulistHead(tabulist);
                if(evalObjective(lastBest) < evalObjective(&curSolution)) {
                    // new best solution
                    addSolution(curSolution);
                }
                feasible = false;
                tinker(&curSolution, infeasible);
                construct();
            }
        }
        else {
            // if solution is no more feasible ( step C2)

            if(selection.size == 0) {
                // no moves posssible
                transfer();
            }
            else {
                // do a move, and continue construction
                changeSolution(moves);
                construct();
            }

        }
        free(selection.moves);

    }
    else {
        transfer();
    }
}

void transfer() {
    spanCount = 0;
    constructive = constructive ? false : true;

    if(N > 6) {
        span = getSpan();
    }
}

void destroy(){
   if(spanCount < span) {

        // increment span counter
        spanCount++;

        // get moves in ascending order of value 
        Selection selection = getSelection();
        Solution *moves = selection.moves;
        Solution *move;
        Solution *infeasible;

        if(!feasible) {
            // if solution is not feasible ( step D1)

            // retain infeasible move
            infeasible = &curSolution;

            // do a move
            changeSolution(move = moves);

            // if move is feasible go to D2, else continue in D1
            if(admissible(move)) {
                feasible = true;
                Solution *lastBest = TabulistHead(tabulist);
                if(evalObjective(lastBest) < evalObjective(move)) {
                    // new best solution
                    addSolution(*move);
                }
                tinker(move, infeasible);
            }
            destroy(); // move to D2 or D1 depending on above outcome
            
        }
        else {
            // if solution is feasible ( step D2)

            if(selection.size == 0) {
                // no moves posssible
                transfer();
            }
            else {
                // do a move, and continue destruction
                changeSolution(moves);
                destroy();
            }

        }
        free(selection.moves);

    }
    else {
        transfer();
    }
}

Solution makeMove(Variable *variable) {
    return makeMoveFromSolution(variable, &curSolution);
}

Solution makeMoveFromSolution(Variable *variable, Solution *move ) {
    move = move ? move : &curSolution;
    Solution newMove;
    float size = sizeof(move->value);
    newMove.value = malloc(size);
    memcpy(newMove.value, move->value, size);
    newMove.value[variable->index] = newMove.value[variable->index] ? 1 : 0;
    return newMove;
}

void addSolution(Solution solution) {

    static int indicator = 0, i;

    indicator++;

    // decrease recency of concerned variables when removing last TT+1 solution
    if(indicator > tabulist->max_size ) {
        indicator = 0;
        Solution last = tabulist->list[tabulist->size];
        for(i = 0; i < N; i++) {
          if(last.value[i] == 1) variables[i].recency--;  
        }
    }

    // add new solution to list
    TabulistPush(tabulist, solution);

    // update frequency and recency of corresponding variables
    for(i = 0; i < N; i++) {
        if(solution.value[i] == 1) {
            variables[i].frequency++;
            variables[i].recency++;
        }  
    }
}

Selection getSelection() {
    
    Selection selection;
    Solution temp;
    int size, i, j, k, test, *candidates;
    float B, *value;

    test = constructive ? 0 : 1;
    size = count(curSolution.value, N, test);
    selection.size = size;
    selection.moves = malloc(sizeof(Solution)*size);
    candidates = malloc(sizeof(int)*size);
    value = malloc(sizeof(float)*size);

    j = 0;
    for (i = 0; i < N; i++)
    {
        if (curSolution.value[i] == test)
        {
            candidates[j] = i;
            j++;
        }
    }

    // constrains
    for (j = 0; j < size; j++) {

        k = candidates[j]; // index of the given variable
        selection.moves[j] = makeMove(variables+k);
        value[j] = 0;

        // calculating W(i) && S(j)
        for(i = 0; i < M; i++)
        {
            B = ( B = constrains.rhs[i] - scalaire(selection.moves[j].value, constrains.lhs[i], N)) > 0 ? 1/B : abs(B) + 2;

            value[j] += B*constrains.lhs[i][k]; // S(j) = S(j) + W(i) * A(i,j)
        }

        value[j] = objectiveFunction.value[j]/value[j]; // C(j)/S(j)

        if(spanCount <= K) {
            value[j] -= (PEN_R * variables[k].recency) + (PEN_F * variables[k].frequency); 
        }
    }
    

    if(constructive) {
        // sort in descending order of value
        for (i = 0; i < size-1; i++) {
            for (j = 0; j < size-i-1; j++) {
                if (value[j] < value[j+1]) {
                    temp = selection.moves[j];
                    selection.moves[j] = selection.moves[j+1] ;
                    selection.moves[j+1] = temp; 
                }
            }
        } 
    }
    else
    {
        // sort in ascending order of value
        for (i = 0; i < size-1; i++) {
            for (j = 0; j < size-i-1; j++) {
                if (value[j] > value[j+1]) {
                    temp = selection.moves[j];
                    selection.moves[j] = selection.moves[j+1] ;
                    selection.moves[j+1] = temp; 
                }
            }
        } 
    }

    free(candidates);
    free(value);

    return selection;
    
}

void tinker(Solution* feasible, Solution* infeasible ) {

    if (constructive)
    {
        // in constrcutive phase

        //tinkering with infeasible solution
        tinkerInfeasible(infeasible);

    }

    else {
        // destrcutive phase

        //tinkering with infeasible solution
        tinkerFeasible(feasible);

        //tinkering with feasible solution
        tinkerInfeasible(infeasible);
        
    }
    
}

void tinkerFeasible(Solution* feasible) {

    int a, b, temp, i, j, size, *candidates; 
    Solution *lastBest = TabulistHead(tabulist);

    size = count(curSolution.value, N, 0);
    candidates = malloc(sizeof(int)*size);
    j = 0;
    for (i = 0; i < N; i++)
    {
        if (curSolution.value[i] == 0)
        {
            candidates[j] = i;
            j++;
        }
    }

    // sort in descending order of objective function coeficients
    for (a = 0; a < size-1; a++) {
        for (b = 0; b < size-a-1; b++) {
            if (objectiveFunction.value[candidates[b]] < objectiveFunction.value[candidates[b+1]]) {
                temp = candidates[b];
                candidates[b] = candidates[b+1];
                candidates[b+1] = temp; 
                }
            }
    }       

    for (i = 0; i < size; i++)
    {
        j = candidates[i];
        Solution move = makeMoveFromSolution(variables+j, feasible);
        if(admissible(&move) && evalObjective(&move) > evalObjective(lastBest)) {
            addSolution(move);
        }
    }

    free(candidates);
}

void tinkerInfeasible(Solution* infeasible ) {

    int a, b, temp, i, j, size, *candidates; 
    Solution *lastBest = TabulistHead(tabulist);

    size = count(curSolution.value, N, 1);
    candidates = malloc(sizeof(int)*size);
    j = 0;
    for (i = 0; i < N; i++)
    {
        if (curSolution.value[i] == 1)
        {
            candidates[j] = i;
            j++;
        }
    }

    // sort in ascending order of objective function coeficients
    for (a = 0; a < size-1; a++) {
        for (b = 0; b < size-a-1; b++) {
            if (objectiveFunction.value[candidates[b]] > objectiveFunction.value[candidates[b+1]]) {
                temp = candidates[b];
                candidates[b] = candidates[b+1];
                candidates[b+1] = temp; 
                }
            }
    }       

    for (i = 0; i < size; i++)
    {
        j = candidates[i];
        Solution move = makeMoveFromSolution(variables+j, infeasible);
        if(admissible(&move) && evalObjective(&move) > evalObjective(lastBest)) {
            addSolution(move);
        }
    }

    free(candidates);

}

float evalObjective(Solution *move)
{
    return scalaire(move->value, objectiveFunction.value, N);
}

int admissible(Solution *move)
{
    int result = 0, admi = true;

    for (int i = 0; i < M; ++i)
    {
        result = scalaire(move->value, constrains.lhs[i], N);

        // Une contrainte a été violé admi reçoit faux
        if (result > constrains.rhs[i])
        {
            admi = false;
            break;
        }
    }
    return admi;
}

int count( int *array, int size, int val) {
    int s = 0;
    for (int k = 0; k < size; k++)
    {
       if (array[k] == val)
       {
          s++;
       }
       
    }
    return s;
}

void changeSolution( Solution *move) {
    free(curSolution.value);
    curSolution = *move;
    for (int i = 0; i < N; i++)
    {
        variables[i].value = curSolution.value[i];
    }
}

float scalaire( int *v1, float *v2, int size) {
    int j,result = 0;
    for (j = 0; j < size; ++j)
    {
        result = result + v1[j] * v2[j];
    }
    return result;
}


void parseFile(FILE *file) {

	int optimum, k, i, j;
	char line[1024];
	const char s[2] = " ";
	char* token;

	if (file != NULL)
	{
		// juste la premiere ligne: nombres de variables, contrainte, et valeur objective 
		fscanf(file, "%d %d %d", &N, &M, &optimum); 
		fgetc(file); // go to line


		// La seconde ligne : les coefficients

        objectiveFunction.value = malloc(sizeof(float)*N);
		fgets(line, 1024, file);
		token = strtok(line, s);
		k = 0;

   		/* walk through other tokens */
        while( token != NULL ) {
	        i = atoi(token);
	        *(objectiveFunction.value + k) = i;
	        token = strtok(NULL, s);
	        k = k + 1;
        }


        // create contains matrix
        constrains = *ConstrainsInit(M,N);

        // les M lignes suivantes pour les contraintes

        for (j = 0; j < M; ++j)
        {
        	fgets(line, 1024, file);

        	token = strtok(line, s);
        	float *inter;
        	k = 0;

			inter = constrains.lhs[j];
        	while( token != NULL ) {
		        i = atoi(token);
		        inter[k] = i;
		        token = strtok(NULL, s);
				k = k + 1;
			}
        	
        }


        // la derniere ligne pour les M contraintes coté droit

        fgets(line, 1024, file);
		token = strtok(line, s);
		k = 0;

   		/* walk through other tokens */
        while( token != NULL ) {
	        i = atoi(token);
	        constrains.rhs[k] = i;
	        token = strtok(NULL, s);
	        k = k + 1;
        }

	}

}

