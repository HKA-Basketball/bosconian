#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "../../Utilities/Position.h"
#include "../../Physics/Hitbox.h"
#include "../../Graphic/SpriteInfo.h"
#include "../Animations/SpriteAnimation.h"
#include "../World.h"

class Entity {
protected:
    unsigned int points{0};
    bool receivedPoints{false};

    Position position{0, 0};
    Degree angle{0};
    float speed{0.f};

    bool defeated{false};
    bool dead{false};

    SpriteInfo spriteInfo = SpriteInfo::PLAYER;
    Hitbox hitbox{{0, 0}, {50, 50}};
    SpriteAnimation explosion = {{SpriteInfo::EXPLOSION_01, SpriteInfo::EXPLOSION_02, SpriteInfo::EXPLOSION_03}};

public:
    explicit Entity(const Vector2D& position, const Degree angle) : position(position), angle(angle) {
        hitbox = {position, {static_cast<float>(spriteMap.at(spriteInfo).w), static_cast<float>(spriteMap.at(spriteInfo).h)}};
    }

    virtual void update(float deltaTime) {
        if(defeated) {
            angle = 0.f;
            explosion.update(deltaTime);
            spriteInfo = explosion.getCurrentSprite();
            dead = explosion.isDone();
        }

        float radians = angle.toRadians() - M_PI_2;
        Vector2D newPosition = position.getCenterPosition();
        newPosition.x += speed * deltaTime * std::cos(radians);
        newPosition.y += speed * deltaTime * std::sin(radians);
        newPosition = World::wrapPosition(newPosition);
        position.setCenterPosition(newPosition);

        Vector2D hitboxPosition = position.getCenterPosition();
        Vector2D hitboxSize = hitbox.getSize();
        hitboxPosition.x -= hitboxSize.x / 2.f;
        hitboxPosition.y -= hitboxSize.y / 2.f;
        hitbox.updatePosition(hitboxPosition);
        hitbox.updateAngle(angle);
    }

    void setDefeated() {
        defeated = true;
        speed = 0.f;
        explosion.start();
    }

    bool isDefeated() const {
        return defeated;
    }

    bool isDead() const {
        return dead;
    }

    Vector2D getPosition() const { return position.getCenterPosition(); }
    Position getPositions() const { return position.getCenterPosition(); }
    void setPosition(const Vector2D& newPosition) { position.setCenterPosition(newPosition); }
    WrappedPositions getWrappedPositions() const { return position.getWrappedPositions(); }

    Degree getAngle() const { return angle; }
    void setAngle(const Degree newAngle) { angle = newAngle; }

    void setSpeed(const float newSpeed) { speed = newSpeed; }

    Hitbox getHitbox() const { return hitbox; }
    void setHitbox(const Hitbox& newHitbox) { hitbox = newHitbox; }

    SpriteInfo getSpriteInfo() const { return spriteInfo; }
    void setSpriteInfo(const SpriteInfo& newSpriteInfo) { spriteInfo = newSpriteInfo; }

    virtual unsigned int receivePoints() {
        if(receivedPoints) {
            return 0;
        }

        receivedPoints = true;
        return points;
    }
};

#endif //BOSCONIAN_ENTITY_H
