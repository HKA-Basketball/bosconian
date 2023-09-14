#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "EntityView.h"
#include "EntityModel.h"
#include "EntityType.h"
#include "Behaviour/Behaviour.h"
#include "../Projectile.h"
#include "../../Drawing/Texture.h"
#include "../../Physics/Hitbox.h"
#include "../../Physics/Collision.h"
#include "../../Sound/SoundManager.h"
#include "../../../includes.h"

namespace Game {

    class Entity {
    private:
        EntityModel m_model;
        EntityView m_view;
        Behavior* m_behavior;

    public:
        Entity(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, EntityType type, Uint64 pts = 0)
                : m_model(pos, deg, img->getSize(), type, pts)
                , m_view(img, m_model)
                , m_behavior(nullptr)
        {}

        Entity(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, Utils::Vector2D hitboxPos, Utils::Vector2D hitboxSize, EntityType type, Uint64 pts = 0)
                : m_model(pos, deg, hitboxPos, hitboxSize, img->getSize(), type, pts)
                , m_view(img, m_model)
                , m_behavior(nullptr)
        {}

        ~Entity() {
            if (m_behavior)
                delete m_behavior;
            m_behavior = nullptr;
        }

        void setBehavior(Behavior* behavior) {
            if (m_behavior)
                delete m_behavior;

            m_behavior = behavior;
        }

        void update(float deltaTime = 0.f) {
            if (m_behavior)
                m_behavior->update(m_model, deltaTime);

            m_model.update();
            m_view.update();

            // Update the positions of the entity projectiles
            for (int i = 0; i < m_model.getProjectiles().size(); i++) {
                m_model.getProjectiles()[i]->update(deltaTime);
                // Check if the projectile is out of bounds
                if (m_model.getProjectiles()[i]->isOffscreen() || !m_model.getProjectiles()[i]->getActive()) {
                    m_model.removeProjectile(i);
                    i--;
                }
            }
        }

        void draw(float deltaTime = 0.f) {
            if (m_behavior)
                m_behavior->update(m_view, deltaTime);

            m_view.drawEntity();

            // Render the entity projectiles
            for (auto& projectile : m_model.getProjectiles()) {
                projectile->render();
            }
        }

        void addProjectile(Projectile* pro) {
            m_model.addProjectile(pro);
        }

        bool checkProjectiels(const Physics::Hitbox& entityHitbox) {
            for (int y = 0; y < m_model.getProjectiles().size(); y++){
                if (!m_model.getProjectiles()[y]->getActive())
                    continue;

                if (Physics::CollisionManager::checkIntersect(m_model.getProjectiles()[y]->getHitbox(), entityHitbox)) {
                    m_model.getProjectiles()[y]->setActive(false);
                    return true;
                }
            }
            return false;
        }

        void clearProjectiels() {
            m_model.clearProjectiles();
        }

        bool isActive() {
            return m_model.isActive();
        }

        void setTriggerAnimation(bool val) {
            m_model.setTriggerAnimation(val);
        }

        bool isTriggerAnimation() {
            return m_model.isTriggerAnimation();
        }

        void setOrigin(Utils::Vector2D newOrigin) {
            m_model.setOrigin(newOrigin);
        }

        EntityType getType() {
            return m_model.getType();
        }

        Uint64 getPTS() {
            return m_model.getPts();
        }

        Utils::Vector2D getOrigin() {
            return m_model.getOrigin();
        }

        Utils::Vector2D getSize() {
            return m_model.getSize();
        }

        void setAngle(float newAngle) {
            m_model.setAngle(newAngle);
        }

        float getAngle() {
            return m_model.getAngle();
        }

        Physics::Hitbox* getHitbox() {
            return m_model.getHitbox();
        }
    };
} // Game

#endif //BOSCONIAN_ENTITY_H
