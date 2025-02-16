#include "image.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv){
  char* img_dir = "./img/image.png";
  short* encoded_message = message_from_file(img_dir);
  int length = sizeof(encoded_message)/sizeof(short);
  printf("length gotten in main %d\n", length );
  for (int i = 0; i < length; i++){
    printf("%hx ", encoded_message[i]);
  
  }
  printf("\n");
  

}
