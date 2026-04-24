#ifndef COBRA_INCLUDE_MATHS_QUATERNION_HPP
#define COBRA_INCLUDE_MATHS_QUATERNION_HPP

#include <maths/matrix.hpp>
#include <maths/utils.hpp>
#include <maths/vector.hpp>

namespace cobra {
namespace maths {

class Quaternion {
public:
  Quaternion() = default;
  Quaternion(double w, double x, double y, double z);
  explicit Quaternion(const Vec4 &v);

  Quaternion(const Quaternion &) = default;
  Quaternion(Quaternion &&) noexcept = default;
  Quaternion &operator=(const Quaternion &) = default;
  Quaternion &operator=(Quaternion &&) noexcept = default;
  ~Quaternion() = default;

  static Quaternion zero();
  static Quaternion unit();
  static Quaternion invalid();

  static Quaternion build(const Vec3 &axis, double angle);
  static Quaternion build(double roll, double pitch, double yaw);

  Quaternion &operator*=(double s);
  Quaternion &operator/=(double s);
  Quaternion &operator+=(const Quaternion &q);
  Quaternion &operator-=(const Quaternion &q);
  Quaternion &operator*=(const Quaternion &q);
  Quaternion operator-() const;

  bool operator==(const Quaternion &q) const;
  bool operator!=(const Quaternion &q) const;

  double max_abs_component() const;
  double squared_norm() const;
  double norm() const;

  bool is_degenerate() const;
  bool normalizable() const;

  Quaternion conjugate() const;
  Quaternion inverse() const;

  Quaternion normalized() const;
  Quaternion &normalize();

  double w() const { return q0; }
  double x() const { return q1; }
  double y() const { return q2; }
  double z() const { return q3; }
  double operator[](int i) const;
  double &operator[](int i);

  void set(double w, double x, double y, double z);

private:
  double q0{0.0};
  double q1{0.0};
  double q2{0.0};
  double q3{0.0};
};

Quaternion operator*(const Quaternion &q, double s);
Quaternion operator*(double s, const Quaternion &q);
Quaternion operator/(const Quaternion &q, double s);
Quaternion operator/(double s, const Quaternion &q);

Quaternion operator+(const Quaternion &a, const Quaternion &b);
Quaternion operator-(const Quaternion &a, const Quaternion &b);
Quaternion operator*(const Quaternion &a, const Quaternion &b);

double dot(const Quaternion &a, const Quaternion &b);
bool is_approximate(const Quaternion &a, const Quaternion &b);

Vec3 rotate(const Quaternion &q, const Vec3 &v);
Mat3 to_rotation_matrix(const Quaternion &q);
Quaternion slerp(const Quaternion &a, const Quaternion &b, double t);

} // namespace maths
} // namespace cobra

#endif // !COBRA_INCLUDE_MATHS_QUATERNION_HPP
