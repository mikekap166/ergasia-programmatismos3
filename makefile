
main: main.o funky.o
	gcc main.o funky.o -o main

main.o: main.c funky.h Product.h order.h
	gcc -c main.c

funky.o : funky.c funky.h Product.h order.h
	gcc -c funky.c
