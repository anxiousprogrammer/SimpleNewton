#ifndef SN_OBJECT_HPP
#define SN_OBJECT_HPP

#include <algorithm>
#include <vector>

#include <Types.hpp>
#include <BasicBases.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <logger/Logger.hpp>
#include <core/Exceptions.hpp>

#include <containers/Vector3.hpp>
#include <containers/Matrix3.hpp>

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
///   Contains the class Object, which represents any geometric object representable in a World.
///   \file
///   \addtogroup geometry Geometry
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** This class provides the base for every geometric object representable in a World. */
//==========================================================================================================================================

template< typename TYPE_T >
class Object : private NonCopyable {

public:   
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Deleted trivial constructor. */
   Object() = delete;
   
   /** Direct initialization constructor in which the arguments are moved into the members. */
   Object( Vector3<TYPE_T> && _c, Vector3<TYPE_T> && _v, Vector3<TYPE_T> && _a ) : center_( std::move(_c) ),
                                                                                   velocity_( std::move(_v) ),
                                                                                   acceleration_( std::move(_a) ) {}
   
   /** Direct initialization constructor in which the arguments are copied into the members. */
   Object( const Vector3<TYPE_T> & _c, const Vector3<TYPE_T> & _v, const Vector3<TYPE_T> & _a ) : center_(_c), 
                                                                                                  velocity_(_v),
                                                                                                  acceleration_(_a) {}
   
   /** Default move constructor. */
   Object( Object && ) = default;
   
   /** Default destructor. */
   virtual ~Object() = 0;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to get the global position of the object. */
   const Vector3<TYPE_T> & getCentre() const         { return center_; }
   
   /** A function to get the global velocity of the object. */
   const Vector3<TYPE_T> & getVelocity() const       { return velocity_; }
   
   /** A function to get the global acceleration of the object. */
   const Vector3<TYPE_T> & getAcceleration() const   { return acceleration_; }
   
   /** @} */

protected:
   
   Vector3<TYPE_T> center_;
   Vector3<TYPE_T> velocity_;
   Vector3<TYPE_T> acceleration_;
};

}   // namespace simpleNewton

#endif
