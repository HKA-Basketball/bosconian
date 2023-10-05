#ifndef BOSCONIAN_FRAMETIMER_H
#define BOSCONIAN_FRAMETIMER_H

#include <SDL.h>

/**
 * @brief A utility class for frame timing and delay.
 *
 * FrameTimer is responsible for keeping track of frame duration,
 * calculating delta time, and ensuring a constant frame rate by
 * adding necessary delay.
 */
class FrameTimer {
private:
    float delayTime;       //!< Time to delay to maintain desired FPS.
    Uint64 lastFrameTime;  //!< Timestamp of when the last frame started.
    float deltaTime;       //!< Time elapsed since the last frame started.

public:
    /**
     * @brief Default constructor initializing the timer for 60 FPS.
     */
    FrameTimer();

    /**
     * @brief Construct a new FrameTimer object.
     *
     * @param fps Desired frames per second.
     */
    explicit FrameTimer(Uint16 fps);

    /**
     * @brief Starts the frame timer, calculating delta time for the current frame.
     */
    void startFrame();

    /**
     * @brief Get the time elapsed since the last frame started.
     *
     * @return float Delta time in seconds.
     */
    float getDeltaTime() const;

    /**
     * @brief Add delay to maintain a steady frame rate.
     */
    void delayFrame() const;
};

#endif //BOSCONIAN_FRAMETIMER_H
