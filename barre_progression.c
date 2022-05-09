#include<stdio.h>

int test(int a){
    int i;int j;
    printf("\n-------\n");
    printf("|");
    for(i=0;i<a;i++){
            printf("#");
        }
    for(j=0;j<5-a;j++){
            printf(" ");
            }
    printf("|");
     
}

