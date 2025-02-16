#ifndef __IMAGE_H
#define __IMAGE_H
#include <stdlib.h>
#include <stdio.h>

int write_shorts_to_image(char* img_dir, short* data, int size);
short* message_from_file(char* img_dir);
int message_length_from_file(FILE* file);


#endif


