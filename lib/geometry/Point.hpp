#ifndef SN_POINT_HPP
#define SN_POINT_HPP

#include <algorithm>
#include <vector>

#include <Types.hpp>

#include "Object.hpp"

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
///   Contains the class Point, which represents a single point in the World.
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
class Point : public Object<TYPE_T> {

private:

   using Object<TYPE_T>::center_;
   using Object<TYPE_T>::velocity_;
   using Object<TYPE_T>::acceleration_;

public:   
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Deleted trivial constructor. */
   Point() = delete;

   /** Direct initialization constructor in which the arguments are moved into the members. */
   Point( Vector3<TYPE_T> && _center, 
          Vector3<TYPE_T> && _vel = {},
          Vector3<TYPE_T> && _acc = {} ) : Object<TYPE_T>( std::move(_center), std::move(_vel), std::move(_acc) ) {}
   
   /** Default move constructor. */
   Point( Point && ) = default;
   
   /** Default destructor. */
   ~Point() = default;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to get the global position of the object. */
   
   /** @} */
};

}   // namespace simpleNewton

#endif
