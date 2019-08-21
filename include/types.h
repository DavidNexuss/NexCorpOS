#pragma once
#define NULL 0
#define FALSE 0
#define TRUE 1
#define nullptr 0

#ifndef __cplusplus
    typedef int bool;
    #define true 1
    #define false 0
#endif

typedef int bool_t;

typedef unsigned int size_t;

typedef unsigned char byte_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;


typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

#ifdef __cplusplus
#include "runtime/string.h"

struct Vector2D{
    int32_t x;
    int32_t y;

    Vector2D(int32_t x,int32_t y);
    ~Vector2D();
};

struct ScreenMode{
	uint32_t width;
	uint32_t heihgt;
	uint8_t depth;

    ScreenMode(uint32_t width,uint32_t height,uint8_t depth);
    ~ScreenMode();
};

#endif
