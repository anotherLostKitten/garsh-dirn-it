all: tree.o
	gcc tree.o -o tree -lm
tree.o: tree.c
	gcc tree.c -c
run: all
	./tree
