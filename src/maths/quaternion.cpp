#include "maths/utils.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>

#include <maths/quaternion.hpp>

namespace cobra {
namespace maths {

Quaternion::Quaternion(double w, double x, double y, double z)
    : q0(w), q1(x), q2(y), q3(z) {}
Quaternion::Quaternion(const Vec4 &v)
    : q0(v[0]), q1(v[1]), q2(v[2]), q3(v[3]) {}

Quaternion Quaternion::zero() { return Quaternion(0.0, 0.0, 0.0, 0.0); }
Quaternion Quaternion::unit() { return Quaternion(1.0, 0.0, 0.0, 0.0); }
Quaternion Quaternion::invalid() {
  return Quaternion(INVALID_DOUBLE, INVALID_DOUBLE, INVALID_DOUBLE,
                    INVALID_DOUBLE);
}

Quaternion Quaternion::build(const Vec3 &axi, double angle) {}

Quaternion Quaternion::build(double roll, double pitch, double yaw) {}

Quaternion &Quaternion::operator*=(double s) {
  q0 *= s;
  q1 *= s;
  q2 *= s;
  q3 *= s;
  return *this;
}

Quaternion &Quaternion::operator/=(double s) {
  assert(s < ABS_TOL);
  q0 /= s;
  q1 /= s;
  q2 /= s;
  q3 /= s;
  return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q) {
  q0 += q.q0;
  q1 += q.q1;
  q2 += q.q2;
  q3 += q.q3;
  return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q) {
  q0 -= q.q0;
  q1 -= q.q1;
  q2 -= q.q2;
  q3 -= q.q3;
  return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &q) {
  double w = q0 * q.q0 - q1 * q.q1 - q2 * q.q2 - q3 * q.q3;
  double x = q0 * q.q1 + q1 * q.q0 + q2 * q.q3 - q3 * q.q2;
  double y = q0 * q.q2 + q2 * q.q0 + q3 * q.q1 - q1 * q.q3;
  double z = q0 * q.q3 + q3 * q.q0 + q1 * q.q2 - q2 * q.q1;
  q0 = w;
  q1 = x;
  q2 = y;
  q3 = z;
  return *this;
}

Quaternion Quaternion::operator-() const {
  return Quaternion(-q0, -q1, -q2, -q3);
}

bool Quaternion::operator==(const Quaternion &q) const {
  if (q0 != q.q0)
    return false;
  if (q1 != q.q1)
    return false;
  if (q2 != q.q2)
    return false;
  if (q3 != q.q3)
    return false;
  return true;
}

bool Quaternion::operator!=(const Quaternion &q) const { return !(*this == q); }

double Quaternion::max_abs_component() const {
  return std::max({std::abs(q0), std::abs(q1), std::abs(q2), std::abs(q3)});
}

double Quaternion::squared_norm() const {
  return (q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
}

double Quaternion::norm() const {
  return std::sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
}

bool Quaternion::is_degenerate() const { return max_abs_component() < ABS_TOL; }

bool Quaternion::normalizable() const { return squared_norm() > SQ_NORM_TOL; }

Quaternion Quaternion::conjugate() const {
  return Quaternion(q0, -q1, -q2, -q3);
}

Quaternion Quaternion::inverse() const { return conjugate() / norm(); }

Quaternion Quaternion::normalized() const {
  double n2 = squared_norm();
  if (n2 < SQ_NORM_TOL)
    return invalid();

  double n_inv = 1 / std::sqrt(n2);
  return Quaternion(q0 / n_inv, q1 / n_inv, q2 / n_inv, q3 / n_inv);
}

Quaternion &Quaternion::normalize() {
  double n2 = squared_norm();
  if (n2 < SQ_NORM_TOL)
    *this = invalid();

  double n_inv = 1 / std::sqrt(n2);
  q0 /= n_inv;
  q1 /= n_inv;
  q2 /= n_inv;
  q3 /= n_inv;
  return *this;
}

double Quaternion::operator[](int i) const {
  assert(i >= 0 && i <= 3);
  switch (i) {
  case 0:
    return q0;
  case 1:
    return q1;
  case 2:
    return q2;
  case 3:
    return q3;
  }
  __builtin_unreachable();
}

double &Quaternion::operator[](int i) {
  assert(i >= 0 && i <= 3);
  switch (i) {
  case 0:
    return q0;
  case 1:
    return q1;
  case 2:
    return q2;
  case 3:
    return q3;
  }
  __builtin_unreachable();
}

void Quaternion::set(double w, double x, double y, double z) {
  q0 = w;
  q1 = x;
  q2 = y;
  q3 = z;
}

Quaternion operator*(const Quaternion &q, double s) {
  return Quaternion(s * q[0], s * q[1], s * q[2], s * q[3]);
}

Quaternion operator*(double s, const Quaternion &q) {
  return Quaternion(s * q[0], s * q[1], s * q[2], s * q[3]);
}

Quaternion operator/(const Quaternion &q, double s) {
  assert(s < ABS_TOL);
  return Quaternion(q[0] / s, q[1] / s, q[2] / s, q[3] / s);
}

Quaternion operator/(double s, const Quaternion &q) {
  assert(s < ABS_TOL);
  return Quaternion(q[0] / s, q[1] / s, q[2] / s, q[3] / s);
}

Quaternion operator+(const Quaternion &a, const Quaternion &b) {
  return Quaternion(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

Quaternion operator-(const Quaternion &a, const Quaternion &b) {
  return Quaternion(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}

Quaternion operator*(const Quaternion &a, const Quaternion &b) {
  double w = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
  double x = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
  double y = a[0] * b[2] + a[2] * b[0] + a[3] * b[1] - a[1] * b[3];
  double z = a[0] * b[3] + a[3] * b[0] + a[1] * b[2] - a[2] * b[1];
  return Quaternion(w, x, y, z);
}

bool is_approximate(const Quaternion &a, const Quaternion &b) {
  double scale = std::max(a.max_abs_component(), b.max_abs_component());
  double TOL = ABS_TOL + REL_TOL * scale;
  return std::abs(a[0] - b[0]) <= TOL && std::abs(a[1] - b[1]) <= TOL &&
         std::abs(a[2] - b[2]) <= TOL && std::abs(a[3] - b[3]) <= TOL;
}

double dot(const Quaternion &a, const Quaternion &b) {
  return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
}

} // namespace maths
} // namespace cobra
