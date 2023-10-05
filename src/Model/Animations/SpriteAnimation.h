#ifndef BOSCONIAN_SPRITEANIMATION_H
#define BOSCONIAN_SPRITEANIMATION_H

#include <vector>
#include "Animation.h"
#include "../../Graphic/SpriteInfo.h"

/**
 * @class SpriteAnimation
 * @brief Derived class representing a sprite-based animation.
 *
 * This class extends the base Animation class to handle animations
 * composed of multiple sprite frames. It manages the progression
 * of frames over time to display the animation.
 */
class SpriteAnimation : public Animation {
private:
    std::vector<SpriteInfo> sprites;          ///< List of sprites (frames) for the animation.
    float animationSpeed{0.1f};               ///< Time (in seconds) each sprite is shown for.
    float elapsedTimeSinceLastFrame{0.0f};    ///< Time passed since the start of the animation or the last frame change.
    size_t currentFrame{0};                   ///< The index of the current sprite being shown.


public:
    /**
     * @brief Constructor that initializes the sprite animation with a list of sprites.
     *
     * @param sprites List of SpriteInfo objects representing the frames of the animation.
     */
    SpriteAnimation(const std::vector<SpriteInfo>& sprites);

    /**
     * @brief Start the sprite animation.
     *
     * Resets the current frame to the beginning and starts the animation.
     */
    void start() override;

    /**
     * @brief Update the animation based on the elapsed time.
     *
     * Progresses the animation frames based on the elapsed time. When the animation
     * reaches its end, it stops playing.
     *
     * @param deltaTime Time elapsed since the last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Get the current sprite frame of the animation.
     *
     * Returns the sprite frame corresponding to the current animation frame.
     * If the animation is past its last frame, returns the last sprite in the sequence.
     *
     * @return SpriteInfo object representing the current sprite frame.
     */
    SpriteInfo getCurrentSprite();
};

#endif //BOSCONIAN_SPRITEANIMATION_H
