#ifndef BOSCONIAN_MATH_H
#define BOSCONIAN_MATH_H

#include <random>

/**
 * @namespace Math
 * @brief Contains utility functions related to mathematical operations.
 */
namespace Math {

    /**
     * @brief Normalizes an angle to be between -180 and 180 degrees.
     * @param angle The angle to normalize.
     * @return Normalized angle.
     */
    float normalizeAngle180(float angle);

    /**
     * @brief Normalizes an angle to be between 0 and 360 degrees.
     * @param angle The angle to normalize.
     * @return Normalized angle.
     */
    float normalizeAngle360(float angle);

    /**
     * @brief Gets the bit value at a specific index in a 32-bit integer.
     * @param number The 32-bit number.
     * @param index The bit index (0-based).
     * @return true if the bit at the index is set, otherwise false.
     */
    bool getBitAtIndex(uint32_t number, uint8_t index);
}

#endif //BOSCONIAN_MATH_H
