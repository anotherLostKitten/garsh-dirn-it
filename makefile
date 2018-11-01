all: stats.o
	gcc stats.o -o stats -lm
stats.o: stats.c
	gcc stats.c -c
run: all
	./stats
