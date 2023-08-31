#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "SDL.h"
#include "../../Utilities/Vector2D.h"

class Entity {
protected:
    SDL_Rect spriteClip;     // The clip of the sprite from the spritesheet.
    SDL_Texture* texture;    // Reference to the spritesheet or individual texture.

    Vector2D position;       // The current position and size of the entity.
    float velocity;
    float angle;      // The rotation angle of the entity

public:
    Entity(SDL_Texture* texture);
    virtual ~Entity();

    virtual void Update();       // Update the entity's state (like position).
    virtual void Render(SDL_Renderer* renderer);   // Render the entity on screen.

    void SetPosition(int x, int y);
    void SetSpriteClip(SDL_Rect clip);
    SDL_Rect GetPosition() const;

    // Other common functionalities...
};



#endif //BOSCONIAN_ENTITY_H
