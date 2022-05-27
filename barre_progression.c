#include <stdio.h>
#include<unistd.h>
int prog_bar(){
    int i,j;
 for(i=0;i<11;i++){
    printf("\n--------------\n");
    printf("|");
    
    for(j=0;j<i;j++){
            printf("█");
        }

    for(j=0;j<10-i;j++){
            printf(" ");
            }
            if(i<7){
              printf(" ");
            }
    printf("|%d",i*10);
    printf("%c",'%');
    printf("\n--------------\n");
    sleep(1);
}
}
