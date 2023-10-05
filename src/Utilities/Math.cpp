#include "Math.h"

int Math::randomInt(const int min, const int max) {
    // Initialize the random engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initialize the distribution
    std::uniform_int_distribution<int> dis(min, max);

    // Generate a random integer in the range [min, max]
    return dis(gen);
}

float Math::randomFloat(const float min, const float max) {
    // Initialize the random engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initialize the distribution
    std::uniform_real_distribution<float> dis(min, max);

    // Generate a random float in the range [min, max]
    return dis(gen);
}

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