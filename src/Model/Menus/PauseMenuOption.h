#ifndef BOSCONIAN_PAUSEMENUOPTION_H
#define BOSCONIAN_PAUSEMENUOPTION_H

#include "Menu.h"
#include "Items/SwitchItem.h"

class PauseMenuOption : public Menu {
    std::map<Option, SwitchItem>* switchItems;

public:
    PauseMenuOption() {
        // Initialize the two SwitchItems with appropriate parameters
        switchItems = new std::map<Option, SwitchItem>{
                {DEBUG, {1, {275, 350}, {50, 50}, "DEBUG MODE"}},
        };

        // Initialize the exit MenuItem and add it to the menuItems map
        menuItems = {
                {EXIT, {"Exit", {675, 675}, {150, 50}, true}}
        };
    }

    ~PauseMenuOption() {
        delete switchItems;
    };

    // Override the update method to handle SwitchItems
    void update() override {
        Menu::update();

        // Update the states of the SwitchItems
        for (auto& item : *switchItems) {
            int switchIndex = item.second.containsPoint(mousePosition);

            if(switchIndex != -1 && isMouseButtonPressed) {
                clickedOption = item.first;
                item.second.toggleSwitch(switchIndex);
            }
        }
    }

    std::map<Option, SwitchItem>* getSwitchItems() {
        return switchItems;
    }
};


#endif //BOSCONIAN_PAUSEMENUOPTION_H
