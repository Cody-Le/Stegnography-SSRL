#include "image.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

char* decode_message(EncodedMessage encoded_message);
char dehamming_code(char c_encoded);

int main(int argc, char** argv){
  char* img_dir = "./img/image.png";
  EncodedMessage encoded_message = message_from_file(img_dir);
  decode_message(encoded_message);
  printf("\n");
  free(encoded_message.data);

}


char* decode_message(EncodedMessage encoded_message){
  int* parity_matrix = get_parity_check_matrix();
  char* message = (char*)malloc(sizeof(char) * encoded_message.size);
  for (int i = 0; i < encoded_message.size; i++){
    short c_encoded = encoded_message.data[i];
    char c1_encoded = (char)(c_encoded >> 8);
    char c2_encoded = (char)c_encoded;
    char c1 = dehamming_code(c1_encoded);
    char c2 = dehamming_code(c2_encoded);
    char c = (c1 << 4) | c2;
    printf("%c \n", c);

  }
}
char dehamming_code(char c_encoded){
  char c = c_encoded & 15;
  return c;
}