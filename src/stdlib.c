#include "stdlib.h"

void sleep(unsigned int t){

  t*= SLEEP;
  while(t--){}
}
void memset(void *s,char val,int count){

      char *sc = s;
      while(count--){

            *sc++ = val;
      }
}
