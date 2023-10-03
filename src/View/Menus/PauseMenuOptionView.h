#ifndef BOSCONIAN_PAUSEMENUOPTIONVIEW_H
#define BOSCONIAN_PAUSEMENUOPTIONVIEW_H

#include "MenuView.h"

#include "../../Model/Menus/PauseMenuOption.h"

class PauseMenuOptionView : public MenuView {
private:
    PauseMenuOption* menuModel;

public:
    PauseMenuOptionView(RenderEngine* renderEngine, PauseMenuOption* menuModel) : MenuView(renderEngine), menuModel(menuModel) {}

    void render() override {

    }
};


#endif //BOSCONIAN_PAUSEMENUOPTIONVIEW_H
