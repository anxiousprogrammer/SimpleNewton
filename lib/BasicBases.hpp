#ifndef BASICBASES_HPP
#define BASICBASES_HPP

#include <Types.hpp>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Simple bases which yield useful functionality
*
|***************************************************************************************************************************************///+

class NonConstructible {
   NonConstructible() = default;
   NonConstructible( const NonConstructible & ) = default;
   NonConstructible( NonConstructible && ) = default;
   ~NonConstructible() = default;
};

class NonCopyable {
   NonCopyable( const NonCopyable & ) = default;
   NonCopyable operator=( const NonCopyable & );
protected:
   NonCopyable() = default;
};

}   // namespace simpleNewton

#endif
