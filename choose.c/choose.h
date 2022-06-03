#ifndef CHOOSE_H
    #define CHOOSE_H
    #include <stdio.h>
    #include<stdlib.h>
/*!
     * @brief this function allows the user to choose the operating mode of the program(zip/unzip/cancel).
     * @param none.
     * @return  integer value used in the main to choose the operating mode, either 1 or 2.
     */
int choose();
/*!
     *@brief this function allow to clear the buffer before each loop.
     *@param none.
     *@return nothing.
     */
void clear_buffer();

#endif
