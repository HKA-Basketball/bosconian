#ifndef BOSCONIAN_MAINMENUSTATE_H
#define BOSCONIAN_MAINMENUSTATE_H

#include "State.h"

#include "../Model/Menus/MainMenu.h"
#include "../View/Menus/MainMenuView.h"
#include "../Controller/InputHandler.h"

class MainMenuState : public State {
    MainMenu* menuModel;
    MainMenuView* menuView;

public:
    MainMenuState() {
        menuModel = MainMenu::Instance();
        menuView = new MainMenuView(RenderEngine::Instance(), menuModel);
    };

    ~MainMenuState() {
        delete menuView;
    }

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_MAINMENUSTATE_H
