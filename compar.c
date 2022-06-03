#include "ppm_lib.h"
#include <sys/stat.h>


void compar(char **argv, PPM_IMG* image_sortie){
char *filename_enter=argv[1];
char *filename_exit=argv[2];

struct stat enter;
struct stat exitt;
 if (stat(filename_enter, &enter) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
 if (stat(filename_exit, &exitt) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }   
 unsigned int byte_enter=enter.st_size;
 unsigned int byte_exit=exitt.st_size;
 float calculation;

 if(byte_enter<=byte_exit){
 calculation=(byte_exit/byte_enter-1)*100;
 printf("you are unziped of %f %c",calculation,'%');
 }
 else{
 calculation=(byte_exit/byte_enter-1)*100;
 printf("you are ziped of %f %c",calculation,'%');
 }
 printf("Total file size: %lu bytes\n", exitt.st_size);
 ppmDisplay  (image_sortie); 
 }
