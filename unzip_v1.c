#include "unzip.h"
#include "ppm_lib.h"

void read_param(int *pwidht,int *pheight,int *prange,int *pnbColors,FILE *zip_file){

	unsigned char widht_byte,height_byte,range_byte,nbColors_byte;

	fread(&widht_byte,sizeof(unsigned char),1,zip_file);
		if(widht_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*pwidht=widht_byte*255;
	fread(&widht_byte,sizeof(unsigned char),1,zip_file);
		if(widht_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*pwidht=*pwidht+widht_byte;

	fread(&height_byte,sizeof(unsigned char),1,zip_file);
		if(height_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*pheight=height_byte*255;
	fread(&height_byte,sizeof(unsigned char),1,zip_file);
		if(height_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*pheight=*pheight+height_byte;

	fread(&range_byte,sizeof(unsigned char),1,zip_file);
		if(range_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*prange=range_byte;

	fread(&nbColors_byte,sizeof(unsigned char),1,zip_file);
	if(nbColors_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	*pnbColors=nbColors_byte;
}



int read_rgb_block(FILE *zip_file,int j, int i,PPM_IMG* image_sortie){
	int red,green,blue;
	int pix;

	fread(&red,sizeof(unsigned char),1,zip_file);
	if(red==0){
	      printf("error in file zip");
          exit(1);
	}
	fread(&green,sizeof(unsigned char),1,zip_file);
	if(green==0){
	      printf("error in file zip");
          exit(1);
	}
	fread(&blue,sizeof(unsigned char),1,zip_file);
	if(blue==0){
	      printf("error in file zip");
          exit(1);
	}
    
    	pix=pixel(red,green,blue);
	ppmWrite(image_sortie,j,i,pix);
    	return(pix);
}
    
int read_same_block(int byte,PPM_IMG* image_sortie,int i,int *pj,int previous_pixel_value){
	int counter;
	counter=byte-192+1;
	 for(int k=0;k<counter;k++){
	                ppmWrite(image_sortie,*pj,i,previous_pixel_value);
	                *pj=*pj+1;
	            }
    return(previous_pixel_value);
}

int read_index_block(int byte,int cache[],int i,int j,PPM_IMG* image_sortie){
    int index=byte;
    int pix;
	pix=cache[index];
	 ppmWrite(image_sortie,j,i,pix);
	return(pix);
}

int read_diff_block(int byte,int previous_pixel_value,int i,int j,PPM_IMG* image_sortie){
    int r,g,b,pix;
    byte=byte-64;
    int diff_red,diff_green,diff_blue;
    diff_red=(byte/16)-2;
    byte=byte-diff_red;
    diff_green=(byte/4)-2;
    diff_blue=byte-diff_green-2;
    r=red(previous_pixel_value)+diff_red;
    g=green(previous_pixel_value)+diff_green;
    b=blue(previous_pixel_value)+diff_blue;
    pix=pixel(r,g,b);
	ppmWrite(image_sortie,j,i,pix);
    return (pix);
}
    
int read_luma_block(FILE *zip_file,int byte,int i,int j,PPM_IMG* image_sortie,int previous_pixel_value){
int diff_green,diff_red,diff_blue;
byte=byte-128;
diff_green=byte-32;
int r,g,b;
g=green(previous_pixel_value)+diff_green;
fread(&byte,sizeof(unsigned char),1,zip_file);
if(byte==0){
	      printf("error in file zip");
          exit(1);
	}
diff_red=(byte/16)+diff_green-8;
diff_blue=byte-((byte/16)*16)+diff_green-8;
r=red(previous_pixel_value)+diff_red;
b=blue(previous_pixel_value)+diff_blue;
int pix;
pix=pixel(r,g,b);
ppmWrite(image_sortie,j,i,pix);
return (pix);
}








void unzip(char **path){
	char* path_enter, *path_exit;
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

	FILE* zip_file;
	zip_file=fopen(path_enter,"rb+");

/* FILE *unzipped;
unzipped=fopen(path_exit,"w+");
if(unzipped==0){
printf("error while creating file");
exit(1);
}
*/

	int cache[64]={0};
	unsigned char pixel_value,previous_pixel_value,index;


	int widht,height,range,nbColors,rgb_byte;
	int *pwidht,*pheight,*prange,*pnbColors;

	pwidht=&widht;
	pheight=&height;
	prange=&range;
	pnbColors=&nbColors;

	read_param(pwidht,pheight,prange,pnbColors,zip_file);

	PPM_IMG *image_sortie;
	image_sortie=ppmNew(widht,height,range,nbColors);
	
	
	
	fread(&rgb_byte,sizeof(unsigned char),1,zip_file);
	printf("%d",rgb_byte);
	if(rgb_byte==0){
	      printf("error in file zip1");
          exit(1);
	}
	
	if(rgb_byte==0xFE){
	previous_pixel_value=read_rgb_block(zip_file,0,0,image_sortie);
	}
	else {
	    printf("error in file zip2");
	    exit(1);
	}

	index=(3*red(previous_pixel_value)+5*green(previous_pixel_value)+7*blue(previous_pixel_value))%64;
	cache[index]=previous_pixel_value;
	
	int byte,j;
	int *pj;
	pj=&j;
	for(int i=0;i<height;i++){
	    for(j=0;j<widht;j++){
	        
	        if(j==0 && i==0){
	            j++;
	        }
	        
	        fread(&byte,sizeof(unsigned char),1,zip_file);
	        	if(byte==0){
	                printf("error in file zip");
                    exit(1);
            	}
	        
	        if (byte==0xFE){
	            pixel_value=read_rgb_block(zip_file,j,i,image_sortie);
	            
	        }
	        
	        else if(byte>192){
	            pixel_value=read_same_block(byte,image_sortie,i,pj,previous_pixel_value);
	           
	        }
	        
	        else if(byte<64){
	            pixel_value=read_index_block(byte,cache,i,j,image_sortie);
	        }
	        
	        else if(byte<128 && byte>64){
	            pixel_value=read_diff_block(byte,previous_pixel_value,i,j,image_sortie);
	        }
	        
	        else{
	            pixel_value=read_luma_block(zip_file,byte,i,j,image_sortie,previous_pixel_value);
	        }
		index=(3*red(pixel_value)+5*green(pixel_value)+7*blue(pixel_value))%64;
		if(cache[index]==0){
		cache[index]=pixel_value;
		}
		previous_pixel_value=pixel_value;
	            
	            
	        }
	    }
ppmSave(image_sortie,path_exit);
ppmClose(image_sortie);
fclose(zip_file);
printf("file unzipped");
}
