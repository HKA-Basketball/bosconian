#ifndef BOSCONIAN_PAUSEMENU_H
#define BOSCONIAN_PAUSEMENU_H

#include "Menu.h"

#include "../../Utilities/Config.h"
#include "../../Utilities/Vector2D.h"

class PauseMenu : public Menu {
public:
    PauseMenu() {
        menuItems = {
                {CONTINUE, {"Continue", {Config::titlePositionX, 350}, {250, 30}, true}},
                {OPTIONS, {"Options", {Config::titlePositionX, 400}, {220, 30}, true}},
                {MAIN_MENU, {"Main Menu", {Config::titlePositionX, 450}, {280, 30}, true}},
                {EXIT, {"Exit", {Config::titlePositionX, 500}, {140, 30}, true}}
        };
    };

    ~PauseMenu() = default;
};


#endif //BOSCONIAN_PAUSEMENU_H
