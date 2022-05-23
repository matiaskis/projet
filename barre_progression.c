#include<stdio.h>
#include<unistd.h>
int prog_bar(int progression){
    int i;int j;
    printf("\n------------\n");
    printf("|");
    for(i=0;i<progression;i++){
            printf("█");
        }
    for(j=0;j<10-progression;j++){
            printf(" ");
            }
    printf("|%d",i*10);
printf("%c",'%');
    printf("\n------------\n");
    sleep(1);
}
