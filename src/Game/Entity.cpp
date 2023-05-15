#include "Entity.h"
#include "../Utilities/GlobalVars.h"

namespace Game {
    Entity::Entity(Utils::Vector2D pos, float deg, Drawing::Image* img) {
        origin = pos;
        angle = deg;
        obj = img;

        hitbox = new Game::Hitbox(origin, obj->getSize());
    }

    void Entity::update() {
        obj->draw();
    }

    // TODO: Movement Manager
    bool Entity::move2Pos(Utils::Vector2D to, float speed) {
        LOG(std::string("Move to: ") + std::to_string(to.x) + std::string(" - ") + std::to_string(to.y));

        return 1;
    }

    void Entity::setOrigin(Utils::Vector2D newOrigin) {
        origin = newOrigin;
        // TODO: Should this happen during the update?
        //hitbox->updateHitboxPos(newOrigin);
        Utils::Vector2D newPosScreen;
        Utils::GlobalVars::WorldToScreen(newOrigin, newPosScreen);
        obj->setPos(newPosScreen);
    }

    Utils::Vector2D Entity::getOrigin() {
        return origin;
    }

    void Entity::setAngle(float newAngle) {
        obj->angle = angle;
        angle = newAngle;
        //hitbox->updateHitboxAngle(angle);
    }

    float Entity::getAngle() {
        return angle;
    }

    Game::Hitbox *Entity::getHitbox() {
        return hitbox;
    }


} // Game