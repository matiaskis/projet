#ifndef ZIP_H
    #define ZIP_H
	#include<stdio.h>
	#include"ppm_lib.h"
	#include"prog_bar.h"
	#include "compar.h"
    
    #define significant_bit_same 192
    #define significant_bit_diff 64
    #define significant_bit_luma 128
    #define significant_bit_rgb 254
    #define offset_diff_value 2
    #define offset_luma_value 8
    #define offset_diff_green 32
    #define counter_max_value 62
    
    /*!
     * @brief           this function zip a ppm image into a binary file
     * @param path      Relative path to the image file to open
     * @return          nothing
     */
    void zip(char **path);
    
    /*!
     * @brief                       this function count the number of similar pixel and write a "eva_block_same" in the zipped file
     * @param i                     integer used to read the ppm image       
     * @param pj                    pointer used to interact with the "for" loop which is used to read the ppm image
     * @param pixel_value           integer value of the current pixel 
     * @param previous_pixel_value  integer value of the previous pixel 
     * @param width                 integer value which is the width of the image
     * @param img_entree            pointer of entree image
     * @param zipped                pointer of the created zipped file
     * @return                      nothing
     */
    void block_same(int i,int* pj,int pixel_value,int previous_pixel_value,int width,PPM_IMG *img_entree,FILE *zipped);

    /*!
     * @brief                       this function check if the current pixel value is stored in the cache, if so it write a "eva_block_index"in the zipped file
     * @param index                 unsigned char which is the positon of the pixel value in the cache 
     * @param zipped                pointer of the created zipped file
     * @return                      nothing
     */
    void block_index(unsigned char index,FILE *zipped);

     /*!
     * @brief                       this function calculate the difference between the previous pixel value and the current pixel value 
     *                              and write a "eva_block_diff" in the zipped file
     * @param diff_red              difference between the previous pixel red component and the current pixel red component          
     * @param diff_green            difference between the previous pixel green component and the current pixel green component      
     * @param diff_blue             difference between the previous pixel blue component and the current pixel blue component
     * @param zipped                pointer of the created zipped file
     * @return                      nothing
     */
    void block_diff(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped);

    /*!
     * @brief                       if diff_red, diff_green or diff_blue is not between -2 and 1 this function calculate the difference    
     *                              between the previous pixel green component and the current pixel green component and write a "eva_block_luma" in the zipped file
     * @param diff_red              difference between the previous pixel red component and the current pixel red component          
     * @param diff_green            difference between the previous pixel green component and the current pixel green component      
     * @param diff_blue             difference between the previous pixel blue component and the current pixel blue component
     * @param zipped                pointer of the created zipped file
     * @return                      nothing
     */
    void block_luma(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped);

    /*!
     * @brief               if none of the previous function is valid this function write the whole pixel value by writing a 
     *                      "eva_block_rgb" in the zipped file
     * @param pixel_value   integer value of the current pixel
     * @param block_rgb_bit unsigned char which is the significant bits of the eva_block_rgb
     * @param zipped                pointer of the created zipped file
     * @return              nothing
     */
    void block_rgb(int pixel_value,FILE *zipped,unsigned char block_rgb_bit);

	/*!
     * @brief               	this function write all the parameter of the ppm image in the zipped file
     * @param width 		integer value which is the width of the ppm image
     * @param height 		integer value which is the height of the ppm image
     * @param range             integer value which is the range of color of the ppm image
     * @param nbColors		integer value which is the number of colors of the ppm image
     * @param zipped		pointer related to the zipped file
     * @return              	nothing
     */
	void param_zipped_writing(int width, int height,unsigned char range, unsigned char nbColors,FILE* zipped);

	 /*!
     * @brief               		this function display a progression bar 
     * @param percent   			float value : percentage of the pixel traited 
     * @return            			nothing
     */
	int prog_bar(float percent);
	
	void block_rgb_grey(int pixel_value,FILE *zipped,unsigned char block_rgb_bit);
	void block_luma_grey(unsigned char diff_grey,FILE *zipped);
	void block_diff_grey(unsigned char diff_grey,FILE *zipped);
#endif
