#ifndef BOSCONIAN_ENEMY_H
#define BOSCONIAN_ENEMY_H

#include "SDL.h"
#include "Entity.h"

class Enemy : public Entity {
private:
    // Any other enemy-specific attributes...

public:
    Enemy(SDL_Texture* texture);

    // Other enemy-specific functionalities...
};

#endif //BOSCONIAN_ENEMY_H
