#ifndef SN_EULEREXPLICITWKBB_HPP
#define SN_EULEREXPLICITWKBB_HPP

#include <algorithm>
#include <vector>

#include <Types.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <core/Exceptions.hpp>

#include <containers/Field.hpp>
#include <containers/Vector3.hpp>

#include <concurrency/OpenMP.hpp>

#include "WorldKinematicsBB.hpp"

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
///   Contains the class EulerExplicitWKBB, which derives from WorldKinematicsBB and implements the explicit Euler method.
///   \file
///   \addtogroup math Math
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template< typename FP_TYPE_T >
class EulerExplicitWKBB : public WorldKinematicsBB<FP_TYPE_T> {

   /* Ancestral visibility */
   using WorldKinematicsBB<FP_TYPE_T>::startTime_;
   using WorldKinematicsBB<FP_TYPE_T>::currentTime_;
   using WorldKinematicsBB<FP_TYPE_T>::timeStep_;

   using WorldKinematicsBB<FP_TYPE_T>::position_;
   using WorldKinematicsBB<FP_TYPE_T>::velocity_;
   using WorldKinematicsBB<FP_TYPE_T>::acceleration_;

   using WorldKinematicsBB<FP_TYPE_T>::size_;

   
   EulerExplicitWKBB() = default;
   
public:
   
   /** \name Destructor
   *   @{
   */
   ~EulerExplicitWKBB() = default;

   /** @} */
   
   /** \name Primary functionality
   *   @{
   */

   /** A function which allocates field resources for a new object. Notes on exception safety: basic safety guaranteed. The function throws 
   *   an AllocError exception if the required resource allocation were not possible.
   *
   *   \return   A handle to the newly created object
   */
   Object_ID_t createObject() override final {
      
      try {
         
         position_.pushBack();
         velocity_.pushBack();
         acceleration_.pushBack();
      }
      catch( const AllocError & ) {
         SN_THROW_ALLOC_ERROR();
      }
      
      return ++size_;
   }

   /** A pure virtual function which requires all base classes to implement a method of kinematic integration. */   
   void integrate() override final {
      
      if( size_ == 0 )
         return;
      
      SN_ASSERT( position_.getSize() == size_ && velocity_.getSize() == size_ && acceleration_.getSize() == size_ );
      
      SN_OPENMP_SIMD_LOOP( OMP_PRIVATE( timeStep_ ) )
      for( large_t i = 0; i < size_; ++i ) {

         position_[i] += velocity_[i] * timeStep_;
         velocity_[i] += acceleration_[i] * timeStep_;
      }
   }
   
   /** @} */
};

}   // namespace simpleNewton

#endif   // header guard
