build: main.o randomart.o
		gcc main.o randomart.o -o randomart

main.o: main.c randomart.c
		gcc -c main.c -o main.o

randomart.o: randomart.c
		gcc -c randomart.c -o randomart.o
