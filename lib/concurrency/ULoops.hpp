#ifndef ULOOPS_HPP
#define ULOOPS_HPP

#include <Types.hpp>

namespace simpleNewton {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

template< class TYPE >
struct ULoops_CPPHackClass {};

/**||***************************************************************************************************************************************
*
*   Description: Performance optimized loops for you and me
*
|***************************************************************************************************************************************///+

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Principle: static loop unrolling for pipelining, end-of-loop test postponing
//////////////////////////////////////////////////////////////////////////////////

namespace fastloops {
namespace impl {

// Declaration
template< small_t SIZE, class... PARAM > struct static_loop_unroll_impl;

// Terminator
template< class... PARAM > 
struct static_loop_unroll_impl< 0, PARAM... > {
   static inline void run( void(*)( small_t, PARAM... ), PARAM... ) {}
};

// Acting specialization
template< small_t SIZE, class... PARAM >
struct static_loop_unroll_impl {
   static inline void run( void(*operation)( small_t, PARAM... ), PARAM... arg ) { 
      operation( SIZE, arg...);
      static_loop_unroll_impl< SIZE-1, PARAM... >::run( operation, arg... );
   }
};

}   // namespace impl
}   // namespace fastloops


// Client function
template< small_t SIZE, class... PARAM > void SN_STATIC_LOOP_UNROLL( void(*operation)( small_t, PARAM... ), PARAM... arg ) {
   fastloops::impl::static_loop_unroll_impl< SIZE, PARAM... >::run( operation, arg... );
}

}   // namespace simpleNewton
#endif
