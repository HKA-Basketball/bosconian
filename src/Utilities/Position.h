#ifndef BOSCONIAN_POSITION_H
#define BOSCONIAN_POSITION_H

#include <array>

#include "Vector2D.h"
#include "Config.h"


class Position {
public:
    // Define an enum for indexing the wrapped positions
    enum Type {
        CENTER,
        RIGHT,
        LEFT,
        UP,
        DOWN,
        UP_RIGHT,
        DOWN_LEFT,
        DOWN_RIGHT,
        UP_LEFT,
        COUNT // total number of positions
    };

private:
    std::array<Vector2D, Type::COUNT> wrappedPositions;

public:
    // Constructors
    Position(const float x, const float y) : Position(Vector2D{x, y}) {}

    Position(const Vector2D& initialPosition) {
        setCenterPosition(initialPosition);
    }

    // Getter for center position
    Vector2D getCenterPosition() const {
        return wrappedPositions.at(Type::CENTER);
    }

    // Getter for a specific position
    Vector2D getPosition(Type type) const {
        return wrappedPositions.at(type);
    }

    std::array<Vector2D, Type::COUNT> getWrappedPositions() const {
        return wrappedPositions;
    }

    // Setter for the center position
    void setCenterPosition(const Vector2D& newPosition) {
        wrappedPositions.at(CENTER) = newPosition;
        updateWrappedPositions();
    }

private:
    // Updates the wrapped positions based on the current center position
    void updateWrappedPositions() {
        wrappedPositions.at(RIGHT) = wrappedPositions.at(CENTER) + Vector2D(Config::levelWidth, 0);
        wrappedPositions.at(LEFT) = wrappedPositions.at(CENTER) - Vector2D(Config::levelWidth, 0);
        wrappedPositions.at(UP) = wrappedPositions.at(CENTER) + Vector2D(0, Config::levelHeight);
        wrappedPositions.at(DOWN) = wrappedPositions.at(CENTER) - Vector2D(0, Config::levelHeight);
        wrappedPositions.at(UP_RIGHT) = wrappedPositions.at(CENTER) + Vector2D(Config::levelWidth, Config::levelHeight);
        wrappedPositions.at(DOWN_LEFT) = wrappedPositions.at(CENTER) - Vector2D(Config::levelWidth, Config::levelHeight);
        wrappedPositions.at(DOWN_RIGHT) = wrappedPositions.at(CENTER) + Vector2D(Config::levelWidth, 0) - Vector2D(0, Config::levelHeight);
        wrappedPositions.at(UP_LEFT) = wrappedPositions.at(CENTER) - Vector2D(Config::levelWidth, 0) + Vector2D(0, Config::levelHeight);
    }
};

typedef std::array<Vector2D, Position::Type::COUNT> WrappedPositions;

#endif //BOSCONIAN_POSITION_H
