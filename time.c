#include<time.h>

float execution_time(clock_t time_1,clock_t time_2){

	float execution_time;
	execution_time=time_2-time_1;
	return (execution_time);
}

clock_t get_time(){
  clock_t time;
    time=clock();
    return(time);
}