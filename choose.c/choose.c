#include"choose.h"

void vide_buffer(){
  while(getc(stdin)!='\n'){
}
}

int choose(){
    int choice=0;
    char y_n ='a';
    char y='y' ,n='n' ;

 
 while(choice!=1 && choice!=2 && choice!=3){
    printf("to zip enter 1, to unzip enter 2, to cancel enter 3 \n");
  
    scanf("%d", &choice);
   vide_buffer();
    y_n ='a';

 while (y_n != 'y' && y_n != 'n' &&  (choice ==1 ||  choice==2  ||choice==3)){
    if(choice==1){
    printf("are you sure that you want to zip\n");
     printf("enter y if yes,enter n if no\n");

    scanf("%c",&y_n);
       vide_buffer();
    
   

    }

   else if(choice==2){
    printf("are you sure that you want to unzip\n");
     printf("enter y if yes,enter n if no\n");

    scanf("%c",&y_n); 
    vide_buffer();
    }
     else {
    printf("are you sure that you want to cancel\n");
     printf("enter y if yes,enter n if no\n");
  
    scanf("%c",&y_n); 
         vide_buffer();
    
    }

    }

    if(y_n==n){
    choice=8;
    }
   }
 if(choice==1){
    return (1);
    }

else if(choice==2){
 return (2);
}
else exit(1);
}
