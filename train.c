#include <stdlib.h>
#include <stdio.h>
#include "methods.h"

int main(int argc, char *argv[]){
	int pop = 25, size = 64, i, numBest = 5;
	double mutationRate;
	int numGenerations;
	char** population;
	char buffer = ' ';
	int* best = calloc(numBest, sizeof(int));
	FILE *f1 = fopen("creatures.txt", "r+");


	fseek(f1, -pop*(size+1)*sizeof(char), SEEK_END);
	if (argc != 3) {/*makes sure number of arguments is correct*/
    	printf("Error, usage: wrong number of arguments. Expected 2. Generations | Mutation Rate\n");
    	exit(-1);
  	}	


  	numGenerations = atoi(argv[1]);
  	mutationRate = (double)atoi(argv[2])/100;
	population = (char**)calloc(pop, size*sizeof(char));
	

	for (i = 0; i < pop; i++){
    	population[i] = (char*) calloc(size, sizeof(char));
	}
	
	for(i = 0; i < pop; i++){
		fread(population[i], sizeof(char), size, f1);
		fread(&buffer, sizeof(char), 1, f1);
	}
	printPopulation(pop, size, population);

	printf("\n\n");


	for(i = 0; i<numGenerations; i++){
		testGeneration(pop, size, population, best, numBest);
		newGeneration(pop, size, &population, best, numBest, mutationRate);
		savePopulation(pop, size, population);
		printPopulation(pop, size, population);
	}


	for ( i = 0; i < pop; i++ ){
    	free(population[i]);
	}
	free(population);

	fclose(f1);
	return 0;
}