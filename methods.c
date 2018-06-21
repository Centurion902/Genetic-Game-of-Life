#define _BSD_SOURCE

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "methods.h"

void createPopulation(int pop, int size, char** population){
	
	int i,j;
	srand(time(NULL));

	for(i = 0;i<pop;i++){
		for(j = 0;j<size;j++){
			if(rand() % 15==0){
				population[i][j]='1';
			}else{
				population[i][j]='0';
			}
			
		}
	}
	
}

void printGrid(int gridSide, char** grid){
	int i,j;
	for(i = 0; i<gridSide+2; i++){
		printf("\033[A");
		printf("\33[2k");
		
		printf("\r");
	}
	for(i = 0;i<=gridSide;i++){
		printf("--");
	}
	printf("\n");
	for(i = 0;i<gridSide;i++){
		printf("|");
		for(j = 0;j<gridSide;j++){
			if( grid[i][j] == '1'){

				printf("[]");
			}else{
				printf("  ");
			}
		}
		printf("|\n");
	}
	for(i = 0; i<=gridSide; i++){
		printf("--");
	}
	printf("\n");
	

	fflush(stdout);
	usleep(1000000/5);
	
}

void printPopulation(int pop, int size, char** population){
	int i,j;

	for(i = 0;i<pop;i++){
		for(j = 0;j<size;j++){
			printf("%c", population[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void savePopulation(int pop, int size, char** population){
	int i;
	FILE *f1 = fopen("creatures.txt", "a+");
	fseek(f1, 0, SEEK_END);
	for(i = 0;i<pop;i++){
		fprintf(f1, "%s\n", population[i]);
	}
	fclose(f1);
}

void newGeneration(int pop, int size, char*** population, int* best, int numBest, double mutationRate){ 
	int i, j, k,  mut;
	char** newPopulation;
	newPopulation = (char**)calloc(pop, size*sizeof(char));
	for ( i = 0; i < pop; i++ ){
    	newPopulation[i] = (char*) calloc(size, sizeof(char));
	}

	for(i = 0; i<numBest; i++){
		strcpy(newPopulation[i], (*population)[best[i]]);
	}

	for(i = 0; i<numBest; i++){
		for(j = 0; j<(pop-numBest)/numBest; j++){
			for(k = 0; k<size;k++){

				mut = (rand() % (int)(1/mutationRate));
				if(mut == 0){
					if((*population)[best[i]][k]=='1'){
						newPopulation[i*(pop-numBest)/numBest+j+numBest][k] = '0';
					}else{
						newPopulation[i*(pop-numBest)/numBest+j+numBest][k] = '1';
					}
				}else{
					newPopulation[i*(pop-numBest)/numBest+j+numBest][k] = (*population)[best[i]][k];
				}
			}
		}
	}

	for( i = 0; i < pop; i++ ){
    	free((*population)[i]);
	}
	free(*population);

	*population = newPopulation;
	
	
}

int posTL(char **grid, int i, int j){
	if(grid[i-1][j-1] == '1'){
		return 1;
	}
	return 0;
}

int posTC(char **grid, int i, int j){
	if(grid[i-1][j] == '1'){
		return 1;
	}
	return 0;
}

int posTR(char **grid, int i, int j){
	if(grid[i-1][j+1] == '1'){
		return 1;
	}
	return 0;
}

int posML(char **grid, int i, int j){
	if(grid[i][j-1] == '1'){
		return 1;
	}
	return 0;
}

int posMR(char **grid, int i, int j){
	if(grid[i][j+1] == '1'){
		return 1;
	}
	return 0;
}

int posBL(char **grid, int i, int j){
	if(grid[i+1][j-1] == '1'){
		return 1;
	}
	return 0;
}

int posBC(char **grid, int i, int j){
	if(grid[i+1][j] == '1'){
		return 1;
	}
	return 0;
}

int posBR(char **grid, int i, int j){
	if(grid[i+1][j+1] == '1'){
		return 1;
	}
	return 0;
}


void tick(char*** grid, int gridSide, int print){
	char** newGrid;
	int neighbors, i, j;

	newGrid = (char**)calloc(gridSide, gridSide*sizeof(char));
	for (i = 0; i < gridSide; i++){
    	newGrid[i] = (char*)calloc(gridSide, sizeof(char));
	}

	for(i = 0; i<gridSide; i++){ /*constructing grid*/
		for(j = 0; j<gridSide; j++){
			neighbors = 0;
			if(i!=0 && j != 0 && i!=gridSide-1 && j!= gridSide-1){
				neighbors += posTL(*grid, i, j);
				neighbors += posTC(*grid, i, j);
				neighbors += posTR(*grid, i, j);
				neighbors += posML(*grid, i, j);
				neighbors += posMR(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(i==0 && j==0){
				neighbors += posMR(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(i==0 && j==gridSide-1){
				neighbors += posML(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
			}else if(i==gridSide-1 && j==0){
				neighbors += posTC(*grid, i, j);
				neighbors += posTR(*grid, i, j);
				neighbors += posMR(*grid, i, j);
			}else if(i==gridSide-1  && j==gridSide-1){
				neighbors += posTL(*grid, i, j);
				neighbors += posTC(*grid, i, j);
				neighbors += posML(*grid, i, j);
			}else if(i==0){
				neighbors += posML(*grid, i, j);
				neighbors += posMR(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(j==0){
				neighbors += posTC(*grid, i, j);
				neighbors += posTR(*grid, i, j);
				neighbors += posMR(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(i==gridSide-1){
				neighbors += posTL(*grid, i, j);
				neighbors += posTC(*grid, i, j);
				neighbors += posTR(*grid, i, j);
				neighbors += posML(*grid, i, j);
				neighbors += posMR(*grid, i, j);
			}else if(j==gridSide-1){
				neighbors += posTL(*grid, i, j);
				neighbors += posTC(*grid, i, j);
				neighbors += posML(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
			}
			
			if(neighbors == 3||(neighbors == 2&&(*grid)[i][j] == '1')){
				newGrid[i][j] = '1';
			/*}else if((*grid)[i][j] == '1' || (*grid)[i][j] == '2'){
				newGrid[i][j] = '2';*/
			}else {
				newGrid[i][j] = '0';
			}

		}
	}
	if(print == 1){
		printGrid(gridSide, newGrid);
	}
	for ( i = 0; i < gridSide; i++ ){
    	free((*grid)[i]);
	}
	free(*grid);

	*grid = newGrid;

	
}

int testCreature(int size, char* creature, int print){
	char** grid;
	int gridSide = 50;
	int numTicks = 75;
	int numLiving = 0;
	int i = 0, j = 0, k = 0, score = 0;

	grid = (char**)calloc(gridSide, gridSide*sizeof(char));
	for (i = 0; i < gridSide; i++){
    	grid[i] = (char*)calloc(gridSide, sizeof(char));
	}
	
	for(i = 0; i<gridSide; i++){ /*constructing grid*/
		for(j = 0; j<gridSide; j++){
			grid[i][j] = '0';
		}
	}

	for(i = (gridSide/2-5); i<(gridSide/2+3); i++){
		for(j = (gridSide/2-5); j<(gridSide/2+3); j++){
			grid[i][j] = creature[(i-(gridSide/2-5))*8+(j-(gridSide/2-5))];
		}
	}

	for(i = 0; i<numTicks; i++){ /*running life for gridSide generations*/
		numLiving = 0;
		tick(&grid, gridSide, print);
		for(k = 0; k<gridSide; k++){ /*tallying score*/
			for(j = 0; j<gridSide; j++){
				if(grid[k][j]=='1'){
					numLiving++;
				}

			}

		}
		score+=130-abs(numLiving-30);
		if(numLiving == 0 || numLiving > 130){
			score = 0;
		}
		
	}

	


	for ( i = 0; i < gridSide; i++ ){
    	free(grid[i]);
	}
	free(grid);

	return score;
}

void testGeneration(int pop, int size, char** population, int* best, int numBest){
	
	int* scores, i, j, maxScore;
	FILE *f2 = fopen("scores.txt", "a+");

	scores = (int*)calloc(pop, sizeof(int));
	fseek(f2, 0, SEEK_END);
	for(i = 0; i<pop; i++){
		scores[i] = testCreature(size, population[i], 0);
		fprintf(f2, "%d, ", scores[i]);
	}

	fprintf(f2, "\n\n");
	for(i=0; i<numBest; i++){
		best[i]=i;
	}
	for(i=0; i<numBest; i++){
		maxScore = 0;
		for(j = 0; j<pop; j++){
			if(maxScore<scores[j]){
				maxScore=scores[j];
				best[i] = j;
			}
		}
		scores[best[i]]=0;
	}

	fclose(f2);
}

