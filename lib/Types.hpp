#ifndef TYPES_HPP
#define TYPES_HPP
 
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

namespace simpleNewton {

// Floating point types
using real_t = double;
using single_t = float;
using ConstReal_t = const double;
using ConstSingle_t = const float;

// Integer types
using std::size_t;
using long_t = unsigned long;
using large_t = unsigned long long;
using ConstLong_t = const unsigned long;
using ConstLarge_t = const unsigned long long;

// Other
using std::string;
using flag_t = bool;

// Inheritance casts
template< class CLS1, class CLS2 >
CLS1* SN_UP_CAST( CLS2* p ) { return p; }
template< class CLS1, class CLS2 >
CLS1* SN_DOWN_CAST( CLS2* p ) { return static_cast<CLS1*>(p); }

}   // namespace simpleNewton

#endif
