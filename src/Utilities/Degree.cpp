#include "Degree.h"

Degree::Degree(const float initialDegree) {
    setDegree(initialDegree);
}

void Degree::setDegree(const float newDegree) {
    degree = std::fmod(newDegree, 360.0f);
    if(degree < 0) degree += 360.0f;
}

float Degree::getDegree() const {
    return degree;
}

float Degree::toRadians() const {
    return this->degree * (static_cast<float>(M_PI) / 180.0f);
}

Degree Degree::operator+(const Degree& other) const {
    return {degree + other.getDegree()};
}

Degree Degree::operator+(const float value) const {
    return {degree + value};
}

Degree Degree::operator-(const Degree& other) const {
    return {degree - other.getDegree()};
}

Degree Degree::operator-(const float value) const {
    return {degree - value};
}

Degree Degree::operator*(const float value) const {
    return {degree * value};
}

Degree Degree::operator*(const Degree& other) const {
    return {degree * other.getDegree()};
}

Degree Degree::operator/(const float value) const {
    if(value != 0) {
        return {degree / value};
    } else {
        return {};  // Return a Degree object initialized to zero as a fallback
    }
}

// Overloaded arithmetic-assignment operators
Degree& Degree::operator+=(const Degree& other) {
    setDegree(degree + other.getDegree());
    return *this;
}

Degree& Degree::operator+=(const float value) {
    setDegree(degree + value);
    return *this;
}

Degree& Degree::operator-=(const Degree& other) {
    setDegree(degree - other.getDegree());
    return *this;
}

Degree& Degree::operator-=(const float value) {
    setDegree(degree - value);
    return *this;
}

Degree& Degree::operator*=(const float value) {
    setDegree(degree * value);
    return *this;
}

Degree& Degree::operator*=(const Degree& other) {
    setDegree(degree * other.getDegree());
    return *this;
}

Degree& Degree::operator/=(const float value) {
    if(value != 0) {
        setDegree(degree / value);
    } else {
        setDegree({});  // Return a Degree object initialized to zero as a fallback

    }
    return *this;
}