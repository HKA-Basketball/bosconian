#ifndef BOSCONIAN_DIPSWITCH_H
#define BOSCONIAN_DIPSWITCH_H

#include "../Event/EventManager.h"
#include "../Drawing/Graphics.h"

/**
 * The Menu namespace encapsulates classes and functionality related to creating and displaying menus.
 */
namespace Menu {

    /**
     * The DipSwitchModel class handles the data and logic for a dip switch option.
     */
    class DipSwitchModel {
    public:
        /**
         * Constructs a DipSwitchModel instance.
         * \param label The label of the dip switch.
         * \param x The x-coordinate position of the dip switch.
         * \param y The y-coordinate position of the dip switch.
         * \param options A vector of boolean pointers representing dip switch options.
         */
        DipSwitchModel(std::string label, int x, int y, std::vector<bool*> options)
            : m_label(label)
            , m_selectedOption(0)
            , m_x(x)
            , m_y(y)
            , m_selectedOptions(options)
        { }

        /**
         * Toggles the selected dip switch option.
         */
        void toggleOption() {
            if (m_selectedOption >= 0 && m_selectedOption < m_selectedOptions.size()) {
                *(m_selectedOptions[m_selectedOption]) = !(*(m_selectedOptions[m_selectedOption]));
            }
        }

        /**
         * Checks if a specific dip switch option is selected.
         * \param option The index of the dip switch option.
         * \return True if the option is selected, false otherwise.
         */
        bool isOptionSelected(int option) const {
            if (option >= 0 && option < m_selectedOptions.size()) {
                return *(m_selectedOptions[option]);
            }
            return false;
        }

        /**
         * Sets the selected dip switch option by index.
         * \param newSelect The index of the option to be selected.
         */
        void setSelectOption(int newSelect) {
            if (newSelect < 0 || newSelect > m_selectedOptions.size() - 1) {
                return;
            }

            m_selectedOption = newSelect;
        }

        /**
         * Retrieves the index of the currently selected dip switch option.
         * \return The index of the selected option.
         */
        int getSelectedOption() const {
            return m_selectedOption;
        }

        /**
         * Selects the next dip switch option.
         */
        void selectNextOption() {
            if (m_selectedOption < m_selectedOptions.size() - 1) {
                m_selectedOption++;
            }
            else {
                m_selectedOption = 0;
            }
        }

        /**
         * Selects the previous dip switch option.
         */
        void selectPreviousOption() {
            if (m_selectedOption > 0) {
                m_selectedOption--;
            }
            else {
                m_selectedOption = m_selectedOptions.size() - 1;
            }
        }

        /**
         * Retrieves the total number of dip switch options.
         * \return The number of dip switch options.
         */
        size_t getNumOptions() const {
            return m_selectedOptions.size();
        }

        /**
         * Retrieves the label of the dip switch.
         * \return The label of the dip switch.
         */
        std::string getLabel() const {
            return m_label;
        }

        /**
         * Retrieves the x-coordinate position of the dip switch.
         * \return The x-coordinate position.
         */
        int getX() const {
            return m_x;
        }

        /**
         * Retrieves the y-coordinate position of the dip switch.
         * \return The y-coordinate position.
         */
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

    /**
     * The DipSwitchView class handles the rendering of a dip switch option.
     */
    class DipSwitchView {
    public:
        /**
         * Constructs a DipSwitchView instance.
         * \param drawing The Graphics instance used for rendering.
         * \param font The font used for rendering text.
         * \param model The associated DipSwitchModel instance.
         */
        DipSwitchView(Drawing::Graphics* drawing, TTF_Font* font, const DipSwitchModel model)
            : m_drawing(drawing)
            , m_font(font)
            , m_model(model)
        {}

        /**
         * Renders the dip switch option based on the provided model.
         * \param model The DipSwitchModel instance containing dip switch data.
         */
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

        /**
         * Retrieves the SDL_FRect representing the dimensions of a dip switch option.
         * \param i The index of the dip switch option.
         * \return The SDL_FRect representing the option's dimensions.
         */
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

    /**
     * The DipSwitch class manages the data and rendering of a dip switch option.
     */
    class DipSwitch {
    private:
        DipSwitchModel m_model;
        DipSwitchView m_view;
        Event::EventManager* g_event;

    public:
        /**
         * Constructs a DipSwitch instance.
         * \param font The font used for rendering text.
         * \param label The label of the dip switch.
         * \param x The x-coordinate position of the dip switch.
         * \param y The y-coordinate position of the dip switch.
         * \param options A vector of boolean pointers representing dip switch options.
         */
        DipSwitch(TTF_Font* font, std::string label, int x, int y, std::vector<bool*> options)
            : m_model(label, x, y, options)
            , m_view(Drawing::g_drawing, font, m_model)
            , g_event(Event::g_event)
        {}

        /**
         * Handles events related to the dip switch.
         */
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

        /**
         * Retrieves the state of a specific dip switch option.
         * \param i The index of the dip switch option.
         * \return True if the option is selected, false otherwise.
         */
        bool optionState(int i) {
            return m_model.isOptionSelected(i);
        }

        /**
         * Renders the dip switch option.
         */
        void render() {
            m_view.render(m_model);
        }
    };

} // Menu

#endif //BOSCONIAN_DIPSWITCH_H
