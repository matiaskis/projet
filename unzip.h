#ifndef UNZIP_H
    #define UNZIP_H
	#include<stdio.h>
	#include"ppm_lib.h"

void unzip(char **path);
void read_param(int *pwidth,int *pheight,int *prange,int *pnbColors,FILE *zip_file);
int read_rgb_block(FILE *zip_file,int j, int i,PPM_IMG* image_sortie);
int read_same_block(unsigned char byte,PPM_IMG* image_sortie,int i,int *pj,int previous_pixel_value,int width);
int read_index_block(unsigned char byte,int cache[],int i,int j,PPM_IMG* image_sortie);
int read_diff_block(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* image_sortie);
int read_luma_block(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* image_sortie,int previous_pixel_value);

#endif
