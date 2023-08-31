#ifndef BOSCONIAN_ENEMY_H
#define BOSCONIAN_ENEMY_H

#include "SDL.h"
#include "Entity.h"

class Enemy : public Entity {
private:
    int health;
    // Any other enemy-specific attributes...

public:
    Enemy(SDL_Texture* texture);

    virtual void Update() override;     // Update enemy's state.
    virtual void Render(SDL_Renderer* renderer) override;

    // Other enemy-specific functionalities...
};

#endif //BOSCONIAN_ENEMY_H
