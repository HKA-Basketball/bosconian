#include "Math.h"

namespace Math {

    float randomFloat(const float min, const float max) {
        // Initialize the random engine
        std::random_device rd;
        std::mt19937 gen(rd());

        // Initialize the distribution
        std::uniform_real_distribution<float> dis(min, max);

        // Generate a random float in the range [min, max]
        return dis(gen);
    }

    float normalizeAngle180(float angle) {
        angle = std::fmod(angle, 360.0f);
        if (angle > 180.0f) {
            angle -= 360.0f;
        } else if (angle < -180.0f) {
            angle += 360.0f;
        }
        return angle;
    }

    float normalizeAngle360(float angle) {
        angle = std::fmod(angle, 360.0f);
        if (angle < 0) {
            angle += 360.0f;
        }
        return angle;
    }

}