#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "SDL.h"
#include "../../Utilities/Vec2.h"
#include "../../Utilities/Degree.h"

class Entity {
protected:
    SDL_Rect spriteClip;     // The clip of the sprite from the spritesheet.
    SDL_Texture* texture;    // Reference to the spritesheet or individual texture.

    Vec2 position;       // The current position and size of the entity.
    float speed;
    Degree angle;      // The rotation angle of the entity

public:
    explicit Entity(SDL_Texture* texture);
    virtual ~Entity();

    virtual void Update(float deltaTime);       // Update the entity's state (like position).

    SDL_Rect getSpriteClip() const;
    void setSpriteClip(SDL_Rect clip);

    void setPosition(const Vec2& newPosition);
    Vec2 getPosition() const;
    void setSpeed(float newSpeed);
    float getSpeed() const;
    void setAngle(float newAngle);
    void setAngle(Degree newAngle);
    Degree getAngle() const;

    // Other common functionalities...
};



#endif //BOSCONIAN_ENTITY_H
