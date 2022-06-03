#include"time.h"
#include"choose.h"
#include"zip.h"
#include"unzip.h"

int main(int argc, char ** argv){
  clock_t time_start,time_end;
  time_start=get_time();
  int choice=choose();
  if(choice==1){
    zip(argv);
  }
  else{
unzip(argv);
  }
  time_end=get_time();
  execution_time(time_start,time_end);
  return 0;
}
