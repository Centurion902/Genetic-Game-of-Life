#include <stdio.h> /*importing nescesary libreries*/
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef METHODS_H
#define METHODS_H

/*Function: Generates a brand new population of creatures randomly
 *Pram: two nonnegative integers. array of creatures
 */
void createPopulation(int pop, int size, char** population);

/*Function: Saves the current population of creatures to a textfile for viewing and reading
 *Pram: two nonnegative integers. array of creatures
 */
void savePopulation(int pop, int size, char** population);

/*Function: Prints the population to the console
 *Pram: two nonnegative integers. array of creatures
 */
void printPopulation(int pop, int size, char** population);

/*Function: Generates a new population of creatures by copying the top numBest
 *creatueres and adding versions of them with randmo mutations
 *Pram: three nonnegative integers. array of creatures. one double. one int array filled with nonnegative integers
 */
void newGeneration(int pop, int size, char*** population, int* best, int numBest, double mutationRate);

/*Function: checks the respectivepositions relative to the given coordinates in the given grid
 *Pram: two nonnegative integers. two dimensional char array representing grid
 */
int posTL(char **grid, int i, int j);

int posTC(char **grid, int i, int j);

int posTR(char **grid, int i, int j);

int posML(char **grid, int i, int j);

int posMR(char **grid, int i, int j);

int posBL(char **grid, int i, int j);

int posBC(char **grid, int i, int j);

int posBR(char **grid, int i, int j);

/*Function: generates the next grid state
 *Pram: two nonnegative integers. pointer to two dimensional char array representing grid 
 */
void tick(char*** grid, int gridSide, int print);

/*Function: tests the current creature and returns its score
 *Pram: char array, int representing size of char array, int is 1 or 0
 */
int testCreature(int size, char* creature, int print);

/*Function: tests the current generation and fills and array with their scores
 *Pram: char array, three nonnegative integers
 */
void testGeneration(int pop, int size, char** population, int* best, int numBest);

#endif