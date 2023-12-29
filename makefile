# make du projet AlgoProg

main.o: main.c main.h
	gcc -c main.c

readData.o: readData.c readData.h
	gcc -c readData.c

interface.o: interface.c interface.h
	gcc -c interface.c

statistique.o: statistique.c statistique.h
	gcc -c statistique.c

main: main.o readData.o interface.o statistique.o
	gcc main.o readData.o interface.o statistique.o -o main -lm
