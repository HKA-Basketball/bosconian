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

    /**
     * @brief Returns a randomly-selected value from the provided arguments.
     *
     * This function accepts a variable number of arguments of type `T` and
     * returns one of them selected at random.
     *
     * @tparam T The type of the values to be considered.
     * @tparam Args Variadic template type for the values.
     * @param first The first value.
     * @param args Additional values.
     * @return A randomly-selected value from the provided arguments.
     *
     * @example
     * int randomVal = getRandomOne(1, 2, 3, 4, 5); // could return any value between 1 and 5
     */
    template <typename T, typename... Args>
    T getRandomOne(T first, Args... args) {
        std::vector<T> values = {first, args...};

        // Initialize the random engine
        std::random_device rd;
        std::mt19937 gen(rd());

        // Initialize the distribution
        std::uniform_int_distribution<size_t> dist(0, values.size() - 1);

        // Generate a random element
        return values[dist(gen)];
    }

}

#endif //BOSCONIAN_RANDOM_H
