#ifndef BOSCONIAN_MAINMENUOPTIONSTATE_H
#define BOSCONIAN_MAINMENUOPTIONSTATE_H

#include "State.h"

#include "../Model/Menus/MainMenuOption.h"
#include "../View/Menus/MainMenuOptionView.h"
#include "../Controller/InputHandler.h"

class MainMenuOptionState : public State {
    MainMenuOption* menuModel;
    MainMenuOptionView* menuView;

public:
    explicit MainMenuOptionState(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler) {
        menuModel = MainMenuOption::Instance();
        menuView = new MainMenuOptionView(renderEngine, menuModel);
    }

    ~MainMenuOptionState() {
        delete menuView;
    }

    void onEnter() override;
    void onExit() override;

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_MAINMENUOPTIONSTATE_H
