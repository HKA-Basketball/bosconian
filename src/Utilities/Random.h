#ifndef BOSCONIAN_RANDOM_H
#define BOSCONIAN_RANDOM_H

#include <random>
#include <vector>

namespace Random {

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
