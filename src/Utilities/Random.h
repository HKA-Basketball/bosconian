#ifndef BOSCONIAN_RANDOM_H
#define BOSCONIAN_RANDOM_H

#include <random>
#include <vector>


namespace Random {

    /**
     * @brief Generates a random integer between min and max (inclusive).
     * @param min The minimum integer value.
     * @param max The maximum integer value.
     * @return Random integer between min and max.
     */
    int randomInt(int min, int max);

    /**
     * @brief Generates a random float between min and max (inclusive for min and exclusive for max).
     * @param min The minimum float value.
     * @param max The maximum float value.
     * @return Random float between min and max.
     */
    float randomFloat(float min, float max);

    template <typename T, typename... Args>
    T getRandomOne(T first, Args... args) {
        std::vector<T> values = {first, args...};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(0, values.size() - 1);

        return values[dist(gen)];
    }

}

#endif //BOSCONIAN_RANDOM_H
