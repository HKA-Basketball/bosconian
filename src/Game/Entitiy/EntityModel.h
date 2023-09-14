#ifndef BOSCONIAN_ENTITYMODEL_H
#define BOSCONIAN_ENTITYMODEL_H

#include "EntityType.h"
#include "../Projectile.h"
#include "../../Physics/Collision.h"
#include "../../Physics/Hitbox.h"
#include "../../../includes.h"

namespace Game {

    class EntityModel {
    private:
        Uint64 pts;
        Utils::Vector2D origin;
        Utils::Vector2D size;
        float angle;
        Physics::Hitbox* hitbox;
        bool triggerAnimation;
        bool active;
        std::vector<Projectile*> projectiles;
        EntityType type;

    public:
        EntityModel(const Utils::Vector2D& origin, float angle, const Utils::Vector2D& size, EntityType type, Uint64 pts = 0) :
            origin(origin), angle(angle), size(size), type(type), pts(pts), active(true), triggerAnimation(false) {
            hitbox = new Physics::Hitbox(origin, size);
        }

        EntityModel(const Utils::Vector2D& origin, float angle, const Utils::Vector2D& hitboxPos, const Utils::Vector2D& hitboxSize,
                    const Utils::Vector2D& size, EntityType type, Uint64 pts = 0) :
            origin(origin), angle(angle), size(size), type(type), pts(pts), active(true), triggerAnimation(false) {
            hitbox = new Physics::Hitbox(origin + hitboxPos, hitboxSize);
        }

        ~EntityModel() {
            for (Projectile* projectile : projectiles) {
                delete projectile;
            }
            projectiles.clear();

            delete hitbox;
            hitbox = nullptr;
        }

        void update() {
            // Update the hitbox position and angle based on the entity's properties
            hitbox->updatePosition(origin);
            hitbox->updateAngle(angle);
        }

        const std::vector<Projectile*> &getProjectiles() const {
            return projectiles;
        }

        void removeProjectile(int index) {
            if (!projectiles[index])
                return;

            delete projectiles[index];
            projectiles[index] = nullptr;
            std::swap(projectiles[index], projectiles.back());
            projectiles.pop_back();
        }

        void clearProjectiles() {
            for (Projectile* entity : projectiles) {
                delete entity;
                entity = nullptr;
            }
            projectiles.clear();
        }

        void addProjectile(Projectile* pro) {
            projectiles.push_back(pro);
        }

        bool isTriggerAnimation() const {
            return triggerAnimation;
        }

        void setTriggerAnimation(bool triggerAnimation) {
            this->triggerAnimation = triggerAnimation;
        }

        void setOrigin(Utils::Vector2D newOrigin) {
            origin = newOrigin;
        }

        Utils::Vector2D getOrigin() const {
            return origin;
        }

        void setAngle(float newAngle) {
            angle = newAngle;
        }

        float getAngle() const {
            return angle;
        }

        const Utils::Vector2D &getSize() const {
            return size;
        }

        Uint64 getPts() const {
            return pts;
        }

        bool isActive() const {
            return active;
        }

        void setActive(bool val) {
            active = val;
        }

        Physics::Hitbox* getHitbox() const {
            return hitbox;
        }

        EntityType getType() const {
            return type;
        }
    };

}

#endif //BOSCONIAN_ENTITYMODEL_H
