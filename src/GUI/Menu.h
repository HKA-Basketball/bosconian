#ifndef BOSCONIAN_MENU_H
#define BOSCONIAN_MENU_H

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"
#include "../Event/EventManager.h"
#include "../Drawing/Graphics.h"

namespace Menu {

    struct MenuOption {
        std::string option;
        std::function<void()> callback;

        MenuOption(const std::string& option, std::function<void()> callback)
                : option(option), callback(callback)
        {}
    };


    class MenuModel {
    private:
        std::vector<MenuOption> m_options;
        int m_selectedIndex;

    public:
        MenuModel() : m_selectedIndex(0) {}

        void addOption(std::string option, std::function<void()> callback) {
            m_options.emplace_back(option, callback);
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

        void setSelectOption(int newSelect) {
            if (newSelect < 0 || newSelect > m_options.size() - 1) {
                return;
            }

            m_selectedIndex = newSelect;
        }

        int getSelectedIndex() const {
            return m_selectedIndex;
        }

        const std::string& getSelectedOption() const {
            return m_options[m_selectedIndex].option;
        }

        size_t getNumOptions() const {
            return m_options.size();
        }

        const std::string& getOption(size_t index) const {
            return m_options[index].option;
        }

        void callbackSelectedOption() const {
             m_options[m_selectedIndex].callback();
        }

        void callbackOption(size_t index) const {
            m_options[index].callback();
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
        int m_textHeight;

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

        int getTextHeight() const {
            return m_textHeight;
        }

        const SDL_Rect &getMenuRect() const {
            return m_menuRect;
        }

        int getLineHeight() const {
            return m_lineHeight;
        }
    };

    class Menu {
    private:
        MenuModel m_model;
        MenuView m_view;
        Event::EventManager* g_event;

    public:
        Menu(TTF_Font* font, SDL_Rect menuRect, SDL_Color normalColor, SDL_Color selectedColor, int lineHeight)
                : m_model()
                , m_view(Drawing::g_drawing, font, menuRect, normalColor, selectedColor, lineHeight)
                , g_event(Event::g_event)
        {}

        void addOption(std::string option, std::function<void()> callback) {
            m_model.addOption(option, callback);
        }

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

        void render() {
            m_view.render(m_model);
        }
    };

} // Menu

#endif //BOSCONIAN_MENU_H
