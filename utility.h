#ifndef HEADER_H
#define HEADER_H
#include <stdlib.h>


//A very simple down version of the matrix mul but for bits
int byte_mul(int data, int* matrix, int matrix_size);
//Give you the generator matrix based on Asecurity site
int* get_generator_matrix();
//Give you the parity check matrix based on Asecurity site
int* get_parity_check_matrix();
//Return the binary of a charater
//!!!!!Only used for debugging, memory leak if used in printf
//without initializing variable for it the freeing it later. 
char* byte_from_char(unsigned char c);

#endif 
