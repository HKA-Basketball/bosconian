#include "Math.h"
#include "Random.h"

float Math::normalizeAngle180(float angle) {
    angle = std::fmod(angle, 360.0f);
    if (angle > 180.0f) {
        angle -= 360.0f;
    } else if (angle < -180.0f) {
        angle += 360.0f;
    }
    return angle;
}

float Math::normalizeAngle360(float angle) {
    angle = std::fmod(angle, 360.0f);
    if (angle < 0) {
        angle += 360.0f;
    }
    return angle;
}

bool Math::getBitAtIndex(uint32_t number, uint8_t index) {
    index %= 32;
    return (number & (1u << index)) != 0;
}