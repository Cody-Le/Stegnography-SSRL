#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utility.h"
#include "image.h"
#include <fcntl.h>

void append_string_to_png();
void read_binary_png();
short* build_encoded_message(char* message);
char hamming_encode(char c);
char head_parity_bit(char c);
void print_encoded_char(char c);

int main(int argc, char** argv){
  if(argc < 2){
    printf("need to add a message as an argument\n");
    return 0;
  }
  char* message = argv[1];
  short* encoded_message = build_encoded_message(message);
  int status = write_shorts_to_image("./img/image.png", encoded_message, strlen(message));
  printf("Number of element written: %d\n", status);
  
}


short* build_encoded_message(char* message){
  int len = (int)strlen(message) * 2;
  short* encoded_m = (short*)malloc(strlen(message) * sizeof(short));
  for (int i = 0; i < len; i += 2){
    char c = message[i / 2];
    char c1 = c >> 4;
    char c2 = (c & 15);
    unsigned char c1_encoded = hamming_encode(c1);
    unsigned char c2_encoded = hamming_encode(c2);
    short c_short = ((short) c1_encoded << 4) | (short) c2_encoded;
    encoded_m[i/2] = c_short;

  }
  return encoded_m;
  
}

char hamming_encode(char c){
  int* encode_matrix = get_generator_matrix();
  int encoded_byte = byte_mul((int) c, encode_matrix,4);
  char with_head = head_parity_bit(encoded_byte);
  return (char) encoded_byte;
}

char head_parity_bit(char c){
  int parity = 0;
  int mask = 1;
  for (int i = 0; i < 8; i++){
    parity = parity ^ ((c & mask) >> i);
    mask = mask << 1;
  }

  parity = parity << 7;
  return (char)(c | parity);
}

