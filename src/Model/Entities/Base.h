#ifndef BOSCONIAN_BASE_H
#define BOSCONIAN_BASE_H

#include "Entity.h"
#include "Cannon.h"

struct CannonInfo {
    Vector2D positionOffset;
    Degree angleOffset;
    SpriteInfo spriteInfo;
    SpriteInfo explosionSpriteInfo;
};

class Base : public Entity {
private:
    std::vector<Cannon*>* cannons = new std::vector<Cannon*>();

    const std::vector<CannonInfo> cannonInfos = {
        {{-112, 0}, {180.f}, SpriteInfo::CANON_L_NORM, SpriteInfo::CANON_L},
        {{-62, -80}, {255.f}, SpriteInfo::CANON_L_UP_NORM, SpriteInfo::CANON_L_UP},
        {{-62, 80}, {105.f}, SpriteInfo::CANON_L_DOWN_NORM, SpriteInfo::CANON_L_DOWN},
        {{112, 0}, {0.f}, SpriteInfo::CANON_R_NORM, SpriteInfo::CANON_R},
        {{62, -80}, {285.f}, SpriteInfo::CANON_R_UP_NORM, SpriteInfo::CANON_R_UP},
        {{62, 80}, {75.f}, SpriteInfo::CANON_R_DOWN_NORM, SpriteInfo::CANON_R_DOWN},
    };

public:
    explicit Base(const Vector2D& position, const Degree angle, Position* playerPositions) : Entity(position, angle) {
        spriteInfo = SpriteInfo::KERN;
        hitbox = {{0, 0}, {30, 45}};

        for (const auto& cannonInfo : cannonInfos) {
            Vector2D cannonPos = position + cannonInfo.positionOffset.rotate(angle.toRadians());
            float radians = angle.toRadians() - M_PI_2;
            cannonPos.x += std::cos(radians);
            cannonPos.y += std::sin(radians);
            Degree cannonAngle = angle + cannonInfo.angleOffset;
            cannons->emplace_back(new Cannon(cannonPos, cannonAngle, playerPositions, cannonInfo.spriteInfo, cannonInfo.explosionSpriteInfo));
        }

    }

    void update(float deltaTime) override {
        Entity::update(deltaTime);

        bool allCannonsDefeated = true;
        for (Cannon* cannon : *cannons) {
            cannon->update(deltaTime);

            if(!cannon->isDefeated()) {
                allCannonsDefeated = false;
            }

        }

        if(allCannonsDefeated && !defeated) {
            this->setDefeated();
        }
    }

    std::vector<Cannon*>* getCannons() const {
        return cannons;
    }
};

#endif //BOSCONIAN_BASE_H
