#include "stdafx.h"
#include "std/stdout.h"
#include "runtime/segment.h"

void printSegmentDebugInfo(){

    print("Segment information: CS: ");
    printint(getCurrentCodeSegment());
    print(" DS: ");
    printint(getCurrentDataSegment());
    print(" SS: ");
    printint(getCurrentStackSegment());
    ln();
}