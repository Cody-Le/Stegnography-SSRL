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

EncodedMessage message_from_file(char* img_dir){
 
  FILE *file = fopen(img_dir, "r");
  EncodedMessage encoded_message;
  if(file == NULL){
    encoded_message.data = NULL;
    encoded_message.size = 0;
    return encoded_message;
  }
  
  int message_length = message_length_from_file(file);

  fseek(file,-message_length * 2, SEEK_END);
  short* encoded_data = (short*)malloc(sizeof(short) * message_length);
  fread(encoded_data, sizeof(short), message_length, file);
  fclose(file);
  
  encoded_message.data = encoded_data;
  encoded_message.size = message_length;
  return encoded_message;
}

int message_length_from_file(FILE* file){
  long IEND_CHUNK = 0x826042ae444e4549; //IEND CHUNK in hex form
  
  if(file == NULL){
    return -1;
  }

  long file_size = ftell(file);
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
    //printf("output : %lx | byte_read: %ld\n", check, byte_read);
    if(check == 0){
      check_range = 0;
    }

  }
  return offset - 4;
  
}

int ask_to_proceed(){
  printf("There is a message hidden in the given image directory.\n");
  printf("Would you like proceed and override the message? y for yes or any other character for no: ");
  char answer;
  scanf("%c", &answer);
  if(answer == 'y'){
    printf("proceeding!\n");
    return 0;
  }else{
    printf("cancelling...\n");
    return -1;
  }

}

int check_and_remove_message(char* img_dir){
  FILE* file = fopen(img_dir, "a+");
  if(file == NULL){
    perror("Unable to open file.\n");
    return -1;
  }
  int message_length = message_length_from_file(file);
  if(message_length <= 0){
    printf("No message in the input image, proceeding!\n");
    return 0;
  }else{
    if(ask_to_proceed() == -1){
      return -1;
    }
  }
  
  fseek(file, -message_length * 2, SEEK_END);
  unsigned long copy_to = ftell(file);
  char* new_image = copy_img_in_range(img_dir, "temp_img", copy_to);

  fclose(file);
  remove(img_dir);
  rename(new_image, img_dir);
  return 0;
}



char* copy_img_in_range(char* in_img_dir, char* out_img_dir, unsigned long copy_to){
  FILE* in_file = fopen(in_img_dir, "rb");
  FILE* out_file = fopen(out_img_dir, "wb");
  
  char* buffer = (char*) malloc(sizeof(char) * copy_to);
  size_t bytes = fread(buffer, 1, copy_to, in_file);
  fwrite(buffer, 1, copy_to, out_file);
  fclose(in_file);
  fclose(out_file);
  return out_img_dir;


}