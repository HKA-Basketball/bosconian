#ifndef BOSCONIAN_PAUSEMENU_H
#define BOSCONIAN_PAUSEMENU_H

#include "Menu.h"

#include "../../Utilities/Config.h"
#include "../../Utilities/Vector2D.h"

class PauseMenu : public Menu {
public:
    PauseMenu() {
        menuItems = {
                {CONTINUE, {"Continue", {Config::pausePositionX, 400}, {250, 30}, true}},
                {OPTIONS, {"Options", {Config::pausePositionX, 450}, {220, 30}, true}},
                {MAIN_MENU, {"Main Menu", {Config::pausePositionX, 500}, {280, 30}, true}},
                {EXIT, {"Exit", {Config::pausePositionX, 550}, {140, 30}, true}}
        };
    };

    ~PauseMenu() = default;
};


#endif //BOSCONIAN_PAUSEMENU_H
