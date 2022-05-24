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



int read_rgb_block(FILE *file_entree){
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
    return(pix);
}
    
int read_same_block(FILE *file_entree,int byte){
    int counter;
    counter=byte-192+1;
    return (counter);
}

int read_index_block(FILE *file_entree,int byte){
    int index=byte;
    return (index);
}

int read_diff_block(FILE *file_entree,int byte,int previous_pixel_value){
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
    return (pix);
}
    
int read_luma_block(FILE *file_entree,int byte){







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
	unsigned char pixel_value,previous_pixel_value index;


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
	if(rgb_byte==0){
	      printf("error in file zip");
          exit(1);
	}
	
	if(rgb_byte==255){
	previous_pixel_value=read_rgb_block(zip_file);
	}
	else {
	    printf("error in file zip");
	    exit(1);
	}

	index=(3*red+5*green+7*blue)%64;
	cache[index]=previous_pixel_value;
	ppmWrite(image_sortie,0,0,previous_pixel_value);
	
	int byte;
	for(int i=0;i<height;i++){
	    for(int j=0;j<widht;j++){
	        
	        if(j==0 && i==0){
	            j++;
	        }
	        
	        fread(&byte,sizeof(unsigned char),1,zip_file);
	        	if(byte==0){
	                printf("error in file zip");
                    exit(1);
            	}
	        
	        if (byte==0xFE){
	            pixel_value=read_rgb_block(zip_file);
	            ppmWrite(image_sortie,j,i,pixel_value);
	        }
	        
	        else if(byte>192){
	            int counter=read_same_block(zip_file,byte);
	            
	            for(int k=0;k<counter;k++){
	                ppmWrite(image_sortie,j,i,previous_pixel_value);
	                j++;
	            }
	            pixel_value=previous_pixel_value;
	        }
	        
	        else if(byte<64){
	            index=read_index_block(zip_file,byte);
	            pixel_value=cache[index];
	            ppmWrite(image_sortie,j,i,pixel_value);
	        }
	        
	        else if(byte<128 && byte>64){
	            pixel_value=read_diff_block(zip_file,byte,previous_pixel_value);
	            ppmWrite(image_sortie,j,i,pixel_value);
	        }
	        
	        else{
	            pixel_value=read_luma_block(zip_file,byte);
	        }
	            
	            
	        }
	    }
	}
