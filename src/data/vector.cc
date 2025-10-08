#include <data/vector.h>
#include <limits>

namespace orbital_control{
namespace data{

Vector::Vector(double x0, double x1, double x2)
: x0(x0), x1(x1), x2(x2) {}

double Vector::norm() const {
  return std::sqrt(x0*x0 + x1*x1 + x2*x2);
}

void Vector::normalize() {
  double norm = this->norm();
  if (norm > 0.0) {
    x0 /= norm;
    x1 /= norm;
    x2 /= norm;
  }
}

Vector Vector::operator+(const Vector &v) const {
  return Vector(x0+v(0), x1+v(1), x2+v(2));
}

Vector Vector::operator*(const Vector &v) const {
  return Vector(x0*v(0), x1*v(1), x2*v(2));
}

Vector Vector::operator*(double d) const {
  return Vector(x0*d, x1*d, x2*d);
}

double Vector::operator()(const int i) const {
  if (i == 0) return x0;
  else if (i == 1) return x1;
  else if (i == 2) return x2;
  else return std::numeric_limits<double>::max();
}

void Vector::serialize(std::ostream& os) const {
  os << x0 << " " << x1 << " " << x2;
}

} /* namespace data */
} /* namespace orbital_control */
