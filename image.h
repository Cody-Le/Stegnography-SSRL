#ifndef __IMAGE_H
#define __IMAGE_H
#include <stdlib.h>
#include <stdio.h>

typedef struct EncodedMessage{
    short* data;
    int size;
} EncodedMessage;

int write_shorts_to_image(char* img_dir, short* data, int size);
EncodedMessage message_from_file(char* img_dir);
int message_length_from_file(FILE* file);
void remove_message(char* img_dir);
char* copy_img_in_range(char* in_img_dir, char* out_img_dir, unsigned long copy_to);

#endif


