Main: main.o funky.o child_exe.o
	gcc -o Main main.o funky.o child_exe.o

main.o: main.c funky.h child_exe.h Order.h Product.h
	gcc -c -o main.o main.c

child_exe.o: child_exe.c
	gcc -c -o child_exe.o child_exe.c
	
funky.o: funky.c Order.h Product.h
	gcc -c -o funky.o funky.c
	
clean :
	rm *.o Main
