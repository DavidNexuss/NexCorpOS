#include "video/modes.h"
#include "types.h"
#include "util/vector.h"
#include "ui/widget.h"

class Session;
namespace sys{

  namespace ui{

    extern vector<Session*> sessions;
    extern Session* currentSession;
  }
}

class Session{

    uint8_t* buffer;
    
    ScreenMode mode;
    uint32_t ttyIndex;

    vector<Widget*> widgets;
    RootWidget* rootWidget;

    vector<Widget*> renderList;

  public:  
    Session(uint32_t ttyIndex,ScreenMode mode);
    ~Session();

    void renderAll();
    void clearScreen();
    
    void addWidget(Widget* widget);
    void deleteWidget(Widget* widget);
};