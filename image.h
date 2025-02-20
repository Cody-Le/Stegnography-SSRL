#ifndef __IMAGE_H
#define __IMAGE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//Used in decoding the message from its encoding form. 
//Store a pointer of a short array and it's size.
typedef struct EncodedMessage{
    short* data;
    int size;
} EncodedMessage;
 
//Write the message encoded ina short to the image.
int write_shorts_to_image(char* img_dir, short* data, int size);
//Return the encoded message from the file.
EncodedMessage message_from_file(char* img_dir);
//Return the length of the message in the file, 0 if there are no message.
int message_length_from_file(FILE* file);
//Check if there is a message and make a new version of the file without it.
int check_and_remove_message(char* img_dir);
//Copy image until a certain location, used in create a new 
//verion of the picture without the message.
char* copy_img_in_range(char* in_img_dir, char* out_img_dir, unsigned long copy_to);

#endif


