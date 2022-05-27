#include"time.h"

clock_t get_time(){
  clock_t time;
    time=clock();
    return(time);
}

void execution_time(clock_t time_1,clock_t time_2){

	float execution_time;
	execution_time=time_2-time_1;
	printf("the operation lasted %fs",execution_time);
}
