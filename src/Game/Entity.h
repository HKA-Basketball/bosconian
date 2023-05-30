#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "../../includes.h"
#include "../Drawing/Texture.h"
#include "Hitbox.h"

namespace Game {

    class EntityModel {
    private:
        Uint64 pts;
        Utils::Vector2D origin;
        Utils::Vector2D center;
        Utils::Vector2D size;
        float angle;
        Game::Hitbox* hitbox;
        bool triggerAnimation;
        bool active;

    public:
        EntityModel(Utils::Vector2D pos, float deg, Utils::Vector2D size, Uint64 points = 0) {
            origin = pos;
            angle = deg;
            pts = points;
            this->size = size;
            hitbox = new Game::Hitbox(origin, size);
            triggerAnimation = false;
            active = true;
        }

        void update() {
            // Update the hitbox position and angle based on the entity's properties
            hitbox->updateHitboxPos(origin);
            //hitbox->updateHitboxAngle(angle);
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

        Uint64 getPts() const {
            return pts;
        }

        bool isActive() const {
            return active;
        }

        void setActive(bool val) {
            active = val;
        }

        Game::Hitbox* getHitbox() {
            return hitbox;
        }

        bool move2Pos(Utils::Vector2D to, float speed) {
            Utils::Vector2D direction = to - origin;
            float distance = direction.length();

            if (distance <= speed) {
                origin = to;
                return true;
            }

            direction.normalize();
            Utils::Vector2D displacement = direction * speed;
            origin += displacement;

            return false;
        }
    };

    class EntityView {
    private:
        std::shared_ptr<Drawing::Texture> obj;
        const EntityModel& m_model;

    public:
        EntityView(std::shared_ptr<Drawing::Texture> img, const EntityModel& model)
            : obj(img)
            , m_model(model)
        {}

        void update() {
            if (!obj)
                return;

            Utils::Vector2D newPosScreen;
            Utils::render::WorldToScreen(m_model.getOrigin(), newPosScreen);
            obj->setPos(newPosScreen - (obj->getSize()*0.5f));
            obj->setAngel(m_model.getAngle());
        }

        void drawEntity() {
            if (!obj)
                return;

            obj->draw();
        }

        void setTexture(std::string name) {
            if (!obj)
                return;

            obj->changeTexture(name, true, "spritesheet.png");
            Utils::Vector2D newPosScreen;
            Utils::render::WorldToScreen(m_model.getOrigin(), newPosScreen);
            obj->setPos(newPosScreen - (obj->getSize()*0.5f));
            obj->setAngel(m_model.getAngle());
        }
    };

    class Behavior {
    public:
        virtual void update(EntityModel& model, float deltaTime = 0.f) = 0;
        virtual void update(EntityView& view, float deltaTime = 0.f) = 0;
    };

    class NonMovingBehavior : public Behavior {
    private:
        bool animationStart = false;
        bool animationEnd = false;
        float animationTime = 0.f;
        const float animationDuration = 250.f;
        std::vector<std::string> explosionImages = {
                "astro-explo-01",
                "astro-explo-02",
                "astro-explo-03"
        };

    public:
        void update(EntityModel& model, float deltaTime = 0.f) override {
            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
                animationTime = 0.f;
            }

            if (animationEnd)
                model.setActive(false);
        }

        void update(EntityView& view, float deltaTime = 0.f) override {
            if (!animationStart)
                return;

            animationTime += deltaTime * 1000.f;

            float progress = animationTime / animationDuration;
            progress = std::clamp(progress, 0.f, 1.f);
            int imageIndex = static_cast<int>(progress * (explosionImages.size() - 1));

            view.setTexture(explosionImages[imageIndex]);

            if (animationTime >= animationDuration)
                animationEnd = true;
        }
    };

    class SpyBehavior : public Behavior {
    private:
        bool isPlayerSpotted;
        bool isMovingTowardsPlayer;

    public:
        void update(EntityModel& model, float deltaTime = 0.f) override {
            // Check if the spy has spotted the player
            if (isPlayerSpotted) {
                // Move away from the player
                moveAwayFromPlayer(model, deltaTime);
            } else {
                // Search for the player
                searchForPlayer(model, deltaTime);
            }
        }

        void update(EntityView& view, float deltaTime = 0.f) override {
            // TODO: add animation
        }
    private:
        int roundToNearestMultiple(int angleInDegrees, int multiple) {
            int remainder = angleInDegrees % multiple;
            int result = angleInDegrees - remainder;
            if (remainder >= multiple / 2) {
                result += multiple;
            }
            return result;
        }

