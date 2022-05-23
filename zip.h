#ifndef ZIP_H
    #define ZIP_H
    
    #define significant_bit_same 192
    #define significant_bit_diff 64
    #define significant_bit_luma 128
    #define significant_bit_rgb 254
    
    /*!
     * @brief           this function zip a ppm image into a binary file
     * @param path      Relative path to the image file to open
     * @return          nothing
     */
    void zip(char **path);
    
    /*!
     * @brief                       this function count the number of similar pixel and write a "eva_block_same" in the zipped file
     * @param pi                    pointer used to interact with the "for" loop which is used to read the ppm image       
     * @param pj                    pointer used to interact with the "for" loop which is used to read the ppm image
     * @param pixel_value           integer value of the current pixel 
     * @param previous_pixel_value  integer value of the previous pixel 
     * @return                      nothing
     */
    void block_same(int* pi,int* pj,int pixel_value,int previous_pixel_value,int width,PPM_IMG *img_entree,FILE *zipped);

    /*!
     * @brief                       this function check if the current pixel value is stored in the cache, if so it write a "eva_block_index"in the zipped file
     * @param cache                 array used to store a new pixel value       
     * @param pixel_value           integer value of the current pixel                   
     * @return                      nothing
     */
    void block_index(unsigned char cache[],int pixel_value,FILE *zipped);

     /*!
     * @brief                       this function calculate the difference between the previous pixel value and the current pixel value 
     *                              and write a "eva_block_diff" in the zipped file
     * @param diff_red              difference between the previous pixel red component and the current pixel red component          
     * @param diff_green            difference between the previous pixel green component and the current pixel green component      
     * @param diff_blue             difference between the previous pixel blue component and the current pixel blue component
     * @return                      nothing
     */
    void block_diff(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped);

    /*!
     * @brief                       if diff_red, diff_green or diff_blue is not between -2 and 1 this function calculate the difference    
     *                              between the previous pixel green component and the current pixel green component and write a "eva_block_luma" in the zipped file
     * @param diff_red              difference between the previous pixel red component and the current pixel red component          
     * @param diff_green            difference between the previous pixel green component and the current pixel green component      
     * @param diff_blue             difference between the previous pixel blue component and the current pixel blue component
     * @return                      nothing
     */
    void block_luma(unsigned char diff_red,unsigned char diff_green,unsigned char diff_blue,FILE *zipped);

    /*!
     * @brief               if none of the previous function is valid this function write the whole pixel value by writing a 
     *                      "eva_block_rgb" in the zipped file
     * @param pixel_value   integer value of the current pixel
     * @return              nothing
     */
    void block_rgb(unsigned char pixel_value,FILE *zipped);
#endif
