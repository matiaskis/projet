#include "unzip.h"
#include "ppm_lib.h"
#include "compar.h"


void read_param(int *pwidth,int *pheight,int *prange,int *pnbColors,FILE *zip_file){

	unsigned char width_byte,height_byte,range_byte,nbColors_byte;
	//width
	fread(&width_byte,sizeof(unsigned char),1,zip_file);
	if(width_byte>=255 || width_byte<0){
	   	printf("error width");
        exit(1);
	}
	*pwidth=width_byte*255;//get the width in the main
	
	fread(&width_byte,sizeof(unsigned char),1,zip_file);
	if(width_byte>=255 || width_byte<0){
	    printf("error width");
        exit(1);
	}
	*pwidth=*pwidth+width_byte;
	//height
	fread(&height_byte,sizeof(unsigned char),1,zip_file);
	if(height_byte>=255 || height_byte<0){
	   	printf("error height");
        exit(1);
	}
	*pheight=height_byte*255;
	fread(&height_byte,sizeof(unsigned char),1,zip_file);
	if(height_byte>=255 || height_byte<0){
	    printf("error height");
        exit(1);
	}
	*pheight=*pheight+height_byte;
	//range
	fread(&range_byte,sizeof(unsigned char),1,zip_file);
	if(range_byte==0){
	    printf("error range");
        exit(1);
	}
	*prange=range_byte;
	//nbColors
	fread(&nbColors_byte,sizeof(unsigned char),1,zip_file);
	if(nbColors_byte==0){
	    printf("error nbcolors");
        exit(1);
	}
	*pnbColors=nbColors_byte;
}



int read_rgb_block(FILE *zip_file,int j, int i,PPM_IMG* zipped){
	unsigned char red,green,blue;
	int pix;
	//get every colors of the rgb block
	fread(&red,sizeof(unsigned char),1,zip_file);
	if(red>255 || red<0){
	      printf("error red_byte");
          exit(1);
	}
	fread(&green,sizeof(unsigned char),1,zip_file);
	if(green>255 || green<0){
	      printf("error green byte");
          exit(1);
	}
	fread(&blue,sizeof(unsigned char),1,zip_file);
	if(blue>255 || blue<0){
	      printf("error blue byte");
          exit(1);
	}
    
    pix=pixel(red,green,blue);
	ppmWrite(zipped,j,i,pix);//write the pixel
	return(pix);//return the current pixel value
}
    
int read_same_block(unsigned char byte,PPM_IMG* zipped,int i,int *pj,int previous_pixel_value,int width){
	int counter;
	counter=byte-significant_bit_same+counter_increment;
	
	for(int k=0;k<counter;k++){
		ppmWrite(zipped,*pj,i,previous_pixel_value);
	    *pj=*pj+1;
	    }
        *pj=*pj-1;
	return(previous_pixel_value);//return the previous_pixel_value
}

int read_index_block(unsigned char byte,int cache[],int i,int j,PPM_IMG* zipped){
    unsigned char index=byte;
    int pix;
	pix=cache[index];//write the value of the pixel stored in the cache
	ppmWrite(zipped,j,i,pix);
	return(pix);
}

int read_diff_block(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* zipped){
    int r,g,b,pix;
    byte=byte-significant_bit_diff;
    unsigned char diff_red,diff_green,diff_blue;
    //get the diff in the diff block between the current and previous pixel 
    diff_red=(byte/16)-offset_diff_value;
    byte=byte-((diff_red+offset_diff_value)*16);
    diff_green=(byte/4)-offset_diff_value;
    diff_blue=byte-((diff_green+offset_diff_value)*4)-offset_diff_value;
   	//get the current pixel value by adding the difference
    r=red(previous_pixel_value)+diff_red;
    g=green(previous_pixel_value)+diff_green;
    b=blue(previous_pixel_value)+diff_blue;
    pix=pixel(r,g,b);
	ppmWrite(zipped,j,i,pix);
	return (pix);
}
    
