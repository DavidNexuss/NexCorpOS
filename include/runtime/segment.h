#pragma once
#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

extern uint16_t getCurrentCodeSegment();
extern uint16_t getCurrentDataSegment();
extern uint16_t getCurrentStackSegment();
extern uint16_t getCurrentStackPointer();

void printSegmentDebugInfo();
 
#ifdef __cplusplus
}
#endif