#ifndef COMPAR_H
    #define COMPAR_H
    
	#include <sys/stat.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <fcntl.h>
	#include <time.h>
	
    /*!
     * @brief 	this function display the parameter of the ppm img/zip or unzip ratio
     * @param 	path relative to enter/exit file
     * @return  nothing
     */
	void compar(char **argv);
#endif
