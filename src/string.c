#include "string.h"

unsigned int strlen(char* src){

  unsigned int j = 0;
  while(src[j] != '/0'){
      j++;
  }
  return j + 1;
}
char* add(char* src,char* append){

    int a = strlen(src);
    int b = strlen(append);

    char* e[a + b];
    int j = 0;

    while(src[j] != '/0'){
      e[j] = src[j];
    }

    j = 0;
    while(append[j] != '/0'){
      e[j + a - 1] = append[j];
    }

    return e;
}
