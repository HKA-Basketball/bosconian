#ifndef BOSCONIAN_DEGREE_H
#define BOSCONIAN_DEGREE_H

#include <cmath>

/**
 * @brief Encapsulates angle values in degrees, providing utility methods and operators.
 *
 * This class ensures that degree values are always maintained in the range [0, 360).
 */
class Degree {
private:
    float degree;  //!< The degree value stored in this Degree object.

public:
    /**
     * @brief Construct a new Degree object.
     *
     * @param initialDegree Initial value in degrees.
     */
    Degree(float initialDegree = 0);

    /**
     * @brief Set the Degree value while ensuring it remains in the range [0, 360).
     *
     * @param newDegree New degree value to set.
     */
    void setDegree(const float newDegree);

    /**
     * @brief Get the current degree value.
     *
     * @return float Degree value.
     */
    float getDegree() const;

    /**
     * @brief Convert the degree value to radians.
     *
     * @return float Radian equivalent of the degree value.
     */
    float toRadians() const;

    // Arithmetic operators
    Degree operator+(const Degree& other) const;
    Degree operator+(float value) const;
    Degree operator-(const Degree& other) const;
    Degree operator-(float value) const;
    Degree operator*(float value) const;
    Degree operator*(const Degree& other) const;
    Degree operator/(float value) const;

    // Arithmetic-assignment operators
    Degree& operator+=(const Degree& other);
    Degree& operator+=(float value);
    Degree& operator-=(const Degree& other);
    Degree& operator-=(float value);
    Degree& operator*=(float value);
    Degree& operator*=(const Degree& other);
    Degree& operator/=(float value);
};

#endif //BOSCONIAN_DEGREE_H
