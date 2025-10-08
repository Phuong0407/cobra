#ifndef include_data_quaternion_h
#define include_data_quaternion_h

#include <cmath>
#include <ostream>

namespace orbital_control{
namespace data{

class Quaternion {
public:
  Quaternion(double q0, double q1, double q2, double q3);
  double norm() const;
  void normalize();
  Quaternion conjugate() const;
  Quaternion operator+(const Quaternion &q) const;
  Quaternion operator*(const Quaternion &q) const;
  Quaternion operator*(double d) const;
  double operator()(int i) const;
  void serialize(std::ostream& os) const;

private:
  double q0;
  double q1;
  double q2;
  double q3;
};

} /* namespace data */
} /* namespace orbital_control */

#endif /* include_data_quaternion_h */