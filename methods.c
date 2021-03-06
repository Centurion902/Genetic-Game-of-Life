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
			if(rand() % 2 ==0){//initializes the array with ones and zeroes randomly
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
		printf("\033[A");//deletes line
		printf("\33[2k");//raises cursor one line
		
		printf("\r");//returns cursor to begining of line
	}

	//printing top of border
	for(i = 0;i<=gridSide;i++){
		printf("--");
	}
	printf("\n");

	//printing grid
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

	//printing bottom of border
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

	//generating new creatures by mutating the best
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

//shorthand for checking specific bordering cells
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
				//checking standard square
				neighbors += posTL(*grid, i, j);
				neighbors += posTC(*grid, i, j);
				neighbors += posTR(*grid, i, j);
				neighbors += posML(*grid, i, j);
				neighbors += posMR(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(i==0 && j==0){
				//checking top left square
				neighbors += posMR(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(i==0 && j==gridSide-1){
				//checking top right square
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
				//checking top edge square
				neighbors += posML(*grid, i, j);
				neighbors += posMR(*grid, i, j);
				neighbors += posBL(*grid, i, j);
				neighbors += posBC(*grid, i, j);
				neighbors += posBR(*grid, i, j);
			}else if(j==0){
				//checking left edge sqare
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
			
			//determining state of cell
			if(neighbors == 3||(neighbors == 2&&(*grid)[i][j] == '1')){
				newGrid[i][j] = '1';
			}else {
				newGrid[i][j] = '0';
			}

		}
	}
	//prints if in display mode
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
	int gridSide = 150;
	int numTicks = 100;
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

	//placing creature into grid
	for(i = (gridSide/2-5); i<(gridSide/2+3); i++){
		for(j = (gridSide/2-5); j<(gridSide/2+3); j++){
			grid[i][j] = creature[(i-(gridSide/2-5))*30+(j-(gridSide/2-5))];
		}
	}

	for(i = 0; i<numTicks; i++){ /*running life for gridSide generations*/
		numLiving = 0;
		tick(&grid, gridSide, print);
		for(k = 0; k<gridSide; k++){ /*calculating fitness*/
			for(j = 0; j<gridSide; j++){
				if(grid[k][j]=='1'){
					numLiving++;
				}

			}

		}//reward calculated based on how close the creature is to size 2000
		score += 100*100-(abs(numLiving-100)*abs(numLiving-100));
		if(numLiving == 0){
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

	//tests each creature
	for(i = 0; i<pop; i++){
		scores[i] = testCreature(size, population[i], 0);
		fprintf(f2, "%d, ", scores[i]);
	}

	fprintf(f2, "\n\n");
	for(i=0; i<numBest; i++){
		best[i]=i;
	}

	//selection sorts the top numBest creatures. no need for faster sort for such small groups.
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

