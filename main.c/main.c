#include<time.h>
#include<choose.h>

int main(int argc, char ** argv){
  clock_t time_start, clock_t time_end;
  time_start=get_time();
  int choose=choose(argv);
 
  
  
  time_end=get_time();
  execution_time(time_start,time_end);
  return 0;
}
