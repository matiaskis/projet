#include<choose.h>

int choose(){
 int choice;
 printf("to compress enter 1, to compress back enter 2");
 scanf("%d", &choice);
 while(choice!=1 && choice!=2){
  printf("please use a valid argument");
  printf("to compress enter 1, to compress back enter 2");
 }
 if(choice==1){

  return (1);
}
else {
  return (2);    
}
}
