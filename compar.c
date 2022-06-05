#include <sys/stat.h>
#include "compar.h"


void compar(char **argv){
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
         calculation=((float)byte_enter/(float)byte_exit);
         calculation=(1-calculation)*100;
         printf("you have unziped of %f %c\n",calculation,'%');
       }
     else{
         calculation=((float)byte_exit/(float)byte_enter);
         calculation=(1-calculation)*100;
         printf("you have ziped of %f %c\n",calculation,'%');
          }
         printf("Total file size: %lu bytes\n", exitt.st_size);
 
}
 
