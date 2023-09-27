#ifndef BOSCONIAN_BASE_H
#define BOSCONIAN_BASE_H

#include "Entity.h"
#include "Cannon.h"

struct CannonInfo {
    Vector2D positionOffset;
    Degree angleOffset;
    SpriteInfo spriteInfo;
};

class Base : public Entity {
private:
    std::vector<Cannon*>* cannons = new std::vector<Cannon*>();

    const std::vector<CannonInfo> cannonInfos = {
        {{-112, 0}, {-90.f}, SpriteInfo::CANON_L_NORM},
        {{-62, -80}, {0.f}, SpriteInfo::CANON_L_UP_NORM},
        {{-62, 80}, {-180.f}, SpriteInfo::CANON_L_DOWN_NORM},
        {{112, 0}, {90.f}, SpriteInfo::CANON_R_NORM},
        {{62, -80}, {0.f}, SpriteInfo::CANON_R_UP_NORM},
        {{62, 80}, {180.f}, SpriteInfo::CANON_R_DOWN_NORM},
    };

public:
    explicit Base(const Vector2D& position, const Degree angle) : Entity(position, angle) {
        spriteInfo = SpriteInfo::KERN;
        hitbox = {{0, 0}, {25, 25}};

        for (int i = 0; i < 6; ++i) {
            Vector2D cannonPos = position + cannonInfos[i].positionOffset.rotate(angle.toRadians());
            float radians = angle.toRadians() - M_PI_2;
            cannonPos.x += std::cos(radians);
            cannonPos.y += std::sin(radians);
            Degree cannonAngle = angle + cannonInfos[i].angleOffset;
            cannons->push_back(new Cannon(cannonPos, cannonAngle, cannonInfos[i].spriteInfo));
        }

    }

    void updatePlayerPosition(const Vector2D& newPlayerPosition) {
        for (Cannon* cannon : *cannons) {
            cannon->updatePlayerPosition(newPlayerPosition);
        }
    }

    void update(float deltaTime) override {
        Entity::update(deltaTime);
    }

    std::vector<Cannon*>* getCannons() const {
        return cannons;
    }
};

#endif //BOSCONIAN_BASE_H
