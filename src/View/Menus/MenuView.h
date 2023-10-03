#ifndef BOSCONIAN_MENUVIEW_H
#define BOSCONIAN_MENUVIEW_H

#include "../RenderEngine.h"

class MenuView {
protected:
    RenderEngine* renderEngine;

public:
    explicit MenuView(RenderEngine* renderEngine) : renderEngine(renderEngine) {};

    virtual void render() = 0;
};


#endif //BOSCONIAN_MENUVIEW_H
