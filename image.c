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

short* message_from_file(char* img_dir){
 
  FILE *file = fopen(img_dir, "r");
  if(file == NULL){
    return NULL;
  }
  
  int message_length = message_length_from_file(file);

  printf("message length: %d\n", message_length);
  fseek(file,-message_length * 2, SEEK_END);
  short* encoded_message = (short*)malloc(sizeof(short) * message_length);
  fread(encoded_message, sizeof(short), message_length, file);
  fclose(file);
  return encoded_message;
}

int message_length_from_file(FILE* file){
  long IEND_CHUNK = 0x826042ae444e4549; //IEND CHUNK in hex form
  
  if(file == NULL){
    return -1;
  }

  long file_size = ftell(file);
  printf("FILE SIZE IS : %ld\n", file_size);
  long check_range = 256;
  int offset = 0;
  int message_length = 0;
  long check_buffer[1];
  while(check_range > 0){
    offset++;
    fseek(file, -offset * sizeof(short), SEEK_END);
    long byte_read = fread(check_buffer, sizeof(long), 1, file);
    check_range -= 1;
    long check = check_buffer[0] ^ IEND_CHUNK;
    printf("output : %lx | byte_read: %ld\n", check, byte_read);
    if(check == 0){
      check_range = 0;
    }

  }
  return offset - 4;
  
}


