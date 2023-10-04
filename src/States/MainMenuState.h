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
    MainMenuState(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler) {
        menuModel = new MainMenu();
        menuView = new MainMenuView(renderEngine, menuModel);
    };

    ~MainMenuState() {
        delete menuModel;
        delete menuView;
    }

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_MAINMENUSTATE_H
