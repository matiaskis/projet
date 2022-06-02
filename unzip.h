#ifndef UNZIP_H
    #define UNZIP_H
    #include<stdio.h>
    #include"ppm_lib.h"
    
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
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param zip_file              pointer relative to zipped file
     * @param j                     integer value : position x of the pixel
     * @param i                     integer value : position y of the pixel
     * @param unzipped              pointer used to get the number of colors of the ppm image
     * @return                      value of the pixel
     */
    int read_rgb_block(FILE *zip_file,int j, int i,PPM_IMG* unzipped);

    /*!
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param byte                  unsigned char ; value of binary byte in the zipped file
     * @param unzipped              pointer relative to the unzipped file
     * @param i                     integer value : y position of the pixel
     * @param pj                    pointer used to change the position of the pixel in the PPM_IMG structure pointer
     * @param previous_pixel_value  integer value of the previous pixel 
     * @param width                 integer value : width of the ppm img
     * @return                      value of the pixel
     */
    int read_same_block(unsigned char byte,PPM_IMG* unzipped,int i,int *pj,int previous_pixel_value,int width);

    /*!
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param byte                  unsigned char ; value of binary byte in the zipped file
     * @param cache                 array where all pixel values are stored
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer used to get the number of colors of the ppm image 
     * @return                      value of the pixel
     */
    int read_index_block(unsigned char byte,int cache[],int i,int j,PPM_IMG* unzipped);

    /*!
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param byte                  unsigned char ; value of binary byte in the zipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @return                      value of the pixel
     */
    int read_diff_block(unsigned char byte,int previous_pixel_value,int i,int j,PPM_IMG* unzipped);
    
    /*!
     * @brief                       this function read the parameter of the ppm image in the zipped file                                             
     * @param zip_file              pointer relative to zipped file
     * @param byte                  unsigned char ; value of binary byte in the zipped file
     * @param i                     integer value : y position of the pixel
     * @param j                     integer value : position x of the pixel
     * @param unzipped              pointer relative to the unzipped file
     * @param previous_pixel_value  integer value of the previous pixel
     * @return                      value of the pixel
     */
    int read_luma_block(FILE *zip_file,unsigned char byte,int i,int j,PPM_IMG* unzipped,int previous_pixel_value);

   	 /*!
     * @brief               		this function display a progression bar 
     * @param percent   			float value : percentage of the pixel traited 
     * @return            			nothing
     */
	int prog_bar(float percent);
#endif
