#include <stdio.h>
#include "methods.h"

int main(int argc, char *argv[]){
	int pop = 25, size = 64;
	char creature[64];
	FILE *f1 = fopen("creatures.txt", "r+");
	if (argc != 2) {/*makes sure number of arguments is correct*/
    	printf("Error, usage: wrong number of arguments. Expected 2. Generations | Mutation Rate\n");
    	exit(-1);
  	}

  	fseek(f1, -(2*pop-atoi(argv[1]))*(size+1)*sizeof(char), SEEK_END);
  	fread(creature, sizeof(char), size, f1);
	testCreature(size, creature, 1);
	return 0;
	fclose(f1);
}