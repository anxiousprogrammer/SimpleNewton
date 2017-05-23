#ifndef SN_PROCTIMER_HPP
#define SN_PROCTIMER_HPP

#include <chrono>

#include <Types.hpp>
#include <BasicBases.hpp>

#include <iostream>
#include <types/BasicTypeTraits.hpp>

//==========================================================================================================================================
//
//  This file is part of simpleNewton. simpleNewton is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  simpleNewton is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with simpleNewton (see LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
//
///   Contains the class ProcTimer which is supposed to provide high resolution, precise, reliable and accurate time information.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {



#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace timer {
namespace internal {

/* Feed a clock to this struct and you'll get a steady_clock if it isn't steady. */
template< bool IS_STEADY > struct steady_clock_fallback;
template<> struct steady_clock_fallback< true >  { using type = std::chrono::high_resolution_clock; };
template<> struct steady_clock_fallback< false > { using type = std::chrono::steady_clock;          };

// Boolean SFINAE struct for partial specialization selection.
template< bool T > struct SFINAE_void;
template<> struct SFINAE_void< true >  { using type = void; };
template<> struct SFINAE_void< false > {};

/* Precision selector */
template< std::intmax_t , std::intmax_t , typename=void > struct ChosenResolution;

template< std::intmax_t NUM, std::intmax_t DEN > 
struct ChosenResolution< NUM, DEN, typename SFINAE_void< ( real_cast(NUM)/real_cast(DEN) <  real_cast(1.0) && 
                                                           real_cast(NUM)/real_cast(DEN) >= real_cast(1e-3) ) >::type > {
   using type = std::chrono::milliseconds;
};

template< std::intmax_t NUM, std::intmax_t DEN > 
struct ChosenResolution< NUM, DEN, typename SFINAE_void< ( real_cast(NUM)/real_cast(DEN) <  real_cast(1e-3) && 
                                                           real_cast(NUM)/real_cast(DEN) >= real_cast(1e-6) ) >::type > {
   using type = std::chrono::microseconds;
};

template< std::intmax_t NUM, std::intmax_t DEN > 
struct ChosenResolution< NUM, DEN, typename SFINAE_void< ( real_cast(NUM)/real_cast(DEN) <  real_cast(1e-6) && 
                                                           real_cast(NUM)/real_cast(DEN) >= real_cast(1e-9) ) >::type > {
   using type = std::chrono::nanoseconds;
};

}   // namespace impl
}   // namespace timer
#endif   // DOXYSKIP



//===CLASS==================================================================================================================================

/** A reliable timer which can be used for a variety of purposes, including benchmarking code performance. Therefore it is required that it 
*   provides high resolution, precise and accurate time information.
*/
//==========================================================================================================================================

class ProcTimer {

public:

   /** A type definition which selects the clock for the timer. If the std::chrono::high_resolution_clock is steady, it is chosen. 
   *   Otherwise, std::chrono::steady_clock is selected.
   */
   using clock = timer::internal::steady_clock_fallback< std::chrono::high_resolution_clock::is_steady >::type;
   /** A typedef which names the resolution type to be used for the clock: std::chrono::milliseconds, std::chrono::microseconds or 
   *   std::chrono::nanoseconds.
   */
   using res = typename timer::internal::ChosenResolution< clock::period::num, clock::period::den >::type;
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Default trivial constructor. */
   ProcTimer() = default;
   
   /** Default destructor. */
   ~ProcTimer() = default;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to get the exact resolution of the clock being used.
   *
   *   \return   The time period of one tick of the clock.
   */
   static inline real_t getExactResolution()   { return real_cast( clock::period::num ) / real_cast( clock::period::den ); }
   
   /** A function to get the age of the timer in seconds.
   *
   *   \return   The time period between the function call and the construction of the timer.
   */
   inline real_t getAge() {
      
      auto current_tp = clock::now();
      return std::chrono::duration_cast< res >( current_tp - tp0_ ).count() * res_;
   }
   
   /** @} */
   
private:

   real_t res_ = real_cast( clock::period::num ) / real_cast( clock::period::den );   ///< Resolution of chosen clock.
   std::chrono::time_point< clock > tp0_ = clock::now();                              ///< The starting time point.
};

}   // namespace simpleNewton
#endif
