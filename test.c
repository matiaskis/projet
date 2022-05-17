char *path_enter, *path_exit;

path_enter=argv[1];


path_exit=argv[2];//verif à faire


PPM_IMG *img_entree;

img_entree=ppmOpen(path);

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

last_pixel_value=ppmRead(img_entree,0,0);// il faut l enregistrerdans l index 
fwrite(&last_pixel_value,sizeof(int),1,zipped);

int index;
index=(3*red(last_pixel_value)+5*green(last_pixel_value)+7*blue(last_pixel_value))%64;
cache[index]=last_pixel_value;

for (i=0;i<widht;i++){
	for (j=0;j<height;j++){
	
		if (i==0 && j==0){
		j++;	
		}
		


		pixel_value1=ppmRead(img_entree,i,j);
		




//block_same
		if((last_pixel_value==pixel_value1){
		while(last_pixel_value==pixel_value1){// attention j ne doit pas depasser height changement a faire
			j++;
			pixel_value1==ppmRead(img_entree,i,j);
			counter++;// compte le nombre de pixel identique a la suite
			}
		counter=128+64+counter-1; //define bit_fort_block_same 128+64
		//verifier si la dernier valeur existe deja dans le cache avant de l engistrer dedans
		fwrite(&counter, sizeof(int),1,zipped);
		counter=0;
		}

//block_index
		index=(3*red(pixel_value1)+5*green(pixel_value1)+7*blue(pixel_value1))%64;

		if(cache[index]!=0){
		fwrite(&index,sizeof(int),1,zipped);
		}

//block_diff
		
		else if( (red(pixel_value1)-red(last_pixel_value))>=(-2) && (red(pixel_value1)-red(last_pixel_value))<=1 && (green(pixel_value1)-green(last_pixel_value))>=(-2) && (green(pixel_value1)-green(last_pixel_value))<=1 && (blue(pixel_value1)-blue(last_pixel_value))>=(-2) && (blue(pixel_value1)-blue(last_pixel_value))<=1 ){

diff_r=red(pixel_value1)-red(last_pixel_value)+2;
diff_g=green(pixel_value1)-green(last_pixel_value)+2;
diff_b=blue(pixel_value1)-blue(last_pixel_value)+2;
switch(diff_red){

	case 1 :
	diff_red=16;
	break;

	case 2 :
	diff_red=32;
	break;
	
	case 3 :
	diff_red=48;
	break;

	default :
	break;
}
switch(diff_green){

	case 1 :
	diff_green=4;
	break;

	case 2 :
	diff_green=8;
	break;
	
	case 3 :
	diff_green=12;
	break;

	default :
	break;
}

	
diff_total=64+diff_red+diff_blue+diff_green; //define bit_fort_block_diff 64
fwrite(&diff_total,sizeof(int),1,zipped);
}		

else if(
































