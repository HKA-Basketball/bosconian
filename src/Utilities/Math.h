#ifndef BOSCONIAN_MATH_H
#define BOSCONIAN_MATH_H

#include <random>

namespace Math {
    float randomFloat(const float min, const float max);
    float normalizeAngle180(float angle);
    float normalizeAngle360(float angle);
}

#endif //BOSCONIAN_MATH_H
