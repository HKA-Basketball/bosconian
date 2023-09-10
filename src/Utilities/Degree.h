#ifndef BOSCONIAN_DEGREE_H
#define BOSCONIAN_DEGREE_H

#include <cmath>

class Degree {
private:
    float degree;  // The degree value stored in this Degree object

public:
    Degree(const float initialDegree = 0) {
        setDegree(initialDegree);
    }

    // Setter method to update the degree while ensuring it remains in the range [0, 360)
    void setDegree(const float newDegree) {
        degree = std::fmod(newDegree, 360.0f);
        if(degree < 0) degree += 360.0f;
    }

    // Getter method to obtain the current degree value
    float getDegree() const {
        return degree;
    }

    // Method to convert the degree to radians
    float toRadians() const {
        return this->degree * (static_cast<float>(M_PI) / 180.0f);
    }

    // Method to add a value (either Degree or float) to the current degree
    Degree operator+(const Degree& other) const {
        return {degree + other.getDegree()};
    }

    Degree operator+(const float value) const {
        return {degree + value};
    }

    // Method to subtract a value (either Degree or float) from the current degree
    Degree operator-(const Degree& other) const {
        return {degree - other.getDegree()};
    }

    Degree operator-(const float value) const {
        return {degree - value};
    }

    Degree operator*(const float value) const {
        return {degree * value};
    }

    Degree operator*(const Degree& other) const {
        return {degree * other.getDegree()};
    }

    Degree operator/(const float value) const {
        if(value != 0) {
            return {degree / value};
        } else {
            //std::cerr << "Division by zero error.\n";
            return {};  // Return a Degree object initialized to zero as a fallback
        }
    }

    // Overloaded arithmetic-assignment operators
    Degree& operator+=(const Degree& other) {
        setDegree(degree + other.getDegree());
        return *this;
    }

    Degree& operator+=(const float value) {
        setDegree(degree + value);
        return *this;
    }

    Degree& operator-=(const Degree& other) {
        setDegree(degree - other.getDegree());
        return *this;
    }

    Degree& operator-=(const float value) {
        setDegree(degree - value);
        return *this;
    }

    Degree& operator*=(const float value) {
        setDegree(degree * value);
        return *this;
    }

    Degree& operator*=(const Degree& other) {
        setDegree(degree * other.getDegree());
        return *this;
    }

    Degree& operator/=(const float value) {
        if(value != 0) {
            setDegree(degree / value);
        } else {
            //std::cerr << "Division by zero error.\n";
        }
        return *this;
    }

    // Additional functionality can be added as per your requirements (like multiplication, division, etc.)
};

#endif //BOSCONIAN_DEGREE_H
