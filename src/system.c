#include "system.h"

void sleep(unsigned int t){

  t*= SLEEP;
  while(t--){}
}
