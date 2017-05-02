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
private:
   NonConstructible() = default;
   NonConstructible( const NonConstructible & ) = default;
   NonConstructible( NonConstructible && ) = default;
   ~NonConstructible() = default;
};



class NonInstantiable {
   virtual void cannot_create_an_instance() = 0;
};



class Singleton {
private:
   Singleton( const Singleton & ) = default;
   Singleton & operator=( const Singleton & ) { return *this; }
   Singleton( Singleton && ) = default;

protected:
   Singleton() = default;
   ~Singleton() = default;
};



class NonCopyable {
   NonCopyable( const NonCopyable & ) = default;
   NonCopyable operator=( const NonCopyable & ) { return *this; }

protected:
   NonCopyable() = default;
   ~NonCopyable() = default;
};

}   // namespace simpleNewton

#endif
