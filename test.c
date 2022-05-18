#include "ppm_lib.h"
#include "test.h"

void zip(char **argv){



char *path_enter, *path_exit;

path_enter=argv[1];


path_exit=argv[2];//verif à faire


PPM_IMG *img_entree;

img_entree=ppmOpen(path_enter);

int width, height;

width=ppmGetWidth(img_entree);

height=ppmGetHeight(img_entree);

FILE *zipped;
zipped=fopen("path_exit","rb+");
if(zipped==0){
printf("error while creating file");
exit(1);
}






int i, j;
int last_pixel_value, pixel_value1;
int counter=0;
int cache[64]={0};
int diff_b,diff_r,diff_g,diff_total;

last_pixel_value=ppmRead(img_entree,0,0);
fwrite(&last_pixel_value,sizeof(int),1,zipped);//enregistrement block rgb fisrt

int index;
index=(3*red(last_pixel_value)+5*green(last_pixel_value)+7*blue(last_pixel_value))%64;
cache[index]=last_pixel_value;//enregistrement premier pixel dans le cache


for (i=0;i<width;i++){
	for (j=0;j<height;j++){
	
		if (i==0 && j==0){
		j++;	
		}
		

//int les diffs avant tester diff temps?
		pixel_value1=ppmRead(img_entree,i,j);
		




//block_same
		if(last_pixel_value==pixel_value1){
		while(last_pixel_value==pixel_value1 && j<height){// attention j ne doit pas depasser height changement a faire
			j++;
			pixel_value1==ppmRead(img_entree,i,j);
			counter++;// compte le nombre de pixel identique a la suite
			}
		counter=128+64+counter-1; //define bit_fort_block_same 128+64
		//verifier si la dernier valeur existe deja dans le cache avant de l engistrer dedans
		fwrite(&counter, sizeof(int),1,zipped);
		counter=0;
		}
	
		//verfi de j
		if (j>=height){
		break;
		}

//block_index
		index=(3*red(pixel_value1)+5*green(pixel_value1)+7*blue(pixel_value1))%64;

		if(cache[index]!=0){
		fwrite(&index,sizeof(int),1,zipped);
		}

//block_diff
		
		else if( (red(pixel_value1)-red(last_pixel_value))>=(-2) && (red(pixel_value1)-red(last_pixel_value))<=1 && (green(pixel_value1)-green(last_pixel_value))>=(-2) && (green(pixel_value1)-green(last_pixel_value))<=1 && (blue(pixel_value1)-blue(last_pixel_value))>=(-2) && (blue(pixel_value1)-blue(last_pixel_value))<=1 ){

diff_r=red(pixel_value1)-red(last_pixel_value)+2;
diff_g=(green(pixel_value1)-green(last_pixel_value)+2)*4;
diff_b=(blue(pixel_value1)-blue(last_pixel_value)+2)*16;

	
	diff_total=64+diff_r+diff_b+diff_g; //define bit_fort_block_diff 64
	fwrite(&diff_total,sizeof(int),1,zipped);
}		


//block_luma
else if((green(pixel_value1)-green(last_pixel_value))>=(-32) && (green(pixel_value1)-green(last_pixel_value))<=31 && (red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) >= (-8) && (red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) <=7 && (blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value)) >= (-8) && (blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))<=7){
	diff_g=128+(green(pixel_value1)-green(last_pixel_value))+32;////define bit_fort_block_luma 128
	fwrite(&diff_g,sizeof(int),1,zipped);
	diff_total=((red(pixel_value1)-red(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))+8)*16+(blue(pixel_value1)-blue(last_pixel_value))-(green(pixel_value1)-green(last_pixel_value))+8;
	fwrite(&diff_total,sizeof(int),1,zipped);
}

//block_rgb
else{
	int red_byte,green_byte,blue_byte,block_rgb;
	red_byte=red(pixel_value1);
	green_byte=green(pixel_value1);
	blue_byte=blue(pixel_value1);
	block_rgb=254;//define block rgb
	fwrite(&block_rgb,sizeof(int),1,zipped);
	fwrite(&red_byte,sizeof(int),1,zipped);
	fwrite(&green_byte,sizeof(int),1,zipped);
	fwrite(&blue_byte,sizeof(int),1,zipped);
}
	last_pixel_value=pixel_value1;
	if(cache[index]==0){
		cache[index]=pixel_value1;
		}
}
}	
}
































