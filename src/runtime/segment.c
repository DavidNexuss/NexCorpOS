#include "stdafx.h"
#include "std/stdout.h"
#include "runtime/segment.h"

void printSegmentDebugInfo(){

    print("Segment information: CS: 0x");
    printhex(getCurrentCodeSegment());
    print(" DS: 0x");
    printhex(getCurrentDataSegment());
    print(" SS: 0x");
    printhex(getCurrentStackSegment());
    ln();
}