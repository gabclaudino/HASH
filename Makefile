all: hash.c main.c
	gcc -g -o myht main.c hash.c -lm

