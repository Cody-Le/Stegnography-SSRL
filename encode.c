#include "encode.h"


/*
This program is responsible to for taking a message and image directory from
the argument and encode it in the Hamming(8,4) extended format.
*/

//Take in argument in format of: message img_dir
int main(int argc, char** argv){

  
  if(argc < 3){
    printf("Need to add arguments in format: message image_dir\n");
    return 0;
  }
  //Name is not available because I use it for removing old message
  if(strcmp(argv[2], "copy_temp") == 0){
    printf("Sorry, cannot use a file under copy_temp as the name.\n");
  }
  int check_status = check_and_remove_message(argv[2]);
  if(check_status == -1){
    return 0;
  }
  char* message = argv[1];
  short* encoded_message = build_encoded_message(message);
  int write_status = write_shorts_to_image(argv[2], encoded_message, strlen(message));
  printf("Number of element written: %d\n", write_status);
  if(write_status == strlen(message)){
    printf("Succesfully write the message.\n");
  }else{
    printf("Something went wrong and the message wasn't written.\n");
  }
  
  return 0;
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
    // A lot of memory leak down here 
    //printf("original c: %c (%s) -> c1, %s | c2, %s\n", c, byte_from_char(c), byte_from_char(c1_encoded), byte_from_char(c2_encoded));
    // ^ debug only, memory leak if leave on
    short c_short = ((short) c1_encoded << 8) | (short) c2_encoded;
    encoded_m[i/2] = c_short;

  }
  return encoded_m;
  
}

char hamming_encode(char c){
  int* encode_matrix = get_generator_matrix();
  int encoded_byte = byte_mul((int) c, encode_matrix,4);
  char with_head = head_parity_bit(encoded_byte);
  free(encode_matrix);
  return (char) with_head;
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

