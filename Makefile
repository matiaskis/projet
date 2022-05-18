all: exec
main.o:main.c test.h
	gcc -c main.c -o main.o
test.o:test.c test.h ppm_lib.h
	gcc -c test.c -o test.o
ppm_lib.o:ppm_lib.c ppm_lib.h
	gcc -c ppm_lib.c -o ppm_lib.o
exec:main.o test.o ppm_lib.o
	gcc main.o test.o ppm_lib.o -o exec
clean:
	rm -f *.o
	rm exec
