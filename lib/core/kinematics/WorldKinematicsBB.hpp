#ifndef SN_WORLDKINEMATICSBB_HPP
#define SN_WORLDKINEMATICSBB_HPP

#include <algorithm>
#include <vector>

#include <Types.hpp>
#include <BasicBases.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <containers/Field.hpp>
#include <containers/Vector3.hpp>

#include <core/Exceptions.hpp>

#include <geometry/Object.hpp>

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
///   Contains the class WorldKinematicsBB, which serves as the base class to World and is responsible for its kinematics.
///   \file
///   \addtogroup math Math
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template< typename FP_TYPE_T >
class WorldKinematicsBB : private NonCopyable, private NonMovable {

   /* A friend indeed! And for generations to come. */
   template< typename FP_T, class KINEMATICS_BB > friend class World;
   
   WorldKinematicsBB() { SN_CT_REQUIRE_FP_TYPE< FP_TYPE_T >(); }
   
public:

   /** This typedef identifies the floating point precision type being employed by the kinematics engine. */
   using precType = FP_TYPE_T;
   
   /** \name Constructors and destructor
   *   @{
   */
   /** A pure virtual destructor means this class cannot be instantiated and serves only as base class. */
   virtual ~WorldKinematicsBB() = 0;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to obtain the number of physical objects existing in the world.
   *
   *   \return   The number of physical objects.
   */
   large_t getSize() const   { return size_; }
   
   /** A function (const) to obtain the position of an object existing in the world. Notes on exception safety: strong safety 
   *   guaranteed. The function throws an OORError exception if the provided index is invalid.
   *
   *   \param handle   The handle which identifies the physical object.
   *   \return         The position vector of the physical object identified by the handle provided as argument.
   */
   const Vector3<FP_TYPE_T> & getPosition( Object_ID_t handle ) const {
      
      SN_ASSERT_INDEX_WITHIN_SIZE( handle, size_ );
      
      #ifdef NDEBUG
      if( handle >= size_ ) {
         SN_THROW_OOR_ERROR();
      }
      #endif
      
      return position_[ handle ];
   }
   
   /** A function (const) to obtain the velocity of an object existing in the world. Notes on exception safety: strong safety 
   *   guaranteed. The function throws an OORError exception if the provided index is invalid.
   *
   *   \param handle   The handle which identifies the physical object.
   *   \return         The velocity vector of the physical object identified by the handle provided as argument.
   */
   const Vector3<FP_TYPE_T> & getVelocity( Object_ID_t handle ) const {
      
      SN_ASSERT_INDEX_WITHIN_SIZE( handle, size_ );
      
      #ifdef NDEBUG
      if( handle >= size_ ) {
         SN_THROW_OOR_ERROR();
      }
      #endif
      
      return velocity_[ handle ];
   }

   /** A function (const) to obtain the acceleration of an object existing in the world. Notes on exception safety: strong safety 
   *   guaranteed. The function throws an OORError exception if the provided index is invalid.
   *
   *   \param handle   The handle which identifies the physical object.
   *   \return         The acceleration vector of the physical object identified by the handle provided as argument.
   */
   const Vector3<FP_TYPE_T> & getAcceleration( Object_ID_t handle ) const {
      
      SN_ASSERT_INDEX_WITHIN_SIZE( handle, size_ );
      
      #ifdef NDEBUG
      if( handle >= size_ ) {
         SN_THROW_OOR_ERROR();
      }
      #endif
      
      return acceleration_[ handle ];
   }
   
   /** A function which can be used to set the acceleration calculated by the response system. Notes on exception safety: strong safety 
   *   guaranteed. The function throws an OORError exception if the provided index is invalid.
   *
   *   \param _acc     The new acceleration value.
   *   \param handle   The handle to the object.
   */
   inline void setAcceleration( FP_TYPE_T _acc, Object_ID_t handle ) {
      
      SN_ASSERT_INDEX_WITHIN_SIZE( handle, size_ );
      
      #ifdef NDEBUG
      if( handle >= size_ ) {
         SN_THROW_OOR_ERROR();
      }
      #endif
      
      acceleration_[ handle ] = _acc;
   }
   
   /** @} */
   
   /** \name Primary functionality
   *   @{
   */

   /** A pure virtual function which should allocate field resources for a new object.
   *
   *   \return   A handle to the newly created object
   */
   virtual Object_ID_t createObject() = 0;

   /** A pure virtual function which requires all base classes to implement a method of kinematic integration. */   
   virtual void integrate() = 0;
   
   /** @} */

protected:
   
   /** A variable which records the starting time */
   FP_TYPE_T startTime_ = {};
   
   /** A variable which records the current time */
   FP_TYPE_T currentTime_ = {};
   
   /** A variable which records the current time-step */
   FP_TYPE_T timeStep_ = {};
   
   /** A field of position vectors of physical objects existing in the world. */
   Field< Vector3< FP_TYPE_T > > position_ = {};
   
   /** A field of velocity vectors of physical objects existing in the world. */
   Field< Vector3< FP_TYPE_T > > velocity_ = {};
   
   /** A field of acceleration variables of physical objects existing in the world. */
   Field< Vector3< FP_TYPE_T > > acceleration_ = {};
   
   /** The size of physical objects in the world. */
   large_t size_;
};

}   // namespace simpleNewton

#endif