int read_luma_block(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* zipped,int previous_pixel_value){
	unsigned char diff_green,diff_red,diff_blue;
	byte=byte-significant_bit_luma;
	diff_green=byte-offset_diff_green;
	int r,g,b;
	g=green(previous_pixel_value)+diff_green;
	fread(&byte,sizeof(unsigned char),1,zip_file);
	if(byte<0 || byte>255){
		printf("error luma");
        exit(1);
	}
	diff_red=(byte/16)+diff_green-offset_luma_value;
	diff_blue=byte-((byte/16)*16)+diff_green-offset_luma_value;
	r=red(previous_pixel_value)+diff_red;
	b=blue(previous_pixel_value)+diff_blue;
	int pix=pixel(r,g,b);
	ppmWrite(zipped,j,i,pix);
	return (pix);
}



//pgm function

int read_rgb_block_pgm(FILE *zip_file,int j, int i,PPM_IMG* zipped){
	unsigned char grey;
	int pix;
	//get the grey value after the rgb block
	fread(&grey,sizeof(unsigned char),1,zip_file);
	if(grey>255 || grey<0){
	      printf("error grey_byte");
          exit(1);
	}		
    pix=grey;
   
	ppmWrite(zipped,j,i,pix);//write the pixel
	return(pix);//return the current pixel value
}
    

int read_diff_block_pgm(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* zipped){
    unsigned char grey;
    int pix;
    byte=byte-significant_bit_diff;
    unsigned char diff_grey;
    
	diff_grey=byte-offset_diff_value;
   	//get the current pixel value by adding the difference
    grey=blue(previous_pixel_value)+diff_grey;
    pix=grey;
  
	ppmWrite(zipped,j,i,pix);
	
	return (pix);
}
    
int read_luma_block_pgm(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* zipped,int previous_pixel_value){
	unsigned char diff_grey;
	byte=byte-significant_bit_luma;
	diff_grey=byte-offset_diff_grey;//offset of diff green and grey is similar
    	unsigned char grey;
	grey=blue(previous_pixel_value)+diff_grey;
	
	int pix=grey;

	ppmWrite(zipped,j,i,pix);
	return (pix);
}



