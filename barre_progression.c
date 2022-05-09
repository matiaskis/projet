#include<barre_progression.h>

int test(int progression){
    int i;int j;
    printf("\n-------\n");
    printf("|");
    for(i=0;i<progression;i++){
            printf("#");
        }
    for(j=0;j<5-progression;j++){
            printf(" ");
            }
    printf("|");
    printf("\n-------\n") 
}

