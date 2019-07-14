#include "system.h"

void *__gxx_personality_v0;
void *_Unwind_Resume;
void sleep(unsigned int t){

  t*= SLEEP;
  while(t--){}
}
