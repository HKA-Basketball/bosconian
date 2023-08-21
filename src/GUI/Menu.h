#ifndef BOSCONIAN_MENU_H
#define BOSCONIAN_MENU_H

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"
#include "../Event/EventManager.h"
#include "../Drawing/Graphics.h"

/**
 * The Menu namespace encapsulates classes and functionality related to creating and displaying menus.
 */
namespace Menu {

    /**
     * Structure representing a menu option.
     */
    struct MenuOption {
        std::string option; /** The text of the menu option. */
        std::function<void()> callback; /** The callback function associated with the option. */

        /**
         * Constructs a MenuOption instance.
         * \param option The text of the menu option.
         * \param callback The callback function associated with the option.
         */
        MenuOption(const std::string& option, std::function<void()> callback)
                : option(option), callback(callback)
        {}
    };

    /**
     * The MenuModel class handles the menu's data and logic.
     */
    class MenuModel {
    private:
        std::vector<MenuOption> m_options;
        int m_selectedIndex;

    public:
        /**
         * Constructs a MenuModel instance.
         */
        MenuModel() : m_selectedIndex(0) {}

        /**
         * Adds a new option to the menu.
         * \param option The text of the new option.
         * \param callback The callback function associated with the option.
         */
        void addOption(std::string option, std::function<void()> callback) {
            m_options.emplace_back(option, callback);
        }

        /**
         * Selects the next option in the menu.
         */
        void selectNextOption() {
            if (m_selectedIndex < m_options.size() - 1) {
                m_selectedIndex++;
            }
            else {
                m_selectedIndex = 0;
            }
        }

        /**
         * Selects the previous option in the menu.
         */
        void selectPreviousOption() {
            if (m_selectedIndex > 0) {
                m_selectedIndex--;
            }
            else {
                m_selectedIndex = m_options.size() - 1;
            }
        }

        /**
         * Sets the selected option by index.
         * \param newSelect The index of the option to be selected.
         */
        void setSelectOption(int newSelect) {
            if (newSelect < 0 || newSelect > m_options.size() - 1) {
                return;
            }

            m_selectedIndex = newSelect;
        }

        /**
         * Retrieves the index of the currently selected option.
         * \return The index of the selected option.
         */
        int getSelectedIndex() const {
            return m_selectedIndex;
        }

        /**
         * Retrieves the text of the currently selected option.
         * \return The text of the selected option.
         */
        const std::string& getSelectedOption() const {
            return m_options[m_selectedIndex].option;
        }

        /**
         * Retrieves the total number of options in the menu.
         * \return The number of menu options.
         */
        size_t getNumOptions() const {
            return m_options.size();
        }

        /**
         * Retrieves the text of an option by index.
         * \param index The index of the option.
         * \return The text of the specified option.
         */
        const std::string& getOption(size_t index) const {
            return m_options[index].option;
        }

        /**
         * Calls the callback function associated with the selected option.
         */
        void callbackSelectedOption() const {
             m_options[m_selectedIndex].callback();
        }

        /**
         * Calls the callback function associated with a specific option.
         * \param index The index of the option.
         */
        void callbackOption(size_t index) const {
            m_options[index].callback();
        }
    };


    /**
     * The MenuView class handles the rendering of the menu.
     */
    class MenuView {
    private:
        Drawing::Graphics* m_drawing;
        TTF_Font* m_font;
        SDL_Rect m_menuRect;
        SDL_Color m_normalColor;
        SDL_Color m_selectedColor;
        int m_lineHeight;
        int m_textHeight;

    public:
        /**
         * Constructs a MenuView instance.
         * \param drawing Drawing graphics interface.
         * \param font Font used for rendering text.
         * \param menuRect Rectangle representing the menu's position and size.
         * \param normalColor Color of normal menu text.
         * \param selectedColor Color of selected menu text.
         * \param lineHeight Height of each line in the menu.
         */
        MenuView(Drawing::Graphics* drawing, TTF_Font* font, SDL_Rect menuRect, SDL_Color normalColor, SDL_Color selectedColor, int lineHeight)
                : m_drawing(drawing)
                , m_font(font)
                , m_menuRect(menuRect)
                , m_normalColor(normalColor)
                , m_selectedColor(selectedColor)
                , m_lineHeight(lineHeight)
        {}

