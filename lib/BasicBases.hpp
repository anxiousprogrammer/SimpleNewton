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
   NonConstructible() = delete;
   NonConstructible( const NonConstructible & ) = delete;
   NonConstructible( NonConstructible && ) = delete;
   ~NonConstructible() = delete;
};



class NonInstantiable {
   virtual void cannot_create_an_instance() = 0;
};



class Singleton {

private:
   Singleton( const Singleton & ) = delete;   // Copying is not allowed.
   Singleton( Singleton && ) = default;       // Can be moved if that is required.

protected:
   Singleton() = default;    // Private inheritance == private creation.
   ~Singleton() = default;   // Born within, died within.
};



class NonCopyable {

   NonCopyable( const NonCopyable & ) = delete;

protected:
   NonCopyable() = default;
   NonCopyable( NonCopyable && ) = default;
   ~NonCopyable() = default;
};



class NonMovable {

   NonMovable( NonMovable && ) = delete;

protected:
   NonMovable() = default;
   NonMovable( const NonMovable & ) = default;
   ~NonMovable() = default;
};

}   // namespace simpleNewton

#endif
