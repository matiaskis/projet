all: exec
main.o:main.c zip.h unzip.h choose.h time.h compar.h
	gcc -c main.c -o main.o
zip.o:zip.c zip.h ppm_lib.h prog_bar.h compar.h
	gcc -c zip.c -o zip.o
unzip.o:unzip.c unzip.h ppm_lib.h prog_bar.h compar.h
	gcc -c unzip.c -o unzip.o
ppm_lib.o:ppm_lib.c ppm_lib.h
	gcc -c ppm_lib.c -o ppm_lib.o
choose.o:choose.c choose.h
	gcc -c choose.c -o choose.o
prog_bar.o:prog_bar.c prog_bar.h
	gcc -c prog_bar.c -o prog_bar.o
time.o:time.c time.h
	gcc -c time.c -o time.o
compar.o:compar.c compar.h 
	gcc -c compar.c -o compar.o
exec:main.o zip.o unzip.o ppm_lib.o choose.o time.o prog_bar.o compar.o
	gcc main.o zip.o unzip.o ppm_lib.o choose.o time.o prog_bar.o compar.o -o exec
clean:
	rm -f *.o
	rm exec
