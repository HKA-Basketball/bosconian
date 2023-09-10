#ifndef BOSCONIAN_VEC2_H
#define BOSCONIAN_VEC2_H

#include <cmath>

/**
 * Represents a 2D vector.
 */
class Vec2 {
public:
    float x, y;

    /**
     * Default constructor. Initializes the vector to (0, 0).
     */
    Vec2(void) { x = y = 0.0f; }
    /**
     * Parametrized constructor. Initializes the vector to the given coordinates.
     * \param X The x-coordinate of the vector.
     * \param Y The y-coordinate of the vector.
     */
    Vec2(float X, float Y) { x = X; y = Y; }
    /**
     * Copy constructor. Creates a new vector with the same values as the given vector.
     * \param v The vector to copy from.
     */
    Vec2(const Vec2& v) { x = v.x; y = v.y; }

    Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    Vec2& operator*=(const Vec2& v) { x *= v.x; y *= v.y; return *this; }
    Vec2& operator/=(const Vec2& v) { x /= v.x; y /= v.y; return *this; }
    Vec2& operator+=(float v) { x += v; y += v; return *this; }
    Vec2& operator-=(float v) { x -= v; y -= v; return *this; }
    Vec2& operator*=(float v) { x *= v; y *= v;; return *this; }
    Vec2& operator/=(float v) { x /= v; y /= v; return *this; }
    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(float scale) const { return Vec2(x * scale , y * scale ); }
    Vec2 operator/(float scale) const { return Vec2(x / scale, y / scale); }

    inline bool operator!=(const Vec2& src) const
    {
        return (src.x != x) || (src.y != y);
    }

    inline bool operator==(const Vec2& src) const
    {
        return (src.x == x) && (src.y == y);
    }

    /**
     * Calculates the length of the vector.
     * \return The length of the vector.
     */
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    /**
     * Checks if the vector's components are finite.
     * \return True if both components are finite, false otherwise.
     */
    __inline bool isValid() const
    {
        return std::isfinite(x) && std::isfinite(y);
    }

    /**
     * Calculates the squared length of the vector.
     * \return The squared length of the vector.
     */
    float lengthSquared() const {
        return (x * x + y * y);
    }

    /**
     * Calculates the dot product of this vector with another vector.
     * \param other The other vector.
     * \return The dot product.
     */
    float dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    /**
     * Rotates the vector by a given angle (in radians) and returns the rotated vector.
     * \param angle The angle to rotate by.
     * \return The rotated vector.
     */
    Vec2 rotate(float angle) const {
        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);

        float rotatedX = x * cosAngle - y * sinAngle;
        float rotatedY = x * sinAngle + y * cosAngle;

        return Vec2(rotatedX, rotatedY);
    }

    /**
     * Returns a normalized copy of the vector.
     * \return The normalized vector.
     */
    Vec2 normalized() const
    {
        Vec2 res = *this;
        float l = res.length();
        if (l != 0.0f) {
            res /= l;
        }
        else {
            res.x = res.y = 0.0f;
        }
        return res;
    }

    /**
     * Normalizes the vector in place.
     */
    void normalize() {
        float magnitude = this->length();
        if (magnitude != 0) {
            x /= magnitude;
            y /= magnitude;
        }
    }
};

#endif //BOSCONIAN_VEC2_H
