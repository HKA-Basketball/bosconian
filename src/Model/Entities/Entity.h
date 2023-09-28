#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "../../Utilities/Position.h"
#include "../../Physics/Hitbox.h"
#include "../../Graphic/SpriteInfo.h"
#include "../World.h"

class Entity {
protected:
    Position position{0, 0};
    Degree angle{0};
    float speed{0.f};

    bool dead{false};

    SpriteInfo spriteInfo = SpriteInfo::PLAYER;
    Hitbox hitbox{{0, 0}, {50, 50}};

public:
    explicit Entity(const Vector2D& position, const Degree angle) : position(position), angle(angle) {
        /* TODO Hitbox in Sprite size */
        //hitbox = {position, {static_cast<float>(spriteMap.at(spriteInfo).w), static_cast<float>(spriteMap.at(spriteInfo).h)}};
    }

    virtual void update(float deltaTime) {
        float radians = angle.toRadians() - M_PI_2;
        Vector2D newPosition = position.getCenterPosition();
        newPosition.x += speed * deltaTime * std::cos(radians);
        newPosition.y += speed * deltaTime * std::sin(radians);
        newPosition = World::WrapPosition(newPosition);
        position.setCenterPosition(newPosition);

        hitbox.updatePosition(position.getCenterPosition());
        hitbox.updateAngle(angle);
    }

    Vector2D getPosition() const { return position.getCenterPosition(); }
    void setPosition(const Vector2D& newPosition) { position.setCenterPosition(newPosition); }
    WrappedPositions getWrappedPositions() const { return position.getWrappedPositions(); }

    Degree getAngle() const { return angle; }
    void setAngle(const Degree newAngle) { angle = newAngle; }

    Hitbox getHitbox() const { return hitbox; }
    void setHitbox(const Hitbox& newHitbox) { hitbox = newHitbox; }

    SpriteInfo getSpriteInfo() const { return spriteInfo; }
    void setSpriteInfo(const SpriteInfo& newSpriteInfo) { spriteInfo = newSpriteInfo; }
};

#endif //BOSCONIAN_ENTITY_H
