#include "utility.h"
#include <stdio.h>

int byte_mul(int data, int* matrix, int matrix_size){
  int result = 0;
  int data_bit = data;
  for (int i = 0; i < matrix_size; i++){
    int data_sign = data_bit & 1;
    //printf("sign: %d | matrix value: %d\n", data_sign, data_sign * matrix[i]);
    //printf("value of XOR: %d\n",result ^ (matrix[i] * data_sign));
    result = result ^ (matrix[i] * data_sign);
    data_bit = data_bit >> 1;
  }
  return result;
 
}

int* get_generator_matrix(){
  int* matrix = (int*)malloc(sizeof(int) * 4);
  matrix[0] = 0b1110001;
  matrix[1] = 0b1100010;
  matrix[2] = 0b1010100;
  matrix[3] = 0b0111000;
  return matrix;
}

int* get_parity_check_matrix(){
  int* matrix = (int*)malloc(sizeof(int) * 8);
  matrix[0] = 0b111;
  matrix[1] = 0b110;
  matrix[2] = 0b101;
  matrix[3] = 0b011;
  matrix[4] = 0b001;
  matrix[5] = 0b010;
  matrix[6] = 0b100;
  return matrix;
}

char* byte_from_char(unsigned char n){
  unsigned int bits[8] = {0};
  char* binary = (char*) malloc(sizeof(char) * 9);
  unsigned int quotient = (unsigned int)n;

  int size = 0;
  while(quotient > 0){
    unsigned int remainder = quotient % 2;
    quotient = quotient/2;
    bits[size] = remainder;
    size++;
  }

  int binary_index = 0;
  for (int i = 7; i >= 0; i--){
    if(bits[i] == 1){
      binary[binary_index] = '1';
    }else{
      binary[binary_index] = '0';
    }
    binary_index++;
  }

  
  return binary;
}
