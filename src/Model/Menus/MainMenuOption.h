#ifndef BOSCONIAN_MAINMENUOPTION_H
#define BOSCONIAN_MAINMENUOPTION_H

#include "Menu.h"
#include "Items/SwitchItem.h" // Include the header file for the SwitchItem class
#include "../../Utilities/Config.h"

class MainMenuOption : public Menu {
private:
    static MainMenuOption* instance;

    std::map<Option, SwitchItem> switchItems;

    MainMenuOption() {
        // Initialize the two SwitchItems with appropriate parameters
        switchItems = {
                {SWA, {8, {130, 100}, {45, 35}, "SWA"}},
                {SWB, {8, {630, 100}, {45, 35}, "SWB"}},
                {DEBUG, {1, {290, 275}, {60, 60}, "DEBUG MODE"}},
        };

        // Initialize the exit MenuItem and add it to the menuItems map
        menuItems = {
                {EXIT, {"Exit", {1000, 800}, {150, 50}, true}}
        };
    }

    ~MainMenuOption() = default;

public:
    static MainMenuOption* Instance() {
        if (!instance) {
            instance = new MainMenuOption();
            return instance;
        }
        return instance;
    }

    // Override the update method to handle SwitchItems
    void update() override {
        Menu::update();

        // Update the states of the SwitchItems
        for (auto& item : switchItems) {
            int switchIndex = item.second.containsPoint(mousePosition);

            if(switchIndex != -1 && isMouseButtonPressed) {
                clickedOption = item.first;
                item.second.toggleSwitch(switchIndex);
            }
        }
    }

    std::map<Option, SwitchItem> getSwitchItems() {
        return switchItems;
    }
};

#endif //BOSCONIAN_MAINMENUOPTION_H

