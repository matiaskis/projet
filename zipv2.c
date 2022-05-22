#include "ppm_lib.h"
#include "zip.h"

void zip(char **path){
    // getcolor à faire et fclose

char *path_enter, *path_exit;

path_enter=path[1];
if (path_enter==NULL){
printf("error path enter");
exit(1);
}

path_exit=path[2];
if (path_exit==NULL){
printf("error path exit");
exit(1);
}

PPM_IMG *img_entree;

img_entree=ppmOpen(path_enter);

int width=ppmGetWidth(img_entree), height=ppmGetHeight(img_entree);

FILE *zipped;
zipped=fopen(path_exit,"wb+");
if(zipped==NULL){
printf("error while creating file");
exit(1);
}


int i, j;
int* pi,*pj;
pi=&i;pj=&j;
unsigned char previous_pixel_value, pixel_value;
unsigned char red_byte=red(previous_pixel_value);,green_byte=green(previous_pixel_value);,blue_byte=blue(previous_pixel_value);
unsigned char cache[64]={0};
unsigned char block_rgb=254;

previous_pixel_value=ppmRead(img_entree,0,0);

fwrite(&block_rgb,sizeof(unsigned char),1,zipped);
fwrite(&red_byte,sizeof(unsigned char),1,zipped);
fwrite(&green_byte,sizeof(unsigned char),1,zipped);
fwrite(&blue_byte,sizeof(unsigned char),1,zipped);

unsigned char index;
index=(3*red(previous_pixel_value)+5*green(previous_pixel_value)+7*blue(previous_pixel_value))%64;
cache[index]=previous_pixel_value;//saving the first pixel value

void block_same(int* pi,int* pj,unsigned char pixel_value,unsigned char previous_pixel_value){
    unsigned char counter;
    *pj++;
	counter++;
		while(previous_pixel_value==pixel_value){
			
			pixel_value==ppmRead(img_entree,j,i);
			*pj++;
			counter++;//counts the number of successive same pixel
            if (*pj>=width){
		        break;
		    }
		}
		counter=significant_bit_same+counter-1; 	
		fwrite(&counter, sizeof(unsigned char),1,zipped);
		counter=0;
	}
	
	void block_index(int cache[],unsigned char pixel value){
    index=(3*red(pixel_value)+5*green(pixel_value)+7*blue(pixel_value))%64;
		if(cache[index]!=0){
		fwrite(&index,sizeof(unsigned char),1,zipped);
		}	
    }	

    void block_diff(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue){       
            diff_red=diff_red+2;
            diff_green=diff_green*4;
            diff_blue=diff_blue*16;
	        unsigned char diff_total=significant_bit_diff+diff_red+diff_blue+diff_green;
	        fwrite(&diff_total,sizeof(unsigned char),1,zipped);
    }

    void block_luma(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue){
        diff_green=significant_bit_luma+diff_green+32;
	    fwrite(&diff_g,sizeof(unsigned char),1,zipped);
	    unsigned char diff_total=(diff_red-diff_green+8)*16+diff_blue-diff_green+8;
	    fwrite(&diff_total,sizeof(unsigned char),1,zipped);
    }

    void block_rgb(unsigned char pixel_value){
        unsigned char red_byte=red(pixel_value);
	    unsigned char green_byte=green(pixel_value);
	    unsigned char blue_byte=blue(pixel_value);
	    fwrite(&block_rgb,sizeof(unsigned char),1,zipped);
	    fwrite(&red_byte,sizeof(unsigned char),1,zipped);
	    fwrite(&green_byte,sizeof(unsigned char),1,zipped);
	    fwrite(&blue_byte,sizeof(unsigned char),1,zipped);
    }

for (i=0;i<height;i++){
	for (j=0;j<width;j++){
	
		if (i==0 && j==0){
		j++;	
		}
		
		pixel_value=ppmRead(img_entree,j,i);
		
//block_same
		if(previous_pixel_value==pixel_value){
        block_same(int* pi,int* pj,pixel_value,previous_pixel_value);
        }

//block_index
		block_index(cache,pixel_value);
        

//block_diff 
		unsigned char diff_red=(red(pixel_value)-red(previous_pixel_value));
        unsigned char diff_green=(green(pixel_value)-green(previous_pixel_value));
        unsigned char diff_blue=(blue(pixel_value)-blue(previous_pixel_value));
		else if( diff_red>=(-2) && diff_red<=1 && diff_green>=(-2) && diff_green<=1 && diff_blue>=(-2) && diff_blue<=1 ){
            block_diff(diff_red,diff_green,diff_blue);    
        }		


//block_luma
        else if(diff_green>=(-32) && diff_green<=31 && diff_red-diff_green >= (-8) && dif_red-diff_green <=7 && diff_blue-diff_green >= (-8) && diff_blue-diff_green<=7){
	        block_luma(diff_red,diff_green,diff_blue);
        }

//block_rgb
        else{
            block_rgb(pixel_value);
        }
//index save
        index=(3*red(pixel_value)+5*green(pixel_value)+7*blue(pixel_value))%64;
	    if(cache[index]==0){
		cache[index]=pixel_value;
		}
}
}
printf("zip created");	
fclose(zipped);	
}