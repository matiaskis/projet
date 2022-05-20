
#include "ppm_lib.h"
#include "zip.h"

void zip(char **path){// getcolor à faire



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


int width, height;

width=ppmGetWidth(img_entree);



height=ppmGetHeight(img_entree);


FILE *zipped;
zipped=fopen(path_exit,"wb+");
if(zipped==0){
printf("error while creating file");
exit(1);
}


int i, j;
int last_pixel_value, pixel_value1;
unsigned char counter=0;
int cache[64]={0};
unsigned char  diff_b,diff_r,diff_g,diff_total;
unsigned char  block_rgb;
block_rgb=254;
last_pixel_value=ppmRead(img_entree,0,0);
fwrite(&block_rgb,sizeof(unsigned char ),1,zipped);

unsigned char red_byte,green_byte,blue_byte;
	red_byte=red(last_pixel_value);
	green_byte=green(last_pixel_value);
	blue_byte=blue(last_pixel_value);


fwrite(&red_byte,sizeof(unsigned char ),1,zipped);
fwrite(&green_byte,sizeof(unsigned char ),1,zipped);
fwrite(&blue_byte,sizeof(unsigned char ),1,zipped);



int index;
index=(3*red(last_pixel_value)+5*green(last_pixel_value)+7*blue(last_pixel_value))%64;
cache[index]=last_pixel_value;//enregistrement premier pixel dans le cache


for (i=0;i<height;i++){
	for (j=0;j<width;j++){
	
		if (i==0 && j==0){
		j++;	
		}
		

//int les diffs avant tester diff temps?
		pixel_value1=ppmRead(img_entree,j,i);
		




//block_same
		if(last_pixel_value==pixel_value1){
		j++;
		counter++;
		while(last_pixel_value==pixel_value1 && j<width){// attention j ne doit pas depasser height changement a faire
			
			pixel_value1==ppmRead(img_entree,j,i);
			j++;
			counter++;// compte le nombre de pixel identique a la suite
			}
		if(last_pixel_value==pixel_value1){
		
		}
		else counter --;

		counter=128+64+counter-1; //define bit_fort_block_same 128+64
		//verifier si la dernier valeur existe deja dans le cache avant de l engistrer dedans
		fwrite(&counter, sizeof(unsigned char ),1,zipped);
		counter=0;
		}
	
		//verfi de j
		if (j>=width){
		break;
		}

//block_index
		index=(3*red(pixel_value1)+5*green(pixel_value1)+7*blue(pixel_value1))%64;

		if(cache[index]!=0){
		fwrite(&index,sizeof(unsigned char),1,zipped);
		}

//block_diff
		
		else if( (red(pixel_value1)-red(last_pixel_value))>=(-2) && (red(pixel_value1)-red(last_pixel_value))<=1 && (green(pixel_value1)-green(last_pixel_value))>=(-2) && (green(pixel_value1)-green(last_pixel_value))<=1 && (blue(pixel_value1)-blue(last_pixel_value))>=(-2) && (blue(pixel_value1)-blue(last_pixel_value))<=1 ){

diff_r=red(pixel_value1)-red(last_pixel_value)+2;
diff_g=(green(pixel_value1)-green(last_pixel_value)+2)*4;
diff_b=(blue(pixel_value1)-blue(last_pixel_value)+2)*16;

	
	diff_total=64+diff_r+diff_b+diff_g; //define bit_fort_block_diff 64
	fwrite(&diff_total,sizeof(unsigned char),1,zipped);
}		


//block_luma
else if((green(pixel_value1)-green(last_pixel_value))>=(-32) && (green(pixel_value1)-green(last_pixel_value))<=31 && (red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) >= (-8) && (red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) <=7 && (blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) >= (-8) && (blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))<=7){
	diff_g=128+(green(pixel_value1)-green(last_pixel_value))+32;////define bit_fort_block_luma 128
	fwrite(&diff_g,sizeof(unsigned char),1,zipped);
	diff_total=((red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))+8)*16+(blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))+8;
	fwrite(&diff_total,sizeof(unsigned char),1,zipped);
}

//block_rgb
else{
	
	red_byte=red(pixel_value1);
	green_byte=green(pixel_value1);
	blue_byte=blue(pixel_value1);
	//define block rgb
	fwrite(&block_rgb,sizeof(unsigned char),1,zipped);
	fwrite(&red_byte,sizeof(unsigned char),1,zipped);
	fwrite(&green_byte,sizeof(unsigned char),1,zipped);
	fwrite(&blue_byte,sizeof(unsigned char),1,zipped);
}
	last_pixel_value=pixel_value1;
	if(cache[index]==0){
		cache[index]=pixel_value1;
		}
}
}
printf("zip created");		
}
	
































