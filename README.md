# projet
This program is used to zip/unzip either a ppm or pgm image. It work with the E.V.A. alglorithm, the img is zipped in a binary file which is used after to write again
the image.

To make it work you have to add in argument when you run it, the path of the file you want to zip/unzip and the path of the zipped/unzipped file.

you have to be in the directory where the program is and the random_directory where is saved your ppm image have to be in there to

first of all you type : make                                                         // to compile the program with the makefile

exemple zip :  ./exec random_directory/image.ppm random_directory/image.zip         //it create a binary zipped file named image.zip in the random_directory        
exemple unzip : ./exec random_directory/image.zip random_directory/image_out.ppm    //it create a ppm image named image_out.ppm in the random_directory 
 
 

after that you will be asked if you want to zip or unzip or cancel, as it is writted you just have to type 1,2 or 3 depend on the action you want to do.
same thing with the confirmation.(type y or n)

(if it say Error segmentation (core dumped) you wrote a wrong path)
