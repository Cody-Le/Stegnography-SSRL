#include "image.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool head_parity_bit(char c_encoded);
char* decode_message(EncodedMessage encoded_message);
char dehamming_code(char c_encoded);
char correct_bits(char c);
char generate_correction_bit(char error);

int main(int argc, char** argv){
  char* img_dir = "./img/image.png";
  EncodedMessage encoded_message = message_from_file(img_dir);
  char* message = decode_message(encoded_message);
  printf("%s\n", message);
  free(encoded_message.data);
  

}


char* decode_message(EncodedMessage encoded_message){
  
  char* message = (char*)malloc(sizeof(char) * (encoded_message.size + 1));
  for (int i = 0; i < encoded_message.size; i++){
    short c_encoded = encoded_message.data[i];
    char c1_encoded = (char)(c_encoded >> 8);
    char c2_encoded = (char)c_encoded;
    char c1 = dehamming_code(c1_encoded);
    char c2 = dehamming_code(c2_encoded);
    
    char c = (c1 << 4) | c2;
    message[i] = c;

  }
  message[encoded_message.size] = '\0';
  return message;
}
char dehamming_code(char c_encoded){
  c_encoded = correct_bits(c_encoded);
  char c = c_encoded & 15;
  return c;
}




char correct_bits(char c_encoded){
  int* parity_matrix = get_parity_check_matrix();
  char error_location = byte_mul(c_encoded, parity_matrix, 7);
  char correction_bit = 0;
  if(!head_parity_bit(c_encoded)){
    if(error_location == 0){
      printf("A multi bit flip has occured, unable to correct\n");
      return c_encoded;
    }
  }
  if(error_location > 0){
    correction_bit = generate_correction_bit(error_location);
    char* correct_binary = byte_from_char(correction_bit);
    printf("correction bit at %s\n", correct_binary);
    free(correct_binary);
  }
  free(parity_matrix);
  return c_encoded ^ correction_bit;
}

//Check if the encoded parity bit is correct
bool head_parity_bit(char c_encoded){
  int c_no_head = c_encoded & 0x01111111;
  int parity = 0;
  int mask = 1;
  for (int i = 0; i < 8; i++){
    parity = parity ^ ((c_no_head & mask) >> i);
    mask = mask << 1;
  }
  int encoded_parity = c_encoded >> 7;
  return parity == encoded_parity;
}

char generate_correction_bit(char error){
  if(error == 4){
    return 1 << 6;
  }else if(error == 2){
    return 1 << 5;
  }else if(error == 1){
    return 1 << 4;
  }else if(error == 3){
    return 1 << 3;
  }else if(error == 5){
    return 1 << 2;
  }else if(error == 6){
    return 1 << 1;
  }else if(error == 7){
    return 1;
  }
} 