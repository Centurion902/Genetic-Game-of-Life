#include <stdlib.h>
#include <stdio.h>
#include "methods.h"

/*
This program generates the first generation of creatures.
*/
int main(){
	int pop = 25, size = 900, i;
	char** population;
	FILE *f1 = fopen("creatures.txt", "w+");
	FILE *f2 = fopen("scores.txt", "w+");
	
	population = (char**)calloc(pop, size*sizeof(char));
	for (i = 0; i < pop; i++){
    	population[i] = (char*)calloc(size, sizeof(char));
	}

	createPopulation(pop, size, population);
	printPopulation(pop, size, population);
	
	for (i = 0; i < pop; i++){
    	fprintf(f1, "%s\n", population[i]);
	}

	//free all alocated data
	for ( i = 0; i < pop; i++ ){
    	free(population[i]);
	}
	free(population);

	fclose(f1);
	fclose(f2);
	return 0;
}