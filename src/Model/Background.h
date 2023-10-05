#ifndef BOSCONIAN_BACKGROUND_H
#define BOSCONIAN_BACKGROUND_H

#include <vector>
#include <SDL.h>

#include "Camera.h"
#include "../Utilities/Math.h"
#include "../Utilities/Random.h"
#include "../Utilities/Config.h"

/**
 * @class Star
 * @brief Represents a star that will be displayed as part of the game's background.
 *
 * The star has properties related to its position, size, and color.
 */
class Star {
public:
    SDL_FRect rect;  //!< Star's position and size.
    SDL_Color color; //!< Star's color.

    /**
     * @brief Constructor that initializes a star with random properties.
     */
    Star();

    /**
     * @brief Randomizes the star's position.
     */
    void randomizePosition();

    /**
     * @brief Randomizes the star's size.
     */
    void randomizeSize();

    /**
     * @brief Randomizes the star's color.
     */
    void randomizeColor();
};

/**
 * @class Background
 * @brief Represents the game's background, including all the stars.
 *
 * The background consists of a set number of stars, with the ability to update their properties periodically.
 */
class Background {
private:
    std::vector<Star> stars;               //!< Collection of stars forming the background.
    const int numStars = 256;              //!< Number of stars in the background.
    Uint64 elapsedTime = 0;                //!< Time elapsed since the last randomization.
    const Uint64 randomizeDelay = 750;     //!< Delay in milliseconds to trigger star randomization.
    bool starHalfToggle = false;           //!< Toggle to determine which half of the stars to randomize.

public:
    /**
     * @brief Default constructor that initializes the background with a set number of stars.
     */
    Background();

    /**
     * @brief Updates the background state.
     * @param deltaTime Time elapsed since the last frame (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Fetches the collection of stars forming the background.
     * @return Vector of stars.
     */
    std::vector<Star> getStars() const;
};

#endif //BOSCONIAN_BACKGROUND_H