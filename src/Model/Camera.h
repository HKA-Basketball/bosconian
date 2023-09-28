#ifndef BOSCONIAN_CAMERA_H
#define BOSCONIAN_CAMERA_H

#include <optional>

#include "Entities/Entity.h"
#include "Entities/Player.h"

class Camera {
private:
    static Camera* instance;

    Vector2D center{0, 0}; // Center of the camera
    Vector2D size{Config::screenWidth, Config::screenHeight}; // Screen size


    Camera() {}
    ~Camera() {}

public:
    //Camera(const Vector2D& size) : size(size) {}

    static Camera* Instance() {
        if (!instance) {
            instance = new Camera();
            return instance;
        }
        return instance;
    }

    void centerOn(const Vector2D& newCenter);

    // Method to transform world coordinates to screen coordinates
    Vector2D WorldToScreen(const Vector2D& worldPosition) const;

    // Check if the object is within the camera's view
    std::optional<Vector2D> IsInView(const Entity& entity) const;

    Vector2D getCenter() const { return this->center; }
    Vector2D getSize() const { return this->size; }
    void setSize(const Vector2D& newSize) { this->size = newSize; }
};


#endif //BOSCONIAN_CAMERA_H
