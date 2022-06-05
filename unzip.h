#ifndef UNZIP_H
    #define UNZIP_H
    #include<stdio.h>
    #include"ppm_lib.h"
    #include"prog_bar.h"	
    #include"compar.h"

    #define significant_bit_same 192
    #define significant_bit_diff 64
    #define significant_bit_luma 128
    #define significant_bit_rgb 254
    #define counter_increment 1
    #define offset_diff_value 2
    #define offset_luma_value 8
    #define offset_diff_green 32
   
    /*!
     * @brief                       this function unzip a binary zipped file into a ppm image
     * @param path                  relative path to the image file to open
     * @return                      nothing
     */
    void unzip(char **path);

    /*!
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param pwidth                pointer used to get the width of the ppm image
     * @param pheight               pointer used to get the height of the ppm image
     * @param prange                pointer used to get the range of color of the ppm image
     * @param pnbColors             pointer used to get the number of colors of the ppm image
     * @param zip_file              pointer of the zipped file 
     * @return                      nothing
     */
    void read_param(int *pwidth,int *pheight,int *prange,int *pnbColors,FILE *zip_file);

    /*!
     * @brief                       this function read the three colors value after the "rgb block"                                            
     * @param zip_file              pointer relative to zipped file
     * @param j                     integer value : position x of the pixel
     * @param i                     integer value : position y of the pixel
     * @param unzipped              pointer used to get the number of colors of the ppm image
     * @return                      value of the pixel
     */
    int read_rgb_block(FILE *zip_file,int j, int i,PPM_IMG* unzipped);

    /*!
     * @brief                       this function find a "eva block same" : read how many time it have to write the previous pixel value                                             
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param unzipped              pointer relative to the unzipped file
     * @param i                     integer value : y position of the pixel
     * @param pj                    pointer used to change the position of the pixel in the PPM_IMG structure pointer
     * @param previous_pixel_value  integer value of the previous pixel 
     * @param width                 integer value : width of the ppm img
     * @return                      value of the pixel
     */
    int read_same_block(unsigned char byte,PPM_IMG* unzipped,int i,int *pj,int previous_pixel_value,int width);

    /*!
     * @brief                       this function find a index block and write the pixel value stored in the cache                                            
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param cache                 array where all pixel values are stored
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer used to get the number of colors of the ppm image 
     * @return                      value of the pixel
     */
    int read_index_block(unsigned char byte,int cache[],int i,int j,PPM_IMG* unzipped);

    /*!
     * @brief                       this function find a "eva block diff" and read the difference in the red green and blue component between the previous and current pixel                                             
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @return                      value of the pixel
     */
    int read_diff_block(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* unzipped);
    
    /*!
     * @brief                       this function find a "eva block luma" and read the difference in the red greenand blue component between the previous and current pixel 
     * @param zip_file              pointer relative to zipped file
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @return                      value of the pixel
     */
    int read_luma_block(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* unzipped,int previous_pixel_value);

    /*!
     * @brief                       this function is used to unzip a pgm img find a single "eva block luma" and read the difference in one color component between the previous and current pixel                                            
     * @param zip_file              pointer relative to zipped file
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @return                      value of the pixel
     */
    int read_luma_block_pgm(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* unzipped,int previous_pixel_value);

    /*!
     * @brief                       this function is used to unzip a pgm img, it find a "eva block diff" and read the difference in the red green and blue component between the previous and current pixel                                             
     * @param byte                  unsigned char : value of binary byte in the zipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @return                      value of the pixel
     */
    int read_diff_block_pgm(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* unzipped);
	
    /*!
     * @brief                       this function is used to unzip a pgm img, read one colors value after the "rgb block"                                            
     * @param zip_file              pointer relative to zipped file
     * @param j                     integer value : position x of the pixel
     * @param i                     integer value : position y of the pixel
     * @param unzipped              pointer used to get the number of colors of the ppm image
     * @return                      value of the pixel
     */
     int read_rgb_block_pgm(FILE *zip_file,int j, int i,PPM_IMG* unzipped);
	
	
#endif
