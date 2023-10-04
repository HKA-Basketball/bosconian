#ifndef BOSCONIAN_MAINMENU_H
#define BOSCONIAN_MAINMENU_H

#include "Menu.h"

#include "../../Utilities/Config.h"
#include "../../Utilities/Vector2D.h"

class MainMenu : public Menu {
public:
    MainMenu() {
        menuItems = {
                {START, {"Start", {Config::titlePositionX, 350}, {150, 30}, true}},
                {OPTIONS, {"Options", {Config::titlePositionX, 400}, {220, 30}, true}},
                {EXIT, {"Exit", {Config::titlePositionX, 450}, {140, 30}, true}}
        };
    };

    ~MainMenu() = default;
};


#endif //BOSCONIAN_MAINMENU_H
