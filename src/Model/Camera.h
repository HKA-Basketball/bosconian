#ifndef BOSCONIAN_CAMERA_H
#define BOSCONIAN_CAMERA_H

#include <optional>

#include "Entities/Entity.h"
#include "Entities/Player.h"

/**
 * @class Camera
 * @brief Represents a camera in the game for rendering and view calculations.
 *
 * The camera has a center and a size, which determine its view. Entities can be checked
 * against this view to see if they should be rendered.
 */
class Camera {
private:
    Vector2D center{0, 0};                                    //!< Center of the camera in world coordinates.
    Vector2D size{Config::screenWidth, Config::screenHeight}; //!< Size of the camera view in pixels.

public:
    /**
     * @brief Default constructor.
     */
    Camera() = default;

    /**
     * @brief Default destructor.
     */
    ~Camera() = default;

    /**
     * @brief Set the center of the camera.
     * @param newCenter New center in world coordinates.
     */
    void centerOn(const Vector2D& newCenter);

    /**
     * @brief Converts a world coordinate to a screen coordinate based on the camera's view.
     * @param worldPosition Position in world coordinates.
     * @return Position in screen coordinates.
     */
    Vector2D WorldToScreen(const Vector2D& worldPosition) const;

    /**
     * @brief Check if a given entity is within the camera's view.
     * @param entity Entity to check.
     * @return Position where the entity is in view or std::nullopt if it's not in view.
     */
    std::optional<Vector2D> IsInView(const Entity& entity) const;

    /**
     * @brief Get the center of the camera.
     * @return Center of the camera in world coordinates.
     */
    Vector2D getCenter() const { return this->center; }

    /**
     * @brief Get the size of the camera view.
     * @return Size of the camera view in pixels.
     */
    Vector2D getSize() const { return this->size; }

    /**
     * @brief Set the size of the camera view.
     * @param newSize New size for the camera view in pixels.
     */
    void setSize(const Vector2D& newSize) { this->size = newSize; }
};

#endif //BOSCONIAN_CAMERA_H