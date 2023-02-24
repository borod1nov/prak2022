main: main.o list.o word.o
	gcc main.o list.o word.o -o My_Shell

main.o:
	gcc -c main.c -o main.o

list.o: list.c list.h
	gcc -c list.c -o list.o

word.o: word.c word.h
	gcc -c word.c -o word.o

.INTERMEDIATE: list.o main.o word.o
