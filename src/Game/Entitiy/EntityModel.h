#ifndef BOSCONIAN_ENTITYMODEL_H
#define BOSCONIAN_ENTITYMODEL_H

#include <memory>

#include "EntityType.h"
#include "../Projectile.h"
#include "../../Physics/Collision.h"
#include "../../Physics/Hitbox.h"
#include "../../../includes.h"

namespace Game {

    class EntityModel {
    private:
        Utils::Vector2D origin;
        Utils::Vector2D size;
        float angle{0.0f};

        std::unique_ptr<Physics::Hitbox> hitbox;
        EntityType type;
        Uint64 points{0};

        bool triggerAnimation{false};
        bool active{true};

        std::vector<Projectile*> projectiles;

    public:
        EntityModel(const Utils::Vector2D& origin, float angle, const Utils::Vector2D& size, EntityType type, Uint64 points = 0)
                : origin(origin), angle(angle), size(size), type(type), points(points),
                  hitbox(std::make_unique<Physics::Hitbox>(origin, size)) {}

        EntityModel(const Utils::Vector2D& origin, float angle, const Utils::Vector2D& hitboxPos, const Utils::Vector2D& hitboxSize,
                    const Utils::Vector2D& size, EntityType type, Uint64 points = 0)
                : origin(origin), angle(angle), size(size), type(type), points(points),
                  hitbox(std::make_unique<Physics::Hitbox>(origin + hitboxPos, hitboxSize)) {}


        ~EntityModel() {
            for (Projectile* projectile : projectiles) {
                delete projectile;
            }
            projectiles.clear();
        }

        void update() {
            hitbox->updatePosition(origin);
            hitbox->updateAngle(angle);
        }

        const auto& getProjectiles() const {
            return projectiles;
        }

        void removeProjectile(size_t index) {
            if (index < projectiles.size()) {
                projectiles.erase(projectiles.begin() + index);
            }
        }

        void clearProjectiles() {
            projectiles.clear();
        }

        void addProjectile(Projectile* projectile) {
            projectiles.push_back(projectile);
        }

        bool isTriggerAnimation() const {
            return triggerAnimation;
        }

        void setTriggerAnimation(const bool setTriggerAnimation) {
            this->triggerAnimation = setTriggerAnimation;
        }

        void setOrigin(const Utils::Vector2D& newOrigin) {
            origin = newOrigin;
        }

        Utils::Vector2D getOrigin() const {
            return origin;
        }

        void setAngle(const float newAngle) {
            angle = newAngle;
        }

        float getAngle() const {
            return angle;
        }

        const Utils::Vector2D &getSize() const {
            return size;
        }

        Uint64 getPts() const {
            return points;
        }

        bool isActive() const {
            return active;
        }

        void setActive(bool isActive) {
            active = isActive;
        }

        Physics::Hitbox* getHitbox() const {
            return hitbox.get();
        }

        EntityType getType() const {
            return type;
        }
    };

}

#endif //BOSCONIAN_ENTITYMODEL_H
