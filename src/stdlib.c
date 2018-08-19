#include "stdlib.h"

void memset(void *s,char val,int count){

      char *sc = s;
      while(count--){

            *sc++ = val;
      }
}
