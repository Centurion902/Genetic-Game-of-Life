All: initialization train display



initialization: methods.c initialization.c methods.h
	gcc -Wall -std=c99 -pedantic initialization.c methods.c -Iinclude -o initialization

train: methods.c train.c methods.h
	gcc -Wall -std=c99 -pedantic train.c methods.c -Iinclude -o train

display: methods.c display.c methods.h
	gcc -Wall -std=c99 -pedantic display.c methods.c -Iinclude -o display



