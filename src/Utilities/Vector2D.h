#ifndef BOSCONIAN_VECTOR2D_H
#define BOSCONIAN_VECTOR2D_H

#include <cmath>

namespace Utils {

    class Vector2D {
    public:
        float x, y;

        Vector2D(void) { x = y = 0.0f; }
        Vector2D(float X, float Y) { x = X; y = Y; }
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

        float length() const
        {
            return sqrtf(x * x + y * y);
        }

        __inline bool isValid() const
        {
            return std::isfinite(x) && std::isfinite(y);
        }

        float lengthSquared() const {
            return (x * x + y * y);
        }

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
    };

} // Utils

#endif //BOSCONIAN_VECTOR2D_H
