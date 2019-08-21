#pragma once
#include "drivers/driver_vga.h"
#include "util/vector.h"

class Widget;

class Widget{

    uint32_t x;
    uint32_t y;
    
    Widget* parent;
    vector<Widget*> childs;
    
    public:

    Widget(Widget* parent,uint32_t x,uint32_t y);
    ~Widget();
    
    virtual void render() {};
    
    void addChild(Widget* child); 
    void setPosition(uint32_t x,uint32_t y);
    Vector2D getGlobalPosition();

};

class RootWidget : public Widget{

    public:

    void render();
    RootWidget();
    ~RootWidget();

};