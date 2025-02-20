#ifndef DECODE
#define DECODE

#include "image.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool head_parity_bit(char c_encoded);
char* decode_message(EncodedMessage encoded_message);
char dehamming_code(char c_encoded, int index);
char correct_bits(char c, int index);
char generate_correction_bit(char error);

#endif