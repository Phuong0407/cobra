/:include <data/quaternion.h>

namespace cobra
{

namespace data{
Quaternion::Quaternion(double q0, double q1, double q2, double q3)
: q0(q0), q1(q1), q2(q2), q3(q3) {}


double Quaternion::norm() const {
  return std::sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
}

void Quaternion::normalize() {
  double norm = this->norm();
  if (norm > 0.0) {
    this->q0 /= norm;
    this->q1 /= norm;
    this->q2 /= norm;
    this->q3 /= norm;
  }
}

Quaternion Quaternion::conjugate() const {
  return Quaternion(q0, -q1, -q2, -q3);
}

Quaternion Quaternion::operator +(const Quaternion &q) const {
  return Quaternion(q0 + q.q0, q1 + q.q1, q2 + q.q2, q3 + q.q3);
}

Quaternion Quaternion::operator *(const Quaternion &q) const {
  return Quaternion(q0*q.q0 - q1*q.q1 - q2*q.q2 - q3*q.q3,
                    q0*q.q1 + q1*q.q0 + q2*q.q3 - q3*q.q2,
                    q0*q.q2 - q1*q.q3 + q2*q.q0 + q3*q.q1,
                    q0*q.q3 + q1*q.q2 - q2*q.q1 + q3*q.q0
                  );
}

Quaternion Quaternion::operator *(double d) const {
  return Quaternion(q0*d, q1*d, q2*d, q3*d);
}

double Quaternion::operator ()(int i) const {
  if (i == 0) return q0;
  else if (i == 1) return q1;
  else if (i == 2) return q2;
  else if (i == 3) return q3;
  else return std::numeric_limits<double>::max();
}

void Quaternion::serialize(std::ostream& os) const {
  os << q0 << " " << q1 << " " << q2 << " " << q3;
}

} /* namespace data */
} /* namespace cobra */
