#ifndef BOSCONIAN_CAMERA_H
#define BOSCONIAN_CAMERA_H

#include "Entity/Entity.h"
#include "Entity/Player.h"

class Camera {
private:
    int x; // Center of the camera
    int y;
    int width;  // Screen width
    int height; // Screen height

public:
    Camera(int w, int h) : x(0), y(0), width(w), height(h) {}

    void centerOn(const Player& player) {
        x = player.getX();
        y = player.getY();
    }

    bool isInView(const Entity& obj) const {
        int halfWidth = width / 2;
        int halfHeight = height / 2;

        return (obj.getX() > x - halfWidth && obj.getX() < x + halfWidth &&
                obj.getY() > y - halfHeight && obj.getY() < y + halfHeight);
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};


#endif //BOSCONIAN_CAMERA_H
