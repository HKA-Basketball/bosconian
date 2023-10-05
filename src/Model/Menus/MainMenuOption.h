#ifndef BOSCONIAN_MAINMENUOPTION_H
#define BOSCONIAN_MAINMENUOPTION_H

#include "Menu.h"
#include "Items/SwitchItem.h" // Include the header file for the SwitchItem class
#include "../../Utilities/Config.h"

class MainMenuOption : public Menu {
    std::map<Option, SwitchItem>* switchItems;

public:
    MainMenuOption() {
        // Initialize the two SwitchItems with appropriate parameters
        switchItems = new std::map<Option, SwitchItem>{
                {SWA,           {8, {130, 100}, {45, 35}, "SWA"}},
                {SWB,           {8, {630, 100}, {45, 35}, "SWB"}},
                {DEBUG,         {1, {290, 275}, {60, 60}, "DEBUG MODE"}},
                {CUSTOM_LEVELS, {1, {790, 275}, {60, 60}, "CUSTOM LEVELS"}},
        };

        // Initialize the exit MenuItem and add it to the menuItems map
        menuItems = {
                {EXIT, {"Exit", {1000, 800}, {150, 50}, true}}
        };
    }

    ~MainMenuOption() {
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

#endif //BOSCONIAN_MAINMENUOPTION_H

