#ifndef TYPES_HPP
#define TYPES_HPP
 
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

#include <types/Functor.hpp>

namespace simpleNewton {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Basic types for the framework
///////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Casts for the framework
/////////////////////////////

// Inheritance casts
template< class CLS1, class CLS2 >
CLS1* SN_UP_CAST( CLS2* p ) { return p; }
template< class CLS1, class CLS2 >
CLS1* SN_DOWN_CAST( CLS2* p ) { return static_cast<CLS1*>(p); }

// Simple typecasts
#define real_cast(X)     static_cast< real_t >(X)
#define single_cast(X)   static_cast< single_t >(X)
#define byte_cast(X)     static_cast< char >(X)
#define int_cast(X)      static_cast< int >(X)
#define uint_cast(X)     static_cast< uint_t >(X)
#define small_cast(X)    static_cast< small_t >(X)
#define large_cast(X)    static_cast< large_t >(X)
#define ID_cast(X)       static_cast< ID_t >(X)
#define string_cast(X)   static_cast< string_t >(X)
#define flag_cast(X)     static_cast< flag_t >(X)

}   // namespace simpleNewton

#endif
