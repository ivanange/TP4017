#include "headers/parser.h"
#include "headers/vars.h"

/*
* Parse MKP problem instance from file
* @param FILE file
*/
void parseFile(FILE *file) {

	int valO, k, j;
	// FILE* fichier = NULL;
	char line[1024];
	// fichier = fopen("../data/mknap1.txt", "r");
	const char s[2] = " ";
	const char* token;

	if (file != NULL)
	{
		// juste la premiere ligne: nombres de variables, contrainte, et valeur objective 
		fscanf(file, "%d %d %d", &N, &M, &valO); fgetc(file);
		// ceci c'est bon
		printf("\n%d", N);


		// La seconde ligne : les coefficients
		fgets(line, 1024, file);
		token = strtok(line, s);
		int *m;

   		/* walk through other tokens */
        while( token != NULL ) {
	        int  i = atoi(token);
	        // tous ceci marche mais je trouve ça bisard je comprend pas pour quoi sa marche
	        m = &objectiveFunction.value  ;
	        *(m+k) = i;
	         m = objectiveFunction.value;
	        printf("\n%d\n", *(&objectiveFunction+k));

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
		        // mon code block refuse ceci sa fait planter la machine pourtant sa devrait marcher
		        constrains.lhs[j][n] = i
		        

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

