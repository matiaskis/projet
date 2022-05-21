#include<stdio.h>

int test(int progression){
    int i;int j;
    printf("\n-------------\n");
    printf("|");
    for(i=0;i<progression;i++){
            printf("#");
        }
    for(j=0;j<10-progression;j++){
            printf(" ");
            }
    printf("|");
    printf("\n-------------\n");
    sleep(1);
}

int main (){
    for(int i=1;i<11;i++){
        test(i);
      }
}
