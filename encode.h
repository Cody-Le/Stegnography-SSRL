#ifndef __ENCODE_
#define __ENCODE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#include "image.h"

/*
For each character, it split the character into two parts, then encode 
them and put them into a short to be written down onto the image. 
*/
short* build_encoded_message(char* message);
//Encoded half a character, the first four bits from the left is assumed to be zero
char hamming_encode(char c);
//Create a new bytes with an extend parity bit from the parity of the entire thing.
char head_parity_bit(char c);

#endif