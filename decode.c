#include "image.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv){
  long IEND_CHUNK = 0x826042ae444e4549;
  char* img_dir = "./img/image.png";
  FILE *file = fopen(img_dir, "r");
  if(file == NULL){
    return 0;
  }

  long file_size = ftell(file);
  printf("FILE SIZE IS : %ld\n", file_size);
  long check_range = 256;
  int i = 1;
  long check_buffer[1];
  while(check_range > 0){
    fseek(file, -i * sizeof(short), SEEK_END);
    long byte_read = fread(check_buffer, sizeof(long), 1, file);
    check_range -= 1;
    long check = check_buffer[0] ^ IEND_CHUNK;
    printf("output : %lx | byte_read: %ld\n", check, byte_read);
    if(check == 0){
      check_range = 0;
    }
    if(i % 16 == 0){
      printf("\n");
    }
    
    i++;
  }

  fclose(file);

}
