#ifndef DECODE_H
#define DECODE_H

#include "image.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




//Decode the message read from the bottom of the image. 
char* decode_message(EncodedMessage encoded_message);
//decode half a byte from it's hamming code
//counter part. The index is passed in 
//to print out the location of the bit flip
char dehamming_code(char c_encoded, int index);

//Correcting any single bit flip that might have occured
//and detect multiple bit flip cases. 
char correct_bits(char c, int index);
//Check if the encoded parity bit is correct.
bool head_parity_bit(char c_encoded);
//Map the output of a parity check matrix to the correct
//bit to flip
char generate_correction_bit(char error);


#endif