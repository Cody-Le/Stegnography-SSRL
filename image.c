#include "image.h"

//Return size_written if successful, -1 if not
int write_shorts_to_image(char* img_dir, short* data, int m_size){
  FILE *file = fopen(img_dir, "a+");
  if (file != NULL){
    int size_t = fwrite(data, sizeof(short), m_size, file);
    fclose(file);
    return size_t;
  }else{
    return -1;
  }
}


