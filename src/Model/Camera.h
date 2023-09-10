#ifndef BOSCONIAN_CAMERA_H
#define BOSCONIAN_CAMERA_H

#include "Entity/Entity.h"
#include "Entity/Player.h"

class Camera {
private:
    Vec2 center; // Center of the camera
    int width;  // Screen width
    int height; // Screen height

public:
    Camera(int w, int h) : center(Vec2()), width(w), height(h) {}

    void centerOn(const Player& player) {
        center = player.getPosition();
    }

    bool isInView(const Entity& entity) const {
        int halfWidth = width / 2;
        int halfHeight = height / 2;

        Vec2 position = entity.getPosition();
        return (position.x > center.x - halfWidth && position.x < center.x + halfWidth &&
                position.y > center.y - halfHeight && position.y < center.y + halfHeight);
    }

    Vec2 getCenter() const { return center; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};


#endif //BOSCONIAN_CAMERA_H
