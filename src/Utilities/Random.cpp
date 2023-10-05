#include "Random.h"

namespace Random {

    int randomInt(const int min, const int max) {
        // Initialize the random engine
        std::random_device rd;
        std::mt19937 gen(rd());

        // Initialize the distribution
        std::uniform_int_distribution<int> dis(min, max);

        // Generate a random integer in the range [min, max]
        return dis(gen);
    }

    float randomFloat(const float min, const float max) {
        // Initialize the random engine
        std::random_device rd;
        std::mt19937 gen(rd());

        // Initialize the distribution
        std::uniform_real_distribution<float> dis(min, max);

        // Generate a random float in the range [min, max]
        return dis(gen);
    }
}