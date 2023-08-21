#ifndef BOSCONIAN_VECTOR2D_H
#define BOSCONIAN_VECTOR2D_H

#include <cmath>

namespace Utils {

    /**
     * Represents a 2D vector.
     */
    class Vector2D {
    public:
        float x, y;

        /**
         * Default constructor. Initializes the vector to (0, 0).
         */
        Vector2D(void) { x = y = 0.0f; }
        /**
         * Parametrized constructor. Initializes the vector to the given coordinates.
         * \param X The x-coordinate of the vector.
         * \param Y The y-coordinate of the vector.
         */
        Vector2D(float X, float Y) { x = X; y = Y; }
        /**
         * Copy constructor. Creates a new vector with the same values as the given vector.
         * \param v The vector to copy from.
         */
        Vector2D(const Vector2D& v) { x = v.x; y = v.y; }

        Vector2D& operator+=(const Vector2D& v) { x += v.x; y += v.y; return *this; }
        Vector2D& operator-=(const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
        Vector2D& operator*=(const Vector2D& v) { x *= v.x; y *= v.y; return *this; }
        Vector2D& operator/=(const Vector2D& v) { x /= v.x; y /= v.y; return *this; }
        Vector2D& operator+=(float v) { x += v; y += v; return *this; }
        Vector2D& operator-=(float v) { x -= v; y -= v; return *this; }
        Vector2D& operator*=(float v) { x *= v; y *= v;; return *this; }
        Vector2D& operator/=(float v) { x /= v; y /= v; return *this; }
        Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
        Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
        Vector2D operator*(float scale) const { return Vector2D(x * scale , y * scale ); }
        Vector2D operator/(float scale) const { return Vector2D(x / scale, y / scale); }

        inline bool operator!=(const Vector2D& src) const
        {
            return (src.x != x) || (src.y != y);
        }

        inline bool operator==(const Vector2D& src) const
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
        float dot(const Vector2D& other) const {
            return x * other.x + y * other.y;
        }

        /**
         * Rotates the vector by a given angle (in radians) and returns the rotated vector.
         * \param angle The angle to rotate by.
         * \return The rotated vector.
         */
        Vector2D rotate(float angle) const {
            float cosAngle = std::cos(angle);
            float sinAngle = std::sin(angle);

            float rotatedX = x * cosAngle - y * sinAngle;
            float rotatedY = x * sinAngle + y * cosAngle;

            return Vector2D(rotatedX, rotatedY);
        }

        /**
         * Returns a normalized copy of the vector.
         * \return The normalized vector.
         */
        Vector2D normalized() const
        {
            Vector2D res = *this;
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

} // Utils

#endif //BOSCONIAN_VECTOR2D_H
