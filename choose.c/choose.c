#include<choose.h>

int choose(){
 int choice;
 printf("to compress enter 1, to compress back enter 2");
 scanf("%d", &choice);
 while(choice!=1 && choice!=2){
  printf("can you choose your use");
  printf("to compress enter 1, to compress back enter 2");
 }
 if(choice==1){

  return (1);
}
else {
  return (2);    
}
}