        void searchForPlayer(EntityModel& model, float deltaTime = 0.f) {
            // Perform search behavior to find the player

            Utils::Vector2D direction = Utils::GlobalVars::cameraPos - model.getOrigin();

            // Check if the player is spotted
            float detectionRange = 150.f; // Adjust the range as needed
            float distance = direction.length();

            if (distance <= detectionRange) {
                isPlayerSpotted = true;
                isMovingTowardsPlayer = false;
            }

            direction.normalize();

            float speed = 250 * deltaTime;
            Utils::Vector2D newPosition;

            // Calculate the closest 45-degree angle
            float angle = std::atan2(direction.y, direction.x);
            int angleInDegrees = static_cast<int>(std::round(angle * 180 / M_PI));
            int closestAngleInDegrees = roundToNearestMultiple(angleInDegrees, 45);
            float closestAngle = closestAngleInDegrees * M_PI / 180;

            // Calculate the target direction based on the closest angle
            Utils::Vector2D targetDirection(std::cos(closestAngle), std::sin(closestAngle));

            // Calculate the dot product between the current direction and the target direction
            float dotProduct = direction.dot(targetDirection);

            // Calculate the turning angle based on the dot product and the turning speed
            float turningAngle = std::acos(dotProduct) * speed;

            // Rotate the direction towards the target direction by the turning angle
            Utils::Vector2D newDirection = direction.rotate(turningAngle);

            // Calculate the new position using the new direction and speed
            newPosition = model.getOrigin() + newDirection * speed;

            float angleF = std::atan2(newDirection.y, newDirection.x);
            float angleInDegreesF = angleF * 180 / M_PI;
            float targetAngle = Utils::Math::normalizeAngle180(angleInDegreesF + 90.f);

            // Apply a smoothing factor
            const float smoothingFactor = 0.1f;

            float currentAngle = model.getAngle();
            float smoothedAngle = currentAngle + smoothingFactor * Utils::Math::normalizeAngle180(targetAngle - currentAngle);

            model.setAngle(smoothedAngle);

            Utils::Math::wrapPos(&newPosition);

            model.setOrigin(newPosition);
        }

        void moveAwayFromPlayer(EntityModel& model, float deltaTime = 0.f) {
            // TODO: Go back to the Base Ship ?
            // Calculate the direction away from the player
            Utils::Vector2D direction = model.getOrigin() - Utils::GlobalVars::cameraPos;

            float detectionRange = 600.f; // Adjust the range as needed
            float distance = direction.length();

            if (distance >= detectionRange) {
                isPlayerSpotted = false;
                isMovingTowardsPlayer = true;
            }

            direction.normalize();

            float speed = 250 * deltaTime;
            Utils::Vector2D newPosition;

            // Calculate the closest 45-degree angle
            float angle = std::atan2(direction.y, direction.x);
            int angleInDegrees = static_cast<int>(std::round(angle * 180 / M_PI));
            int closestAngleInDegrees = roundToNearestMultiple(angleInDegrees, 45);
            float closestAngle = closestAngleInDegrees * M_PI / 180;

            // Calculate the target direction based on the closest angle
            Utils::Vector2D targetDirection(std::cos(closestAngle), std::sin(closestAngle));

            // Calculate the dot product between the current direction and the target direction
            float dotProduct = direction.dot(targetDirection);

            // Calculate the turning angle based on the dot product and the turning speed
            float turningAngle = std::acos(dotProduct) * speed;

            // Rotate the direction towards the target direction by the turning angle
            Utils::Vector2D newDirection = direction.rotate(turningAngle);

            // Calculate the new position using the new direction and speed
            newPosition = model.getOrigin() + newDirection * speed;

            float angleF = std::atan2(newDirection.y, newDirection.x);
            float angleInDegreesF = angleF * 180 / M_PI;
            float targetAngle = Utils::Math::normalizeAngle180(angleInDegreesF + 90.f);

            // Apply a smoothing factor
            const float smoothingFactor = 0.1f;

            float currentAngle = model.getAngle();
            float smoothedAngle = currentAngle + smoothingFactor * Utils::Math::normalizeAngle180(targetAngle - currentAngle);

            model.setAngle(smoothedAngle);

            Utils::Math::wrapPos(&newPosition);

            model.setOrigin(newPosition);
        }
    };

    class Entity {
    private:
        EntityModel m_model;
        EntityView m_view;
        Behavior* m_behavior;

    public:
        Entity(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, Uint64 pts = 0)
            : m_model(pos, deg, img->getSize(), pts)
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
            if (!m_model.isActive())
                return;

            if (m_behavior)
                m_behavior->update(m_model, deltaTime);

            m_model.update();
            m_view.update();
        }

        void draw(float deltaTime = 0.f) {
            if (!m_model.isActive())
                return;

            if (m_behavior)
                m_behavior->update(m_view, deltaTime);

            m_view.drawEntity();
        }

        bool isActive() {
            return m_model.isActive();
        }

        void setTriggerAnimation(bool val) {
            m_model.setTriggerAnimation(val);
        }

        void setOrigin(Utils::Vector2D newOrigin) {
            m_model.setOrigin(newOrigin);
        }

        Uint64 getPTS() {
            return m_model.getPts();
        }

        Utils::Vector2D getOrigin() {
            return m_model.getOrigin();
        }

        void setAngle(float newAngle) {
            m_model.setAngle(newAngle);
        }

        float getAngle() {
            return m_model.getAngle();
        }

        Game::Hitbox* getHitbox() {
            return m_model.getHitbox();
        }

        bool move2Pos(Utils::Vector2D to, float speed) {
            return m_model.move2Pos(to, speed);
        }
    };
} // Game

#endif //BOSCONIAN_ENTITY_H
