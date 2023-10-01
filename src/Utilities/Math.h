#ifndef BOSCONIAN_MATH_H
#define BOSCONIAN_MATH_H

#include <random>

namespace Math {
    float randomInt(const int min, const int max);
    float randomFloat(const float min, const float max);
    float normalizeAngle180(float angle);
    float normalizeAngle360(float angle);
    bool getBitAtIndex(uint32_t number, uint8_t index);
}

#endif //BOSCONIAN_MATH_H
