#ifndef include_data_vector_h
#define include_data_vector_h

#include <cmath>
#include <ostream>

namespace cobra{
namespace data{

class Vector {
public:
  Vector(double x0, double x1, double x2);
  double norm() const;
  void normalize();
  Vector operator+(const Vector &q) const;
  Vector operator*(const Vector &q) const;
  Vector operator*(double d) const;
  double operator()(int i) const;
  void serialize(std::ostream& os) const;

private:
  double x0;
  double x1;
  double x2;
};

} /* namespace data */
} /* namespace cobra */
#endif /* include_data_vector_h */
