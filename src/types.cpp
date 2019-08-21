#include "types.h"

Vector2D::Vector2D(int32_t px,int32_t py){
    x = px;
    y = py;
}

ScreenMode::ScreenMode(uint32_t p_width,uint32_t p_height,uint8_t p_depth){

    width = p_width;
    heihgt = p_height;
    depth = p_depth;
}

ScreenMode::~ScreenMode(){}