void unzip(char **path){
	char* path_enter, *path_exit;
	path_enter=path[1];//path relative to the zipped file
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
	zip_file=fopen(path_enter,"rb+");//opening the zipped file in reading mode

	int cache[64]={0};
	int pixel_value,previous_pixel_value;
	unsigned char index;
	int width,height,range,nbColors;
	float percent;
	unsigned char rgb_byte;
	int *pwidth,*pheight,*prange,*pnbColors;
	int grey;
	unsigned char byte;
	int j,i;
	int *pj;
	pj=&j;
	
	pwidth=&width;
	pheight=&height;
	prange=&range;
	pnbColors=&nbColors;

	read_param(pwidth,pheight,prange,pnbColors,zip_file);
	
	PPM_IMG *zipped;
	zipped=ppmNew(width,height,range,nbColors);//create a ppm_img structure
	
	if(nbColors==3){
		
		
		fread(&rgb_byte,sizeof(unsigned char),1,zip_file);//reading the first rgb block
		if(rgb_byte==0){
		      printf("error rgb_byte non existant");
    	      exit(1);
		}
	
		if(rgb_byte==0xFE){
		previous_pixel_value=read_rgb_block(zip_file,0,0,zipped);
		}
		else {
		    printf("error of the rgb_byte value");
		    exit(1);
		}

		index=(3*red(previous_pixel_value)+5*green(previous_pixel_value)+7*blue(previous_pixel_value))%64;
		cache[index]=previous_pixel_value;//save the first pixel value
	

	
		for(i=0;i<height;i++){
		    for(j=0;j<width;j++){
	        
		        if(j==0 && i==0){
		            j++;
		        }
		        
	 	       fread(&byte,sizeof(unsigned char),1,zip_file);//read the current byte
	 	       if(byte<0 || byte>255){
	  	          printf("error byte read");
     		       	exit(1);
       		     	}
	 	       //rgb block traitment
	 	       if (byte==0xFE){
	 	           pixel_value=read_rgb_block(zip_file,j,i,zipped);
	     	    }
	    	    //same block
	    	    else if(byte>=significant_bit_same){
	            pixel_value=read_same_block(byte,zipped,i,pj,previous_pixel_value,width);
	           
	     	   }
	     	   //index block
	     	   else if(byte<significant_bit_diff){
	            pixel_value=read_index_block(byte,cache,i,j,zipped);
	     	   }
	     	   //diff block
	     	   else if(byte<significant_bit_luma && byte>=significant_bit_diff){
	            pixel_value=read_diff_block(byte,previous_pixel_value,i,j,zipped);
	     	   }
	     	   //luma block
	     	   else{
	      	      pixel_value=read_luma_block(zip_file,byte,i,j,zipped,previous_pixel_value);
	       	 }
				index=(3*red(pixel_value)+5*green(pixel_value)+7*blue(pixel_value))%64;//calculate index of the pixel value	
				cache[index]=pixel_value;//saving pixel value in the cache 		
				previous_pixel_value=pixel_value;
			}
			//display a progress bar
			percent = (1.0*i*width + j)/(width*height) + 0.005;
			prog_bar(percent);	            
		}
		
	
	}
		
else{	
	fread(&rgb_byte,sizeof(unsigned char),1,zip_file);//reading the first rgb block
	if(rgb_byte==0){
	      printf("error rgb_byte non existant");
          exit(1);
	}
	
	if(rgb_byte==0xFE){
		previous_pixel_value=read_rgb_block_pgm(zip_file,0,0,zipped);
	}
	else {
	    printf("error of the rgb_byte value");
	    exit(1);
	}

	grey=blue(previous_pixel_value);
	index=(3*grey+5*grey+7*grey)%64;
	cache[index]=previous_pixel_value;//save the first pixel value
	
	
	
	for(i=0;i<height;i++){
	    for(j=0;j<width;j++){
	        
	        if(j==0 && i==0){
	            j++;
	        }
	        
	        fread(&byte,sizeof(unsigned char),1,zip_file);//read the current byte
	        if(byte<0 || byte>255){
	            printf("error byte read");
            	exit(1);
            	}
            	
	        //rgb block traitment
	        if (byte==0xFE){
	            pixel_value=read_rgb_block_pgm(zip_file,j,i,zipped);
	         }
	        //same block
	        else if(byte>=significant_bit_same){
	            pixel_value=read_same_block(byte,zipped,i,pj,previous_pixel_value,width);
	           
	        }
	        //index block
	        else if(byte<significant_bit_diff){
	            pixel_value=read_index_block(byte,cache,i,j,zipped);
	        }
	        //diff block
	        else if(byte<significant_bit_luma && byte>=significant_bit_diff){
	            pixel_value=read_diff_block_pgm(byte,previous_pixel_value,i,j,zipped);
	        }
	        //luma block
	        else{
	            pixel_value=read_luma_block_pgm(zip_file,byte,i,j,zipped,previous_pixel_value);
	        }
			grey=blue(pixel_value);
			index=(3*red(pixel_value)+5*green(pixel_value)+7*grey)%64;//calculate index of the pixel value	
			cache[index]=pixel_value;//saving pixel value in the cache 		
			previous_pixel_value=pixel_value;
		}
		//display a progress bar
		percent = (1.0*i*width + j)/(width*height) + 0.005;
		prog_bar(percent);	            
	}
	
	
}
		ppmSave(zipped,path_exit);
		fclose(zip_file);
		printf("file unzipped\n");
		compar(path);
		ppmDisplay(zipped);
		ppmClose(zipped);
}
