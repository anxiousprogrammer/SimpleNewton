#pragma once
#include <limits>
#include "Types.hh"

namespace simpleNewton {
namespace globalConstants {

constexpr real_t POSITIVEZERO = std::numeric_limits< real_t >::epsilon();
constexpr real_t NEGATIVEZERO = std::numeric_limits< real_t >::epsilon() * static_cast< real_t >(-1.f);

}   // namespace globalConstants
}   // namespace simpleNewton
