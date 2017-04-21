#ifndef TYPES_HPP
#define TYPES_HPP
 
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

#include <types/Functor.hpp>

namespace simpleNewton {

// The empty class/typename
struct NullType {};

// Floating point types
using real_t         = double;
using single_t       = float;
using const_real_t   = const double;
using const_single_t = const float;

// Integer types
using byte_t        = char;
using uint_t        = unsigned int;
using small_t       = unsigned int;
using large_t       = unsigned long;
using ID_t          = unsigned long;
using const_byte_t  = const unsigned int;
using const_small_t = const unsigned int;
using const_large_t = const unsigned long;
using const_ID_t    = const unsigned long;

// Other
using string_t       = std::string;
using const_string_t = const std::string;
using flag_t         = bool;

// Inheritance casts
template< class CLS1, class CLS2 >
CLS1* SN_UP_CAST( CLS2* p ) { return p; }
template< class CLS1, class CLS2 >
CLS1* SN_DOWN_CAST( CLS2* p ) { return static_cast<CLS1*>(p); }

}   // namespace simpleNewton

#endif
