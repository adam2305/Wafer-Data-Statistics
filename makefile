# make du projet AlgoProg

all: main.o fichier1.o fichier2.o fichier3.o
	gcc main.o fichier1.o fichier2.o fichier3.o -o main 

main.o: main.c main.h
	gcc -c main.c

fichier1.o: fichier1.c fichier1.h
	gcc -c fichier1.c

fichier2.o: fichier2.c fichier2.h
	gcc -c fichier2.c

fichier3.o: fichier3.c fichier3.h
	gcc -c fichier3.c


