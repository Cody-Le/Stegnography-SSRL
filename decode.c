#include "decode.h"

/*This file is responsbile for decoding a message
placed at the end of an image, encoded in Hamming(8,4)
format. 
*/


//Main function, take in an image directory as an argument 
//from the command line
int main(int argc, char** argv){
  if(argc < 2){
    printf("Please enter the directory to the image!\n");
    return 0;
  }
  EncodedMessage encoded_message = message_from_file(argv[1]);
  if(encoded_message.size == 0){
    printf("No message were found in the file!");
  }
  char* message = decode_message(encoded_message);
  printf("%s\n", message);
  free(encoded_message.data);
  

}

/*
Decode the message read from the bottom of the image. 
*/
char* decode_message(EncodedMessage encoded_message){
  
  char* message = (char*)malloc(sizeof(char) * (encoded_message.size + 1));
  for (int i = 0; i < encoded_message.size; i++){
    short c_encoded = encoded_message.data[i];
    char c1_encoded = (char)(c_encoded >> 8);
    char c2_encoded = (char)c_encoded;
    char c1 = dehamming_code(c1_encoded, i);
    char c2 = dehamming_code(c2_encoded, i);
    
    char c = (c1 << 4) | c2;
    if(c == '\0'){
      printf("ignoring a null character that has been detected in between message\n");
      c = (c1_encoded << 4) | (c2 & 15);
    }
    
    message[i] = c;

  }
  message[encoded_message.size] = '\0';
  return message;
}

//decode half a byte from it's hamming code
//counter part. The index is passed in 
//to print out the location of the bit flip
char dehamming_code(char c_encoded, int index){
  c_encoded = correct_bits(c_encoded, index);
  char c = c_encoded & 15;
  return c;
}



//Correcting any single bit flip that might have occured
//and detect multiple bit flip cases. 
char correct_bits(char c_encoded, int index){
  int* parity_matrix = get_parity_check_matrix();
  char error_location = byte_mul(c_encoded, parity_matrix, 7);
  char correction_bit = 0;
  if(!head_parity_bit(c_encoded)){
    if(error_location == 0){
      printf("a multi bit flip has been detected at %d\n", index);
      return c_encoded;
    }
  }
  if(error_location > 0){
    correction_bit = generate_correction_bit(error_location);
    char* correct_binary = byte_from_char(correction_bit);
    printf("single bit flip on char at %d, correcting with byte of %s\n", index, correct_binary);
    free(correct_binary);
  }
  free(parity_matrix);
  return c_encoded ^ correction_bit;
}

//Check if the encoded parity bit is correct.
bool head_parity_bit(char c_encoded){
  char c_no_head = c_encoded & 127;
  int parity = 0;
  int mask = 1;
  for (int i = 0; i < 8; i++){
    parity = parity ^ ((c_no_head & mask) >> i);
    mask = mask << 1;
  }
  char encoded_parity = (c_encoded >> 7) & 1;
  return parity == encoded_parity;
}


/*
Mapping the output of the parity check 
from to the correct bit to flip. 
Note: I am sure there is a better
way to do this but for some reason
I just can't figure so here we are. 
*/
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