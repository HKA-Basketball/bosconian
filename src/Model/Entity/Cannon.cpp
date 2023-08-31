#include "Cannon.h"

Cannon::Cannon() : state(CannonState::ACTIVE) {}

CannonState Cannon::GetState() const {
    return state;
}

void Cannon::Destroy() {
    state = CannonState::DESTROYED;
}
