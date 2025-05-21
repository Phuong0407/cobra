#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstdio>

struct Vector3 {
    double x1, x2, x3;

    Vector3() : x1(0.0), x2(0.0), x3(0.0) {}

    Vector3(double x1_, double x2_, double x3_) : x1(x1_), x2(x2_), x3(x3_) {}

    inline double norm() const { 
        return std::sqrt(x1 * x1 + x2 * x2 + x3 * x3);
    }

    inline void normalize() {
        double n = norm();
        if (n > 0.0) {
            x1 /= n;
            x2 /= n;
            x3 /= n;
        }
    }

    inline double dot(const Vector3& other) const {
        return x1 * other.x1 + x2 * other.x2 + x3 * other.x3;
    }

    inline Vector3 cross(const Vector3& other) const {
        return Vector3(
            x2 * other.x3 - x3 * other.x2,
            x3 * other.x1 - x1 * other.x3,
            x1 * other.x2 - x2 * other.x1
        );
    }

    inline Vector3 operator+(const Vector3& other) const {
        return Vector3(x1 + other.x1, x2 + other.x2, x3 + other.x3);
    }

    inline Vector3 operator-(const Vector3& other) const {
        return Vector3(x1 - other.x1, x2 - other.x2, x3 - other.x3);
    }

    inline Vector3 operator*(double scalar) const {
        return Vector3(x1 * scalar, x2 * scalar, x3 * scalar);
    }

    inline Vector3 operator/(double scalar) const {
        if (scalar == 0.0) {
            std::fprintf(stderr, "[ERROR]: Division by zero in Vector3::operator/.\n");
            return Vector3(0.0, 0.0, 0.0);
        }
        return Vector3(x1 / scalar, x2 / scalar, x3 / scalar);
    }

    void print() const {
        std::printf("Vector3: [%.6f, %.6f, %.6f]\n", x1, x2, x3);
    }
};

#endif // VECTOR_H
