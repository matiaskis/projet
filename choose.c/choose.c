#include<choose.h>
#define char *compression = compression
#define char *decompression = decompression

int choose(char **choice){
 while (*choice[3]!=*compression && *choice[3]!=*decompression) { 
    printf("Vous n'avez pas corectement écrit compression ou decompression \n");
    printf("veuillez resaisir l'action voulu");
    scanf("%s", choice[3]);
}
if (choice[3]=*compression){
  return (1);
}
else {
  return (2);    
}
}
