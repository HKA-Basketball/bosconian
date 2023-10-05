#ifndef BOSCONIAN_ANIMATION_H
#define BOSCONIAN_ANIMATION_H

/**
 * @class Animation
 * @brief Abstract class representing a basic animation.
 *
 * This class provides a basic structure for animations, offering mechanisms
 * to start the animation, update its state, and check if it's completed.
 */
class Animation {
protected:
    bool isPlaying{false}; ///< Flag indicating whether the animation is currently playing.

public:
    /**
     * @brief Default constructor.
     */
    Animation() = default;

    /**
     * @brief Start the animation.
     *
     * Sets the `isPlaying` flag to true, indicating the animation has started.
     */
    virtual void start() {
        isPlaying = true;
    }

    /**
     * @brief Abstract method to update the animation state.
     *
     * Derived classes must provide an implementation for this method to define
     * the behavior of the animation during each update cycle.
     *
     * @param deltaTime Time elapsed since the last update.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Check if the animation has completed.
     *
     * @return Returns `true` if the animation is not playing, `false` otherwise.
     */
    virtual bool isDone() const {
        return !isPlaying;
    }
};

#endif //BOSCONIAN_ANIMATION_H
