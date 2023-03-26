#ifndef BOSCONIAN_ENTITY_H
#define BOSCONIAN_ENTITY_H

#include "../../includes.h"
#include "../Drawing/Image.h"
#include "Hitbox.h"

namespace Game {

    class Entity {
    private:
        // TODO: add Bounds, may Change Image Class to Texture
        // TODO: add Score PTS ... May Add an extra Class for an Player (Entity than only for Enemies I guess)
        // TODO: add Animation, Better Movement Handler

        Drawing::Image* obj;
        Game::Hitbox* hitbox;
        Utils::Vector2D origin;
        // TODO:
        Utils::Vector2D center;
        float angle;

    public:
        Entity(Utils::Vector2D pos, float deg, Drawing::Image* img);

        void update();

        void setOrigin(Utils::Vector2D newOrigin);
        Utils::Vector2D getOrigin();

        void setAngle(float newAngle);
        float getAngle();

        Game::Hitbox* getHitbox();

        bool move2Pos(Utils::Vector2D to, float speed);

    };

} // Game

#endif //BOSCONIAN_ENTITY_H
