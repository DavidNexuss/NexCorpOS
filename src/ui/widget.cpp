#include "config.h"
#include "ui/widget.h"


Widget::Widget(Widget* pparent,uint32_t px,uint32_t py){
    x = px;
    y = py;
    parent = pparent;
}
Widget::~Widget(){}

void Widget::addChild(Widget* child){
    if(!childs.contains(child))childs.push_back(child);
}
void Widget::setPosition(uint32_t px,uint32_t py){
    x = px;
    y = py;
}

Vector2D Widget::getGlobalPosition(){

    int32_t tx = x;
    int32_t ty = y;

    Widget* m = parent;
    while (m)
    {
        tx += m->x;
        ty += m->y;
        m = m->parent;
    }
    
    return Vector2D(tx,ty);
}

RootWidget::RootWidget() : Widget(0,0,0){}
void RootWidget::render(){}