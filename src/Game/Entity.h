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
        bool active;

    public:
        EntityModel(Utils::Vector2D pos, float deg, Utils::Vector2D size, Uint64 points = 0) {
            origin = pos;
            angle = deg;
            pts = points;
            this->size = size;
            hitbox = new Game::Hitbox(origin, size);
            active = true;
        }

        void update() {
            // Update the hitbox position and angle based on the entity's properties
            hitbox->updateHitboxPos(origin);
            //hitbox->updateHitboxAngle(angle);
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
        Drawing::Texture* obj;
        const EntityModel& m_model;

        // TODO: Add Animation Manager

    public:
        EntityView(Drawing::Texture* img, const EntityModel& model)
            : obj(img)
            , m_model(model)
        {}

        void update() {
            Utils::Vector2D newPosScreen;
            Utils::render::WorldToScreen(m_model.getOrigin(), newPosScreen);
            obj->setPos(newPosScreen - (obj->getSize()*0.5f));
            obj->setAngel(m_model.getAngle());
        }

        void drawEntity() {
            obj->draw();
        }
    };

    class Entity {
    private:
        EntityModel m_model;
        EntityView m_view;

        //TODO: may add Typ for movement stuff

    public:
        Entity(Utils::Vector2D pos, float deg, Drawing::Texture* img, Uint64 pts = 0)
            : m_model(pos, deg, img->getSize(), pts)
            , m_view(img, m_model)
        {}

        void update() {
            if (!m_model.isActive())
                return;

            m_model.update();
            m_view.update();
        }

        void draw() {
            if (!m_model.isActive())
                return;

            m_view.drawEntity();
        }

        bool isActive() {
            return m_model.isActive();
        }

        void setActive(bool val) {
            m_model.setActive(val);
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
