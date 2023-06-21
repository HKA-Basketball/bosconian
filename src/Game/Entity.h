#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "../../includes.h"
#include "../Drawing/Texture.h"
#include "Hitbox.h"
#include "Projectile.h"
#include "../Sound/SoundManager.h"

namespace Game {

    enum class EntityType {
        None = 0,
        NonMoving,
        Moving,
        Base,
        Player
    };

    class EntityModel {
    private:
        Uint64 pts;
        Utils::Vector2D origin;
        Utils::Vector2D center;
        Utils::Vector2D size;
        float angle;
        Utils::Vector2D hitboxPos;
        Game::Hitbox* hitbox;
        bool triggerAnimation;
        bool active;
        std::vector<Projectile*> projectiles;
        EntityType type;

    public:
        EntityModel(Utils::Vector2D pos, float deg, Utils::Vector2D size, EntityType type, Uint64 points = 0) {
            origin = pos;
            angle = deg;
            pts = points;
            this->size = size;
            hitbox = new Game::Hitbox(origin, size);
            triggerAnimation = false;
            active = true;
        }

        EntityModel(Utils::Vector2D pos, float deg, Utils::Vector2D hitboxPos, Utils::Vector2D hitboxSize, Utils::Vector2D size, EntityType type, Uint64 points = 0) {
            origin = pos;
            angle = deg;
            pts = points;
            this->size = size;
            this->hitboxPos = hitboxPos;
            //LOG("Hitbox: " + std::to_string((origin + hitboxPos).x) + ":" + std::to_string((origin + hitboxPos).y) + " - " + std::to_string(hitboxSize.x) + ":" + std::to_string(hitboxSize.y));
            hitbox = new Game::Hitbox(origin + this->hitboxPos, hitboxSize);
            triggerAnimation = false;
            active = true;
        }

        ~EntityModel() {
            for (Projectile* projectile : projectiles) {
                delete projectile;
                projectile = nullptr;
            }
            projectiles.clear();

            delete hitbox;
            hitbox = nullptr;
        }

        void update() {
            // Update the hitbox position and angle based on the entity's properties
            hitbox->updateHitboxPos(origin + hitboxPos);
            //hitbox->updateHitboxAngle(angle);
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

        Game::Hitbox* getHitbox() const {
            return hitbox;
        }

        EntityType getType() const {
            return type;
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
            drawHitbox();
        }

        void setTexture(std::string name) {
            if (!obj)
                return;

            obj->changeTexture(name, true, "spritesheet.png");
            update();
        }

        void setSize(Utils::Vector2D size) {
            obj->setSize(size);
            update();
        }

    private:
        void drawHitbox() {
            if (!Utils::GlobalVars::debugMode)
                return;

            SDL_Rect worldPosRec = m_model.getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::render::WorldToScreen(worldPos, screenPos);

            SDL_Rect screenPosRect = {static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), worldPosRec.w, worldPosRec.h};

            //char pos[256];
            //snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)worldPosRec.x, (int)worldPosRec.y);
            //SDL_Rect destR = { 0, 0, 0, 0 };
            //TTF_SizeText(Renderer::g_renderer->m_fonts[1], pos, &destR.w, &destR.h);
            //Drawing::g_drawing->string(std::string(pos), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }, Utils::Vector2D(screenPos.x, screenPos.y));

            if (!m_model.isActive())
                Drawing::g_drawing->rectangle({255, 0, 0, 255}, screenPosRect);
            else
                Drawing::g_drawing->rectangle({0, 255, 0, 255}, screenPosRect);
        }
    };

    class Behavior {
    public:
        virtual void update(EntityModel& model, float deltaTime = 0.f) = 0;
        virtual void update(EntityView& view, float deltaTime = 0.f) = 0;
    };

