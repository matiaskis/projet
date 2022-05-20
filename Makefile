all: exec
main.o:main.c zip.h
	gcc -c main.c -o main.o
zip.o:zip.c zip.h ppm_lib.h
	gcc -c zip.c -o zip.o
ppm_lib.o:ppm_lib.c ppm_lib.h
	gcc -c ppm_lib.c -o ppm_lib.o
exec:main.o zip.o ppm_lib.o
	gcc main.o zip.o ppm_lib.o -o exec
clean:
	rm -f *.o
	rm exec
