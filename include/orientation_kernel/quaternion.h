#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include <cstdio>
#include "./data_structure/vector.h"

struct Quaternion {
    double q0, q1, q2, q3;

    Quaternion() : q0(1.0), q1(0.0), q2(0.0), q3(0.0) {}
    Quaternion(double q0_, double q1_, double q2_, double q3_)
        : q0(q0_), q1(q1_), q2(q2_), q3(q3_) {}

    double norm() const {
        return std::sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    }

    void normalize() {
        double n = norm();
        if (n > 0.0) {
            q0 /= n;
            q1 /= n;
            q2 /= n;
            q3 /= n;
        }
    }

    Quaternion conjugate() const {
        return Quaternion(q0, -q1, -q2, -q3);
    }

    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            q0*other.q0 - q1*other.q1 - q2*other.q2 - q3*other.q3,
            q0*other.q1 + q1*other.q0 + q2*other.q3 - q3*other.q2,
            q0*other.q2 - q1*other.q3 + q2*other.q0 + q3*other.q1,
            q0*other.q3 + q1*other.q2 - q2*other.q1 + q3*other.q0
        );
    }

    Vector3 rotate(const Vector3& v) const {
        Quaternion vq(0.0, v.x1, v.x2, v.x3);
        Quaternion result = (*this) * vq * this->conjugate();
        return Vector3(result.q1, result.q2, result.q3);
    }

    void print() const {
        std::printf("Quaternion: [%.6f, %.6f, %.6f, %.6f]\n", q0, q1, q2, q3);
    }
};

#endif // QUATERNION_H