    class MovingBehavior : public Behavior {
    public:
        void update(EntityModel& model, float deltaTime = 0.f) override {
            Utils::Vector2D currentPosition = model.getOrigin();
            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            float distance = (currentPosition - playerPosition).length();
            // TODO: may add viewAngle?
            float attackThreshold = 250.0f;

            if (distance <= attackThreshold) {
                move2Pos(model, playerPosition, deltaTime);
            }
            else {
                if (needNewPos) {
                    float randomX = Utils::GlobalVars::lvlWidth * static_cast<float>(std::rand()) / RAND_MAX;
                    float randomY = Utils::GlobalVars::lvlHeight * static_cast<float>(std::rand()) / RAND_MAX;
                    targetPos = {randomX, randomY};
                    needNewPos = false;
                }

                move2Pos(model, targetPos, deltaTime);
            }

            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
                animationTime = 0.f;
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
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

    private:
        Utils::Vector2D targetPos;
        bool needNewPos = true;

        bool animationStart = false;
        bool animationEnd = false;
        float animationTime = 0.f;
        const float animationDuration = 250.f;
        std::vector<std::string> explosionImages = {
                "astro-explo-01",
                "astro-explo-02",
                "astro-explo-03"
        };


        int roundToNearestMultiple(int angleInDegrees, int multiple) {
            int remainder = angleInDegrees % multiple;
            int result = angleInDegrees - remainder;
            if (remainder >= multiple / 2) {
                result += multiple;
            }
            return result;
        }

        void move2Pos(EntityModel& model, Utils::Vector2D pos2move, float deltaTime = 0.f) {

            Utils::Vector2D direction = pos2move - model.getOrigin();

            // Check if the player is spotted
            float detectionRange = 150.f; // Adjust the range as needed
            float distance = direction.length();

            if (distance <= detectionRange) {
                needNewPos = true;
            }

            direction.normalize();

            float speed = 190 * deltaTime;
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

    class CoreBehavior : public Behavior {
    private:
        bool animationStart = false;
        bool animationEnd = false;
        float animationTime = 0.f;
        const float animationDuration = 450.f;
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
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
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
            //xD may add new Texture
            view.setSize({288, 256});

            if (animationTime >= animationDuration)
                animationEnd = true;
        }
    };

    class CanonBehavior : public Behavior {
    private:
        bool animationStart = false;
        bool animationEnd = false;
        bool canShoot = false;
        Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 1500;
        std::string texture;
        float viewDirection;
        float viewAngle = 45.f;
        float viewLength = 400.0f;

        Utils::Vector2D canonPosition;

    public:
        CanonBehavior(std::string afterShoot, float initialViewDirection)
            : texture(afterShoot)
            , viewDirection(initialViewDirection)
        {}

        void update(EntityModel& model, float deltaTime = 0.f) override {
            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
            }

            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            canonPosition = model.getOrigin();

            Utils::Vector2D direction = playerPosition - canonPosition;
            float distance = direction.length();
            direction.normalize();

            // Calculate the angle between the Canon and the player
            float angleToPlayer = std::atan2(direction.y, direction.x);
            angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
            float targetAngle = Utils::Math::normalizeAngle180(angleToPlayer + 90.f);

            float startAngle = viewDirection - (viewAngle / 2.0f);
            float endAngle = viewDirection + (viewAngle / 2.0f);
            angleToPlayer = Utils::Math::normalizeAngle360(angleToPlayer);
            startAngle = Utils::Math::normalizeAngle360(startAngle);
            endAngle = Utils::Math::normalizeAngle360(endAngle);

            // Check if the player is within the view area
            bool playerInViewArea = false;
            if (startAngle <= endAngle) {
                playerInViewArea = (angleToPlayer >= startAngle && angleToPlayer <= endAngle);
            } else {
                playerInViewArea = (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
            }

            bool playerWithinDistance = distance <= viewLength;

            if (playerInViewArea && playerWithinDistance && model.isActive()) {
                Uint64 currentTime = SDL_GetTicks64();
                if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                    canShoot = true;
                    Sound::g_sound->playSound(Sound::SOUND_SHOOT, 4, 0);

                    Projectile* newProjectile = new Projectile(model.getOrigin().x, model.getOrigin().y
                            , 180, targetAngle);

                    model.addProjectile(newProjectile);
                    timeSinceLastProjectile = currentTime;
                }
            }

            if (animationEnd)
                model.setActive(false);
        }

        void update(EntityView& view, float deltaTime = 0.f) override {
            drawView();

            if (!animationStart)
                return;

            view.setTexture(texture);

            animationEnd = true;
        }
    private:
        void drawView() {
            if (!Utils::GlobalVars::debugMode)
                return;

            Utils::Vector2D tmp1;
            Utils::Vector2D tmp2;

            // Calculate the start and end angles of the view cone
            float startAngle = viewDirection - (viewAngle / 2.0f);
            float endAngle = viewDirection + (viewAngle / 2.0f);

            float endX = canonPosition.x + viewLength * std::cos(startAngle * (M_PI / 180.0f));
            float endY = canonPosition.y + viewLength * std::sin(startAngle * (M_PI / 180.0f));

            Utils::render::WorldToScreen(canonPosition, tmp1);
            Utils::render::WorldToScreen({endX, endY}, tmp2);

            Drawing::g_drawing->line({255, 255, 255, 255}, tmp1, tmp2);

            endX = canonPosition.x + viewLength * std::cos(endAngle * (M_PI / 180.0f));
            endY = canonPosition.y + viewLength * std::sin(endAngle * (M_PI / 180.0f));
            Utils::render::WorldToScreen(canonPosition, tmp1);
            Utils::render::WorldToScreen({endX, endY}, tmp2);

            Drawing::g_drawing->line({255, 255, 255, 255}, tmp1, tmp2);

            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;

            // Calculate the angle between the Canon and the player
            float angleToPlayer = std::atan2(playerPosition.y - canonPosition.y, playerPosition.x - canonPosition.x);
            angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
            angleToPlayer = Utils::Math::normalizeAngle360(angleToPlayer);
            startAngle = Utils::Math::normalizeAngle360(startAngle);
            endAngle = Utils::Math::normalizeAngle360(endAngle);

            // Check if the player's angle is within the view cone
            bool playerInCone = false;
            if (startAngle <= endAngle) {
                playerInCone = (angleToPlayer >= startAngle && angleToPlayer <= endAngle);
            } else {
                playerInCone = (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
            }

            if (playerInCone) {
                endX = canonPosition.x + viewLength * std::cos(angleToPlayer * (M_PI / 180.0f));
                endY = canonPosition.y + viewLength * std::sin(angleToPlayer * (M_PI / 180.0f));
                Utils::render::WorldToScreen(canonPosition, tmp1);
                Utils::render::WorldToScreen({endX, endY}, tmp2);

                Drawing::g_drawing->line({255, 0, 0, 255}, tmp1, tmp2);
            }
        }
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
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
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
        Utils::Vector2D startPos;
        bool once = false;


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
            if (!once) {
                startPos = model.getOrigin();
                once = true;
            }

            // Check if the spy has spotted the player
            if (isPlayerSpotted) {
                // Move away from the player
                moveAwayFromPlayer(model, deltaTime);
            } else {
                // Search for the player
                searchForPlayer(model, deltaTime);
            }


            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
                animationTime = 0.f;
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
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
            if (!model.isTriggerAnimation())
                Utils::GlobalVars::condition = 1;

            // Calculate the direction away from the player
            Utils::Vector2D direction2Player = model.getOrigin() - Utils::GlobalVars::cameraPos;
            Utils::Vector2D direction = startPos - model.getOrigin();

            float distance2StartPos = direction.length();

            float detectionRange = 600.f; // Adjust the range as needed
            float distance = direction2Player.length();

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

            if (distance2StartPos <= 50.f) {
                // TODO: Start Attack
                Utils::GlobalVars::condition = 2;
                model.setActive(false);
            }
        }
    };

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

        bool checkProjectiels(SDL_Rect entityHitbox) {
            for (int y = 0; y < m_model.getProjectiles().size(); y++){
                if (!m_model.getProjectiles()[y]->getActive())
                    continue;

                if (m_model.getProjectiles()[y]->ProjectileHitsEntity(entityHitbox)) {
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

        Game::Hitbox* getHitbox() {
            return m_model.getHitbox();
        }
    };
} // Game

#endif //BOSCONIAN_ENTITY_H
