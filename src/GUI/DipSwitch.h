#ifndef BOSCONIAN_DIPSWITCH_H
#define BOSCONIAN_DIPSWITCH_H

#include "../Event/EventManager.h"
#include "../Drawing/Graphics.h"

namespace Menu {

    class DipSwitchModel {
    public:
        DipSwitchModel(std::string label, int x, int y, std::vector<bool*> options)
            : m_label(label)
            , m_selectedOption(0)
            , m_x(x)
            , m_y(y)
            , m_selectedOptions(options)
        { }

        void toggleOption() {
            if (m_selectedOption >= 0 && m_selectedOption < m_selectedOptions.size()) {
                *(m_selectedOptions[m_selectedOption]) = !(*(m_selectedOptions[m_selectedOption]));
            }
        }

        bool isOptionSelected(int option) const {
            if (option >= 0 && option < m_selectedOptions.size()) {
                return *(m_selectedOptions[option]);
            }
            return false;
        }

        void setSelectOption(int newSelect) {
            if (newSelect < 0 || newSelect > m_selectedOptions.size() - 1) {
                return;
            }

            m_selectedOption = newSelect;
        }

        int getSelectedOption() const {
            return m_selectedOption;
        }

        void selectNextOption() {
            if (m_selectedOption < m_selectedOptions.size() - 1) {
                m_selectedOption++;
            }
            else {
                m_selectedOption = 0;
            }
        }

        void selectPreviousOption() {
            if (m_selectedOption > 0) {
                m_selectedOption--;
            }
            else {
                m_selectedOption = m_selectedOptions.size() - 1;
            }
        }

        size_t getNumOptions() const {
            return m_selectedOptions.size();
        }

        std::string getLabel() const {
            return m_label;
        }

        int getX() const {
            return m_x;
        }

        int getY() const {
            return m_y;
        }

    private:
        std::string m_label;
        std::vector<bool*> m_selectedOptions;
        unsigned int m_selectedOption;
        int m_x;
        int m_y;
    };

    class DipSwitchView {
    public:
        DipSwitchView(Drawing::Graphics* drawing, TTF_Font* font, const DipSwitchModel model)
            : m_drawing(drawing)
            , m_font(font)
            , m_model(model)
        {}

        void render(const DipSwitchModel& model)
        {
            int optionWidth = 40;
            int optionHeight = 20;

            int recWidth = m_model.getNumOptions() * optionWidth;
            SDL_Rect rect = { m_model.getX() - (recWidth/2), m_model.getY() - 10, recWidth, optionHeight + 20 };

            int textWidth, textHeight;
            TTF_SizeText(m_font, m_model.getLabel().c_str(), &textWidth, &textHeight);
            m_drawing->string(m_model.getLabel(), m_font, {255, 255, 255, 255},
                              {static_cast<float>(m_model.getX()), static_cast<float>(rect.y - (textHeight/2))},
                              2);

            m_drawing->fillRectangleOutline({48, 48, 48, 255}, rect);

            // Render the options
            for (int i = 0; i < m_model.getNumOptions(); i++) {
                SDL_Rect optionRect = { m_model.getX() - (recWidth/2)  + (i * optionWidth), m_model.getY(), optionWidth, optionHeight };

                /*if (i == m_model.getSelectedOption()) {
                    optionRect.y -= 10;
                    optionRect.h += 20;
                    m_drawing->fillRectangleOutline({170, 170, 170, 100}, optionRect);
                    optionRect.y += 10;
                    optionRect.h -= 20;
                }*/

                // Set the color based on the selected state
                if (model.isOptionSelected(i)) {
                    optionRect.y -= 10;
                    m_drawing->fillRectangleOutline({0, 255, 0, 255}, optionRect);
                } else {
                    optionRect.y += 10;
                    m_drawing->fillRectangleOutline({255, 0, 0, 255}, optionRect);
                }
            }
        }

        SDL_FRect optionRect(int i) {
            int optionWidth = 40;
            int optionHeight = 20;

            int recWidth = m_model.getNumOptions() * optionWidth;
            SDL_FRect optionRect = { static_cast<float>(m_model.getX() - (recWidth/2) + (i * optionWidth)), static_cast<float>(m_model.getY() - 10), static_cast<float>(optionWidth), static_cast<float>(optionHeight + 20) };

            return optionRect;
        }

    private:
        Drawing::Graphics* m_drawing;
        TTF_Font* m_font;
        const DipSwitchModel m_model;
    };

    class DipSwitch {
    private:
        DipSwitchModel m_model;
        DipSwitchView m_view;
        Event::EventManager* g_event;

    public:
        DipSwitch(TTF_Font* font, std::string label, int x, int y, std::vector<bool*> options)
            : m_model(label, x, y, options)
            , m_view(Drawing::g_drawing, font, m_model)
            , g_event(Event::g_event)
        {}

        void handleEvent()
        {
            if (!g_event)
                return;

            for (size_t i = 0; i < m_model.getNumOptions(); i++) {
                SDL_FRect inRect = m_view.optionRect(i);
                bool isIn = false;
                if (Utils::render::isCursorInRect({inRect.x, inRect.y}, {inRect.w, inRect.h})) {
                    m_model.setSelectOption(i);
                    isIn = true;
                }
                if (isIn && g_event->isMouseClicked(1, true)) {
                    m_model.toggleOption();
                }
            }

            /*if (g_event->isKeyClicked(SDL_SCANCODE_UP, true)) {
                m_model.toggleOption();
            }
            if (g_event->isKeyClicked(SDL_SCANCODE_DOWN, true)) {
                m_model.toggleOption();
            }

            if (g_event->isKeyClicked(SDL_SCANCODE_LEFT, true)) {
                m_model.selectPreviousOption();
            }
            if (g_event->isKeyClicked(SDL_SCANCODE_RIGHT, true)) {
                m_model.selectNextOption();
            }*/
        }

        bool optionState(int i) {
            return m_model.isOptionSelected(i);
        }

        void render() {
            m_view.render(m_model);
        }
    };

} // Menu

#endif //BOSCONIAN_DIPSWITCH_H
