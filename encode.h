#ifndef __ENCODE_
#define __ENCODE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#include "image.h"

short* build_encoded_message(char* message);
char hamming_encode(char c);
char head_parity_bit(char c);

#endif