#ifndef BOSCONIAN_TEXTANIMATION_H
#define BOSCONIAN_TEXTANIMATION_H

#include "Animation.h"

#include <string>
#include <iostream>
#include <utility>

/**
 * @class TextAnimation
 * @brief Derived class representing a timed text-based animation.
 *
 * This class extends the base Animation class to handle animations
 * based on displaying text for a specific duration.
 */
class TextAnimation : public Animation {
private:
    std::string text;       ///< Text to be displayed in the animation.
    float elapsedTime{0.f}; ///< Time passed since the start of the animation.
    float length{6.f};      ///< Duration the text should be shown (in seconds).

public:
    /**
     * @brief Constructor that initializes the text animation with given text.
     *
     * @param text The text string to be displayed during the animation.
     */
    explicit TextAnimation(std::string text);

    /**
     * @brief Start the text animation.
     *
     * Resets the elapsed time to zero and starts the animation.
     */
    void start() override;

    /**
     * @brief Update the animation based on the elapsed time.
     *
     * Stops the animation once the elapsed time surpasses the defined length.
     *
     * @param deltaTime Time elapsed since the last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Get the text associated with this animation.
     *
     * @return The text string of the animation.
     */
    std::string getText() const;

};

#endif //BOSCONIAN_TEXTANIMATION_H
