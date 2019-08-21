#include "video/session.h"
#include "drivers/driver_vga.h"
#include "system.h"

namespace sys{

    namespace ui{

        vector<Session*> sessions;
        Session* currentSession;
    }
}
Session::Session(uint32_t p_ttyIndex,ScreenMode p_mode):
mode(p_mode)
{

    ttyIndex = p_ttyIndex;
    mode = p_mode;

    buffer = new uint8_t[mode.width * mode.heihgt * mode.depth / 8];
    
    rootWidget = new RootWidget();
    widgets.push_back(rootWidget);
}

Session::~Session(){

    delete [] buffer;
}

void Session::clearScreen(){

    for (int32_t x = 0; x < mode.width; x++)
    {
        for (int32_t y = 0; y < mode.heihgt; y++)
        {
            sys::vga_driver->PutPixel(x,y,3);
        }
    }
    
}
void Session::renderAll(){

    clearScreen();
    for (size_t i = 0; i < renderList.size(); i++)
    {
        widgets[i]->render();
    }
}

void Session::addWidget(Widget* widget){

    widgets.push_back(widget);
}

void Session::deleteWidget(Widget* widget){

    delete widget;
}