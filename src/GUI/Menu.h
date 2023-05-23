#ifndef BOSCONIAN_MENU_H
#define BOSCONIAN_MENU_H

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"
#include "../Event/EventManager.h"
#include "../Drawing/Graphics.h"

namespace Menu {

    class MenuModel {
    private:
        std::vector<std::string> m_options;
        int m_selectedIndex;

    public:
        MenuModel() : m_selectedIndex(0) {}

        void addOption(std::string option) {
            m_options.push_back(option);
        }

        void selectNextOption() {
            if (m_selectedIndex < m_options.size() - 1) {
                m_selectedIndex++;
            }
            else {
                m_selectedIndex = 0;
            }
        }

        void selectPreviousOption() {
            if (m_selectedIndex > 0) {
                m_selectedIndex--;
            }
            else {
                m_selectedIndex = m_options.size() - 1;
            }
        }

        int getSelectedIndex() const {
            return m_selectedIndex;
        }

        const std::string& getSelectedOption() const {
            return m_options[m_selectedIndex];
        }

        size_t getNumOptions() const {
            return m_options.size();
        }

        const std::string& getOption(size_t index) const {
            return m_options[index];
        }
    };


    class MenuView {
    private:
        Drawing::Graphics* m_drawing;
        TTF_Font* m_font;
        SDL_Rect m_menuRect;
        SDL_Color m_normalColor;
        SDL_Color m_selectedColor;
        int m_lineHeight;

    public:
        MenuView(Drawing::Graphics* drawing, TTF_Font* font, SDL_Rect menuRect, SDL_Color normalColor, SDL_Color selectedColor, int lineHeight)
                : m_drawing(drawing)
                , m_font(font)
                , m_menuRect(menuRect)
                , m_normalColor(normalColor)
                , m_selectedColor(selectedColor)
                , m_lineHeight(lineHeight)
        {}

        void render(const MenuModel& model) {
            m_drawing->fillRectangleOutline({155, 155, 155, 50}, m_menuRect);

            int y = m_menuRect.y;
            for (size_t i = 0; i < model.getNumOptions(); i++) {
                SDL_Color color = (i == model.getSelectedIndex()) ? m_selectedColor : m_normalColor;

                int textWidth, textHeight;
                TTF_SizeText(m_font, model.getOption(i).c_str(), &textWidth, &textHeight);

                m_drawing->string(model.getOption(i), m_font, color,
                                  {static_cast<float>(m_menuRect.x + (m_menuRect.w/2)), static_cast<float>(y + (textHeight/2))},
                                  2);

                y += m_lineHeight;
            }
        }
    };

    class Menu {
    private:
        MenuModel m_model;
        MenuView m_view;
        Event::EventManager* g_event;

    public:
        Menu(Drawing::Graphics* drawing, Event::EventManager* event, TTF_Font* font, SDL_Rect menuRect, SDL_Color normalColor, SDL_Color selectedColor, int lineHeight)
                : m_model()
                , m_view(drawing, font, menuRect, normalColor, selectedColor, lineHeight)
                , g_event(event)
        {}

        void addOption(std::string option) {
            m_model.addOption(option);
        }

        void handleEvent() {
            if (!g_event)
                return;

            if (g_event->isKeyClicked(SDL_SCANCODE_UP, true)) {
                m_model.selectPreviousOption();
            }
            if (g_event->isKeyClicked(SDL_SCANCODE_DOWN, true)) {
                m_model.selectNextOption();
            }

            // TODO: Add addEvent()
            if (m_model.getSelectedOption() == "Exit" && g_event->isKeyClicked(SDL_SCANCODE_RIGHT, true)) {
                ExitProcess(1);
            }
        }

        void render() {
            m_view.render(m_model);
        }
    };

} // Menu

#endif //BOSCONIAN_MENU_H
