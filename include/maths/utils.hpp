#ifndef COBRA_INCLUDE_MATHS_UTILS_HPP
#define COBRA_INCLUDE_MATHS_UTILS_HPP

#include <limits>
namespace cobra {
namespace maths {

constexpr double REL_TOL = 1e-12;
constexpr double ABS_TOL = 1e-15;
constexpr double SQ_NORM_TOL = 1e-24;

constexpr double INVALID_DOUBLE = std::numeric_limits<double>::quiet_NaN();

} // namespace maths
} // namespace cobra
#endif // !COBRA_INCLUDE_MATHS_UTILS_HPP
