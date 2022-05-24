#include "unzip.h"
#include "ppm_lib.h"

void read_param(int *pwidht,int *pheight,int *prange,int *pnbColors,FILE *zip_file){

	unsigned char widht_byte,height_byte,range_byte,nbColors_byte;

	fread(&widht_byte,sizeof(unsigned char),1,zip_file);
	*pwidht=widht_byte*255;
	fread(&widht_byte,sizeof(unsigned char),1,zip_file);
	*pwidht=*pwidht+widht_byte;

	fread(&height_byte,sizeof(unsigned char),1,zip_file);
	*pheight=height_byte*255;
	fread(&height_byte,sizeof(unsigned char),1,zip_file);
	*pheight=*pheight+height_byte;

	fread(&range_byte,sizeof(unsigned char),1,zip_file);
	*prange=range_byte;

	fread(&nbColors_byte,sizeof(unsigned char),1,zip_file);
	*pnbColors=nbColors_byte;
}



void read_rgb_block(FILE *file_entree;
	int red,green,blue;

	fread(&red,sizeof(unsigned char),1,zip_file);
	fread(&green,sizeof(unsigned char),1,zip_file);
	fread(&blue,sizeof(unsigned char),1,zip_file);










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


	int widht,height,range,nbColors;
	int *pwidht,*pheight,*prange,*pnbColors;

	pwidht=&widht;
	pheight=&height;
	prange=&range;
	pnbColors=&nbColors;

	read_param(pwidht,pheight,prange,pnbColors,zip_file);

	PPM_IMG *image_sortie;
	image_sortie=ppmNew(widht,height,range,nbColors);


	previous_pixel_value=pixel(red,green,blue);

	index=(3*red+5*green+7*blue)%64;
	cache[index]=previous_pixel_value;


