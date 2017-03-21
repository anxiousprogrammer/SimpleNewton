#ifndef GLOBALCONSTANTS_HPP
#define GLOBALCONSTANTS_HPP

#include <limits>
#include "Types.hpp"

namespace simpleNewton {
namespace globalConstants {

constexpr real_t ZERO = std::numeric_limits< real_t >::epsilon();

}   // namespace globalConstants
}   // namespace simpleNewton

#endif
