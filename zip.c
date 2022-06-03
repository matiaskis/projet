#include "ppm_lib.h"
#include "zip.h"
#include "prog_bar.h"
#include "compar.h"

//write the width,height,range,nbcolor
void param_zipped_writing(int width, int height,unsigned char range, unsigned char nbColors,FILE* zipped){
	unsigned char binary_width,binary_height;
	binary_width=width/255;
	fwrite(&binary_width,sizeof(unsigned char),1,zipped);
	binary_width=width%255;
	fwrite(&binary_width,sizeof(unsigned char),1,zipped);
	
	binary_height=height/255;
	fwrite(&binary_height,sizeof(unsigned char),1,zipped);
	binary_height=height%255;
	fwrite(&binary_height,sizeof(unsigned char),1,zipped);
	
	fwrite(&range,sizeof(unsigned char),1,zipped);
	
	fwrite(&nbColors,sizeof(unsigned char),1,zipped);
}
	
	

void block_same(int i,int* pj,int pixel_value,int previous_pixel_value,int width,PPM_IMG *img_entree,FILE *zipped){
    unsigned char counter=0;
    *pj=*pj+1;
	counter++;
		while(previous_pixel_value==pixel_value && *pj<width && counter < counter_max_value){
			pixel_value=ppmRead(img_entree,*pj,i);
			*pj=*pj+1;
			counter++;//counts the number of successive same pixel
           		}
			//when j is equal to width it check the last pixel		
			if(previous_pixel_value!=pixel_value){
				counter--;
				*pj=*pj-1;
			}
			counter=significant_bit_same+counter-1;
			fwrite(&counter,sizeof(unsigned char),1,zipped);
			counter=0;
			*pj=*pj-1;
	}

void block_index(unsigned char index,FILE *zipped){
			fwrite(&index,sizeof(unsigned char),1,zipped);		
    }	

void block_diff(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped){       
	diff_red=(diff_red+offset_diff_value)*16;//*16 to place the diff in the right position in the byte 
    	diff_green=(diff_green+offset_diff_value)*4; 
    	diff_blue=(diff_blue+offset_diff_value);
	unsigned char diff_total=significant_bit_diff+diff_red+diff_blue+diff_green;
	fwrite(&diff_total,sizeof(unsigned char),1,zipped);
    }

void block_luma(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped){
	unsigned char diff_g=diff_green;//save the diff green before
	diff_green=significant_bit_luma+diff_green+offset_diff_green;
	fwrite(&diff_green,sizeof(unsigned char),1,zipped);
	unsigned char diff_total=(diff_red-diff_g+offset_luma_value)*16+diff_blue-diff_g+offset_luma_value;
	fwrite(&diff_total,sizeof(unsigned char),1,zipped);
    }

void block_rgb(int pixel_value,FILE *zipped,unsigned char block_rgb_bit){
	unsigned char red_byte=red(pixel_value);
	unsigned char green_byte=green(pixel_value);
	unsigned char blue_byte=blue(pixel_value);
	    	
	fwrite(&block_rgb_bit,sizeof(unsigned char),1,zipped);
	fwrite(&red_byte,sizeof(unsigned char),1,zipped);
	fwrite(&green_byte,sizeof(unsigned char),1,zipped);
	fwrite(&blue_byte,sizeof(unsigned char),1,zipped);
    }

void zip(char **path){
    // getcolor à faire
	char *path_enter, *path_exit;

	path_enter=path[1];//get the path of the ppm img
	if (path_enter==NULL){
		printf("error path enter");
		exit(1);
	}

	path_exit=path[2];//get path of the zipped file
	if (path_exit==NULL){
		printf("error path exit");
		exit(1);
	}

	PPM_IMG *img_entree;
	img_entree=ppmOpen(path_enter);
	int width=ppmGetWidth(img_entree), height=ppmGetHeight(img_entree);
	unsigned char range=ppmGetRange(img_entree),nbColors=ppmGetColors(img_entree);//parameter of img


	FILE *zipped;
	zipped=fopen(path_exit,"wb+");//opening the zipped file in binary mode
	if(zipped==NULL){
		printf("error while creating file");
		exit(1);
	}
	
	param_zipped_writing(width,height,range,nbColors,zipped);
	
	int i,j;
	int* pj;
	pj=&j;
	int previous_pixel_value, pixel_value;
	int cache[64]={0};
	unsigned char block_rgb_bit=significant_bit_rgb;
	previous_pixel_value=ppmRead(img_entree,0,0);//get the value of the first pixel
	//get every color component of the first pixel
	unsigned char red_byte=red(previous_pixel_value);
	unsigned char green_byte=green(previous_pixel_value);
	unsigned char blue_byte=blue(previous_pixel_value);
	//writing the first pixel value
	fwrite(&block_rgb_bit,sizeof(unsigned char),1,zipped);
	fwrite(&red_byte,sizeof(unsigned char),1,zipped);
	fwrite(&green_byte,sizeof(unsigned char),1,zipped);
	fwrite(&blue_byte,sizeof(unsigned char),1,zipped);

	unsigned char index;
	index=(3*red(previous_pixel_value)+5*green(previous_pixel_value)+7*blue(previous_pixel_value))%64;
	cache[index]=previous_pixel_value;//saving the first pixel value in the cache

	unsigned char diff_red;
	unsigned char diff_green;
	unsigned char diff_blue;
	float percent;

	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
	
			if (i==0 && j==0){
				j++;	
			}
		
		pixel_value=ppmRead(img_entree,j,i);//get the current pixel value
		
		index=(3*red(pixel_value)+5*green(pixel_value)+7*blue(pixel_value))%64;
		//calculate diff
		diff_red=(red(pixel_value)-red(previous_pixel_value));
       		diff_green=(green(pixel_value)-green(previous_pixel_value));
        	diff_blue=(blue(pixel_value)-blue(previous_pixel_value));
        
		
		//block_same
		if(previous_pixel_value==pixel_value){
        		block_same(i,pj,pixel_value,previous_pixel_value,width,img_entree,zipped);
       		}
		//block_index
		else if(cache[index]==pixel_value){
			block_index(index,zipped);
		}
		//block_diff 
		else if( diff_red>=(-2) && diff_red<=1 && diff_green>=(-2) && diff_green<=1 && diff_blue>=(-2) && diff_blue<=1 ){
            		block_diff(diff_red,diff_green,diff_blue,zipped);    
        	}		
		//block_luma
        else if(diff_green>=(-32) && diff_green<=31 && diff_red-diff_green >= (-8) && diff_red-diff_green <=7 && diff_blue-diff_green >= (-8) && diff_blue-diff_green<=7){
	        block_luma(diff_red,diff_green,diff_blue,zipped);
        	}
		//block_rgb
        else{
            block_rgb(pixel_value,zipped,block_rgb_bit);
        	}
		//index save
		cache[index]=pixel_value;
		previous_pixel_value=ppmRead(img_entree,j,i);
		}
	//display a progress bar
	percent = (1.0*i*width + j)/(width*height) + 0.005;
	prog_bar(percent);
	}
printf("zip created\n");
compar(path);
fclose(zipped);	
}
