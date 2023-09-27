#ifndef BOSCONIAN_SPRITE_H
#define BOSCONIAN_SPRITE_H

#include "SDL.h"

#include "SpriteInfo.h"
#include "../Utilities/Vector2D.h"

class Sprite {
private:
    SDL_Rect srcRect;
    SDL_FRect destRect;

public:
    explicit Sprite(SpriteInfo spriteInfo) {
        srcRect = spriteMap.at(spriteInfo);
        destRect.x = static_cast<float>(srcRect.x);
        destRect.y = static_cast<float>(srcRect.y);
        destRect.w = static_cast<float>(srcRect.w);
        destRect.h = static_cast<float>(srcRect.h);
    }

    Sprite(SpriteInfo spriteInfo, const Vector2D& position) : Sprite(spriteInfo) {
        setPosition(position);
    }

    Sprite(SpriteInfo spriteInfo, const Vector2D& position, const Vector2D& size) : Sprite(spriteInfo, position) {
        setSize(size);
    }

    void setPosition(const Vector2D& newPosition) {
        destRect.x = newPosition.x;
        destRect.y = newPosition.y;
    }

    void setSize(const Vector2D& newSize) {
        destRect.w = newSize.x;
        destRect.h = newSize.y;
    }

    SDL_Rect getSourceRectangle() {
        return srcRect;
    }

    SDL_FRect getDestinationRectangle(bool centered = false) {
        SDL_FRect updatedDestRect = destRect;
        if(centered) {
            updatedDestRect.x = destRect.x - (destRect.w / 2);
            updatedDestRect.y = destRect.y - (destRect.h / 2);
        }
        return updatedDestRect;
    }
};


#endif //BOSCONIAN_SPRITE_H
