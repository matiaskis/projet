#ifndef TIME_H
    #define TIME_H


    #include <stdio.h>
    #include "time.h"
    #include <time.h>

/*!
     * @brief this function calculate the execution time of the program and display it.
     *
     * @param time_1 first measured time value.
     * @param time_2 second measured time value.
     * @return  nothing.
     */
void execution_time(clock_t time_1,clock_t time_2);

/*!
     * @brief this function is used to get the curent time value.
     *
     * @param none
     * @return  the current time.
     */
clock_t get_time();

#endif
