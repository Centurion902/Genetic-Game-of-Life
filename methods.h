#include <stdio.h> /*importing nescesary libreries*/
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef METHODS_H
#define METHODS_H

void createPopulation(int pop, int size, char** population);

void savePopulation(int pop, int size, char** population);

void printPopulation(int pop, int size, char** population);

void newGeneration(int pop, int size, char*** population, int* best, int numBest, double mutationRate);

int posTL(char **grid, int i, int j);

int posTC(char **grid, int i, int j);

int posTR(char **grid, int i, int j);

int posML(char **grid, int i, int j);

int posMR(char **grid, int i, int j);

int posBL(char **grid, int i, int j);

int posBC(char **grid, int i, int j);

int posBR(char **grid, int i, int j);

void tick(char*** grid, int gridSide, int print);

int testCreature(int size, char* creature, int print);

void testGeneration(int pop, int size, char** population, int* best, int numBest);

#endif