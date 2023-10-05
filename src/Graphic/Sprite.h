#ifndef BOSCONIAN_SPRITE_H
#define BOSCONIAN_SPRITE_H

#include "SDL.h"

#include "SpriteInfo.h"
#include "../Utilities/Vector2D.h"

/**
 * @class Sprite
 * @brief Represents a graphical sprite with source and destination rectangles.
 *
 * The Sprite class encapsulates the information and behavior of a graphical sprite element.
 * This includes its source rectangle (on the spritesheet) and its destination rectangle (on the screen).
 */
class Sprite {
private:
    SDL_Rect srcRect;     //!< Source rectangle on the spritesheet.
    SDL_FRect destRect;   //!< Destination rectangle on the screen.

public:
    /**
     * @brief Construct a Sprite from a SpriteInfo.
     * @param spriteInfo The information about the sprite.
     */
    explicit Sprite(SpriteInfo spriteInfo);

    /**
     * @brief Construct a Sprite from a SpriteInfo and position.
     * @param spriteInfo The information about the sprite.
     * @param position The position of the sprite.
     */
    Sprite(SpriteInfo spriteInfo, const Vector2D& position);

    /**
     * @brief Construct a Sprite from a SpriteInfo, position, and size.
     * @param spriteInfo The information about the sprite.
     * @param position The position of the sprite.
     * @param size The size of the sprite.
     */
    Sprite(SpriteInfo spriteInfo, const Vector2D& position, const Vector2D& size);

    /**
     * @brief Set the position of the sprite.
     * @param newPosition The new position.
     */
    void setPosition(const Vector2D& newPosition);

    /**
     * @brief Set the size of the sprite.
     * @param newSize The new size.
     */
    void setSize(const Vector2D& newSize);

    /**
     * @brief Get the source rectangle of the sprite.
     * @return The source rectangle.
     */
    SDL_Rect getSourceRectangle();

    /**
     * @brief Get the destination rectangle of the sprite.
     * @param centered Whether or not the destination should be centered.
     * @return The destination rectangle.
     */
    SDL_FRect getDestinationRectangle(bool centered = false);
};


#endif //BOSCONIAN_SPRITE_H
