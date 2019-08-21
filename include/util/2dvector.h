#pragma once
#include "types.h"
class Vector2D
{
private:
    int32_t _x;
    int32_t _y;
public:
    Vector2D(int32_t x,int32_t y);
    Vector2D(const Vector2D& other);

    ~Vector2D();

    inline int32_t len();
    inline int32_t len2();
    inline int32_t X();
    inline int32_t Y();
    
    long operator += (const Vector2D& other);
    long operator -= (const Vector2D& other);
    bool operator == (const Vector2D& other);
    
    Vector2D& operator + (const Vector2D& other);
    Vector2D& operator - (const Vector2D& other);
    Vector2D& operator * (const Vector2D& other);
};
