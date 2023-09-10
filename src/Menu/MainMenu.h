#ifndef BOSCONIAN_MAINMENU_H
#define BOSCONIAN_MAINMENU_H

#include <string>
#include <vector>
#include <iostream>
#include "SDL_rect.h"

class MainMenu {
public:
    MainMenu() {
        initializeOptions();
    }

    ~MainMenu();

    void update();

    const std::vector<std::string>& getOptions() const { return options; }
    size_t getSelectedIndex() const { return selectedIndex; }

private:
    std::vector<std::string> options = {"Start", "Option", "Exit"}; // Menu options
    std::vector<SDL_Rect> optionRects; // Rectangles representing the position and size of each option
    size_t selectedIndex = 0; // Index of the currently selected option

    void initializeOptions() {
        options = {"Start", "Option", "Exit"}; // Setting up the menu options
    }
};

#endif //BOSCONIAN_MAINMENU_H
