#include "ppm_lib.h"


void compar(char **argv, PPM_IMG* image_sortie){
char *filename_enter=argv[1];
char *filename_exit=argv[2];

struc stat enter;
struc stat exit;
 if (stat(filename_enter, &enter) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
 if (stat(filename_exit, &exit) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }   
 unsigned int byte_enter=enter.st_size;
 unsigned int byte_exit=exit.st_size;
 float caculation;
 calculation
 if(byte_enter<=byte_exit){
 calculation=(byte_exit/byte_enter-1)*100;
 printf("you are unziped of %f %",calculation);
 }
 else{
 calculation=(byte_exit/byte_enter-1)*100;
 printf("you are ziped of %f %",calculation);
 }
 printf("Total file size: %lu bytes\n", exit.st_size);
 ppmDisplay  (image_sortie); 
 }
