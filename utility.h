#ifndef HEADER_H
#define HEADER_H
#include <stdlib.h>

int byte_mul(int data, int* matrix, int matrix_size);
int* get_generator_matrix();
int* get_parity_check_matrix();
char* byte_from_char(unsigned char c);

#endif 
