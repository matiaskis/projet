#include"choose.h"

void clear_buffer(){  //clear the buffer
  while(getc(stdin)!='\n'){
}
}

int choose(){
    int choice=0;
    char y_n ='a';
    char y='y' ,n='n' ;

 
    while(choice!=1 && choice!=2 && choice!=3){//check if the user entered the right number
      printf("to zip enter 1, to unzip enter 2, to cancel enter 3 \n");
      scanf("%d", &choice);
      clear_buffer();
      y_n ='a';//enter in the "while" loop when the user made a mistake in the first choice

    while (y_n != 'y' && y_n != 'n' &&  (choice ==1 ||  choice==2  ||choice==3)){ //check if the user enter the right letter
      if(choice==1){
          printf("are you sure that you want to zip\n");
          printf("enter y if yes,enter n if no\n");
          scanf("%c",&y_n);
          clear_buffer();
     }

   else if(choice==2){
        printf("are you sure that you want to unzip\n");
        printf("enter y if yes,enter n if no\n");
        scanf("%c",&y_n); 
        clear_buffer();
    }
     else {
         printf("are you sure that you want to cancel\n");
         printf("enter y if yes,enter n if no\n");
         scanf("%c",&y_n); 
         clear_buffer();
    
    }

  }

   if(y_n==n){//allow when the user made a mistake to ask again what he wants
        choice=8;
    } 
}
  if(choice==1){//the user wants zip
      return (1);
    }

  else if(choice==2){//the user wants unzip
      return (2);
  }
  else exit(1);//the user wants cancel
  }
