#pragma once
#include "types.h"

void initGDBStub();


#ifdef __cplusplus
extern "C"{
#endif

    void putDebugChar(uint8_t data);/* write a single character      */
    int getDebugChar();	/* read and return a single char */

#ifdef __cplusplus
}
#endif