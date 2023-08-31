#ifndef BOSCONIAN_BASE_H
#define BOSCONIAN_BASE_H

// ... other includes
#include <vector>

#include "Entity.h"
#include "Cannon.h"
#include "Projectile.h"

class Base : public Entity {
public:
    Base(float x, float y);
    ~Base() override = default;

    bool IsDestroyed() const;
    void TakeDamage(int cannonIndex);  // You target a specific cannon by index

    void Update();
    std::vector<Projectile> FireProjectiles();

private:
    static constexpr int totalCannons = 6;
    bool coreIntact;

    std::array<Cannon, totalCannons> cannons;
};


#endif //BOSCONIAN_BASE_H
