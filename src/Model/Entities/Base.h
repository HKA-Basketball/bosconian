#ifndef BOSCONIAN_BASE_H
#define BOSCONIAN_BASE_H

#include "Entity.h"
#include "Cannon.h"
#include "Spy.h"

struct CannonInfo {
    Vector2D positionOffset;
    Degree angleOffset;
    SpriteInfo spriteInfo;
    SpriteInfo explosionSpriteInfo;
};

class Base : public Entity {
private:
    std::vector<Cannon*>* cannons = new std::vector<Cannon*>();
    Spy* spy;

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
        points = 1500;

        spy = new Spy(position, angle, playerPositions);

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

        if (spy->isLoaded()) {
            spy->update(deltaTime);

        }

        if (spy->isDead() || !spy->isLoaded()) {
            spy->reset();
        }

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

    Spy* getSpy() const {
        return spy;
    }

    Vector2D getTotalSize() const {
        // Initialize the bounds with very large and very small values
        float leftmost = std::numeric_limits<float>::max();
        float rightmost = std::numeric_limits<float>::min();
        float highest = std::numeric_limits<float>::max();
        float lowest = std::numeric_limits<float>::min();

        for (const Cannon* cannon : *cannons) {
            Vector2D cannonSize = cannon->getHitbox().getSize();
            float halfWidth = cannonSize.x / 2.0f;
            float halfHeight = cannonSize.y / 2.0f;

            if (cannon->getPosition().x - halfWidth < leftmost) {
                leftmost = cannon->getPosition().x - halfWidth;
            }

            if (cannon->getPosition().x + halfWidth > rightmost) {
                rightmost = cannon->getPosition().x + halfWidth;
            }

            if (cannon->getPosition().y - halfHeight < highest) {
                highest = cannon->getPosition().y - halfHeight;
            }

            if (cannon->getPosition().y + halfHeight > lowest) {
                lowest = cannon->getPosition().y + halfHeight;
            }
        }

        Vector2D totalSize;
        totalSize.x = rightmost - leftmost;
        totalSize.y = lowest - highest;

        return totalSize;
    }

};

#endif //BOSCONIAN_BASE_H
