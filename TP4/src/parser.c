#include "headers/parser.h"
#include "headers/vars.h"

/*
* Parse MKP problem instance from file
* @param FILE file
*/
void parseFile(FILE *file) {

	int valO;
	// FILE* fichier = NULL;
	char line[1024];
	// fichier = fopen("../data/mknap1.txt", "r");
	const char* tok;

	if (fichier != NULL)
	{
		// juste la premiere ligne: nombres de variables, contrainte, et valeur objective 
		fscanf(file, "%d %d %d", N, M, valO); fgetc(file);


		// La seconde ligne : les coefficients
		fgets(line, 1024, file);
		token = strtok(line, s);
		k = 0

   		/* walk through other tokens */
        while( token != NULL ) {
	        int  i = atoi(token);
	        *(objectiveFunction.value + k) = i;

	        token = strtok(NULL, s);
	        k = k + 1;
        }

        // les M lignes suivantes pour les contraintes

        for (int j = 0; j < M; ++j)
        {
        	fgets(line, 1024, file);

        	token = strtok(line, s);
        	float *inter;
        	int n = 0;

        	while( token != NULL ) {
		        int  i = atoi(token);
		        inter = constrains.lhs[j]
		        inter[n] = i;

		        token = strtok(NULL, s);
		        n = n + 1;
        	}
        	
        }

        // la derniere ligne pour les M contraintes coté droit

        fgets(line, 1024, file);
		token = strtok(line, s);
		int b = 0

   		/* walk through other tokens */
        while( token != NULL ) {
	        int  i = atoi(token);
	        constrains.rhs[b] = i;

	        token = strtok(NULL, s);
	        b = b + 1;
        }

	}

}

