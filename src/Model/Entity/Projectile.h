#ifndef BOSCONIAN_PROJECTILE_H
#define BOSCONIAN_PROJECTILE_H

#include <vector>
#include "SDL.h"
#include "Entity.h"


class Projectile : public Entity {
private:
    // Any other enemy-specific attributes...

public:
    explicit Projectile(SDL_Texture* texture);

    // Other enemy-specific functionalities...

};

typedef std::vector<Projectile*> Projectiles;


#endif //BOSCONIAN_PROJECTILE_H
