All: initialization train display



initialization: methods.o initialization.o
	gcc -std=c99 -Wall -ansi -pedantic initialization.o methods.o -o initialization

train: methods.o train.o
	gcc -std=c99 -Wall -ansi -pedantic train.o methods.o -o train

display: methods.o display.o
	gcc -std=c99 -Wall -ansi -pedantic display.o methods.o -o display



display.o: display.c
	gcc -std=c99 -Wall -ansi -pedantic -c display.c -o display.o

train.o: train.c
	gcc -std=c99 -Wall -ansi -pedantic -c train.c -o train.o	

initialization.o: initialization.c
	gcc -std=c99 -Wall -ansi -pedantic -c initialization.c -o initialization.o

methods.o: methods.c methods.h
	gcc -std=c99 -Wall -ansi -pedantic -c methods.c -o methods.o -lm
