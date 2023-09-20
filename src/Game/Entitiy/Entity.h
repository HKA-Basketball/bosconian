#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include <utility>

#include "../../Drawing/Texture.h"
#include "EntityType.h"
#include "../Animations/ExplosionAnimation.h"
#include "../Projectile.h"
#include "../../Physics/Hitbox.h"
#include "../../Physics/Collision.h"
#include "../../Sound/SoundManager.h"
#include "../../../includes.h"
#include "../Animations/Animation.h"

namespace Game {

    class Entity {
    private:
        std::shared_ptr<Animation> explosionAnimation{new ExplosionAnimation()};
        std::shared_ptr<Drawing::Texture> texture;

        //EntityModel m_model;
        Utils::Vector2D origin;
        Utils::Vector2D size;
        float angle{0.0f};

        std::unique_ptr<Physics::Hitbox> hitbox;
        EntityType type;
        Uint64 points{0};

        bool triggerAnimation{false};
        bool active{true};

        std::vector<Projectile*> projectiles;


        virtual void updateBehaviour(float deltaTime = 0.f) {
            /* TODO: Default Behaviour */
        }

    public:
        Entity(Utils::Vector2D pos, float deg, const std::shared_ptr<Drawing::Texture>& img, EntityType type, Uint64 pts = 0)
                :   origin(pos), angle(deg), texture(img), size(img->getSize()), type(type), points(pts),
                    hitbox(std::make_unique<Physics::Hitbox>(origin, size))
        {}

        Entity(Utils::Vector2D pos, float deg, const std::shared_ptr<Drawing::Texture>& img,
               const Utils::Vector2D& hitboxPos, const Utils::Vector2D& hitboxSize, EntityType type, Uint64 pts = 0)
                :   origin(pos), angle(deg), texture(img), size(img->getSize()), type(type), points(pts),
                    hitbox(std::make_unique<Physics::Hitbox>(origin + hitboxPos, hitboxSize))
        {}

        ~Entity() = default;

        Animation* getAnimation() {
            return explosionAnimation.get();
        }

        void update(float deltaTime = 0.f) {
            updateBehaviour(deltaTime);

            explosionAnimation->update(texture, deltaTime);


            hitbox->updatePosition(origin);
            hitbox->updateAngle(angle);

            Utils::Vector2D screenPos;
            Utils::render::WorldToScreen(origin, screenPos);
            texture->setPos(screenPos);
            texture->setAngle(angle);

            // Update the positions of the entity projectiles
            for (int i = 0; i < projectiles.size(); i++) {
                projectiles[i]->update(deltaTime);
                // Check if the projectile is out of bounds
                if (projectiles[i]->isOffscreen() || !projectiles[i]->getActive()) {
                    removeProjectile(i);
                    i--;
                }
            }
        }

        void addProjectile(Projectile* newProjectile) {
            projectiles.push_back(newProjectile);
        }

        std::vector<Projectile*> getProjectiles() {
            return projectiles;
        }

        bool checkProjectiels(const Physics::Hitbox& entityHitbox) {
            for (int y = 0; y < projectiles.size(); y++){
                if (!projectiles[y]->getActive())
                    continue;

                if (Physics::CollisionManager::checkIntersect(projectiles[y]->getHitbox(), entityHitbox)) {
                    projectiles[y]->setActive(false);
                    return true;
                }
            }
            return false;
        }

        void removeProjectile(size_t index) {
            if (index < projectiles.size()) {
                projectiles.erase(projectiles.begin() + index);
            }
        }

        void clearProjectiels() {
            projectiles.clear();
        }

        void setActive(const bool newActive) {
            active = newActive;
        }

        bool isActive() {
            return active;
        }

        void setTriggerAnimation(const bool setTriggerAnimation) {
            this->triggerAnimation = setTriggerAnimation;
        }

        bool isTriggerAnimation() const {
            return triggerAnimation;
        }

        void setOrigin(const Utils::Vector2D& newOrigin) {
            origin = newOrigin;
        }

        EntityType getType() {
            return type;
        }

        Uint64 getPts() const {
            return points;
        }

        Utils::Vector2D getOrigin() {
            return origin;
        }

        Utils::Vector2D getSize() {
            return size;
        }

        void setAngle(float newAngle) {
            angle = newAngle;
        }

        float getAngle() {
            return angle;
        }

        Physics::Hitbox* getHitbox() {
            return hitbox.get();
        }

        void setTexture(const std::string& name) {
            if (!texture)
                return;

            texture->changeTexture(name, true, "spritesheet.png");
            update();
        }

        const std::shared_ptr<Drawing::Texture> &getTexture() const {
            return texture;
        }
    };
} // Game

#endif //BOSCONIAN_ENTITY_H
