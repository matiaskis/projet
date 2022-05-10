#include<choose.h>

int choose(){
 int choice;
 printf("to zip enter 1, to unzip enter 2");
 scanf("%d", &choice);
 while(choice!=1 && choice!=2){
  printf("please use a valid argument");
  printf("to zip enter 1, to unzip enter 2");
 }
 if(choice==1){

  return (1);
}
else {
  return (2);    
}
}
