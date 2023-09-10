// ... other includes

#include "Base.h"

Base::Base(SDL_Texture* texture, float x, float y) : Entity(texture), coreIntact(true) {}

bool Base::IsDestroyed() const {
    /*return std::all_of(cannons.begin(), cannons.end(), [](const Cannon& cannon) {
        return cannon.GetState() == CannonState::DESTROYED;
    }) || !coreIntact;*/
    return 0;
}

void Base::TakeDamage(int cannonIndex) {
    if (cannons[cannonIndex].GetState() == CannonState::ACTIVE) {
        cannons[cannonIndex].Destroy();
    } else {
        coreIntact = false;
    }
}

std::vector<Projectile> Base::FireProjectiles() {
    return {};
}

// ... rest of the methods remain unchanged