        /**
         * Renders the menu based on the provided model.
         * \param model The MenuModel instance containing menu data.
         */
        void render(const MenuModel& model) {
            m_drawing->fillRectangleOutline({78, 78, 78, 100}, m_menuRect);

            int y = m_menuRect.y;
            for (size_t i = 0; i < model.getNumOptions(); i++) {
                SDL_Color color = (i == model.getSelectedIndex()) ? m_selectedColor : m_normalColor;

                int textWidth, textHeight;
                TTF_SizeText(m_font, model.getOption(i).c_str(), &textWidth, &textHeight);
                m_textHeight = textHeight;

                m_drawing->string(model.getOption(i), m_font, color,
                                  {static_cast<float>(m_menuRect.x + (m_menuRect.w/2)), static_cast<float>(y + (textHeight/2))},
                                  2);

                y += m_lineHeight;
            }
        }

        /**
         * Retrieves the height of the text rendered in the menu.
         * \return The text height.
         */
        int getTextHeight() const {
            return m_textHeight;
        }

        /**
         * Retrieves the menu rectangle representing position and size.
         * \return The menu rectangle.
         */
        const SDL_Rect &getMenuRect() const {
            return m_menuRect;
        }

        /**
         * Retrieves the height of each line in the menu.
         * \return The line height.
         */
        int getLineHeight() const {
            return m_lineHeight;
        }
    };

    /**
     * The Menu class manages the menu's data and rendering.
     */
    class Menu {
    private:
        MenuModel m_model;
        MenuView m_view;
        Event::EventManager* g_event;

    public:
        /**
         * Constructs a Menu instance.
         * \param font Font used for rendering menu text.
         * \param menuRect Rectangle representing the menu's position and size.
         * \param normalColor Color of normal menu text.
         * \param selectedColor Color of selected menu text.
         * \param lineHeight Height of each line in the menu.
         */
        Menu(TTF_Font* font, SDL_Rect menuRect, SDL_Color normalColor, SDL_Color selectedColor, int lineHeight)
                : m_model()
                , m_view(Drawing::g_drawing, font, menuRect, normalColor, selectedColor, lineHeight)
                , g_event(Event::g_event)
        {}

        /**
         * Adds a new option to the menu.
         * \param option The text of the new option.
         * \param callback The callback function associated with the option.
         */
        void addOption(std::string option, std::function<void()> callback) {
            m_model.addOption(option, callback);
        }

        /**
         * Handles events related to the menu.
         */
        void handleEvent() {
            if (!g_event)
                return;

            SDL_Rect rec = m_view.getMenuRect();
            int y = rec.y;
            for (size_t i = 0; i < m_model.getNumOptions(); i++) {
                SDL_FRect inRect = {static_cast<float>(rec.x), static_cast<float>(y), static_cast<float>(rec.w), static_cast<float>(m_view.getTextHeight())};
                bool isIn = false;
                if (Utils::render::isCursorInRect({inRect.x, inRect.y}, {inRect.w, inRect.h})) {
                    m_model.setSelectOption(i);
                    isIn = true;
                }
                if (isIn && g_event->isMouseClicked(1, true)) {
                    m_model.callbackSelectedOption(); // Invoke the associated callback
                }

                y += m_view.getLineHeight();
            }

            if (g_event->isKeyClicked(SDL_SCANCODE_UP, true)) {
                m_model.selectPreviousOption();
            }
            if (g_event->isKeyClicked(SDL_SCANCODE_DOWN, true)) {
                m_model.selectNextOption();
            }

            if (g_event->isKeyClicked(SDL_SCANCODE_RIGHT, true)) {
                m_model.callbackSelectedOption(); // Invoke the associated callback
            }
        }

        /**
         * Renders the menu.
         */
        void render() {
            m_view.render(m_model);
        }
    };

} // Menu

#endif //BOSCONIAN_MENU_H
