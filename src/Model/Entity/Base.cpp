// ... other includes

#include "Base.h"

Base::Base(float x, float y) : Entity(x, y), coreIntact(true) {}

bool Base::IsDestroyed() const {
    return std::all_of(cannons.begin(), cannons.end(), [](const Cannon& cannon) {
        return cannon.GetState() == CannonState::DESTROYED;
    }) || !coreIntact;
}

void Base::TakeDamage(int cannonIndex) {
    if (cannons[cannonIndex].GetState() == CannonState::ACTIVE) {
        cannons[cannonIndex].Destroy();
    } else {
        coreIntact = false;
    }
}

// ... rest of the methods remain unchanged
