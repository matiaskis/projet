
#include"prog_bar.h"

// percent float value between 0 and 1 both included
void prog_bar(float percent){
    int i;
    int L = 40;
    int N = (int)(percent*L);


    printf("\33[4A");
    printf("\33[1G");
    

    printf("\n ");
    for(i=0;i<L;i++){
        printf("-");
    }
    printf("\n|");
    
    for(i=0;i<L;i++){
        if(i<N){
            printf("#");             
        }
        else{
            printf(" ");
        }
    }

    printf("| %3d",(int)(percent*100));
    printf("%c",'%');
    printf("\n ");
    for(i=0;i<L;i++){
        printf("-");
    }
    printf("\n|");

    usleep(1);
}
