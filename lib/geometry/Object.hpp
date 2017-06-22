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

/** This typedef identifies handles to physical objects. */
using Object_ID_t = ID_t;

//===CLASS==================================================================================================================================

/** This class provides the base for every geometric object representable in a World. */
//==========================================================================================================================================

template< typename TYPE_T >
class Object : private NonCopyable {

public:   
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Default trivial constructor. */
   Object() = default;
   
   /** Default move constructor. */
   Object( Object && ) = default;
   
   /** Pure virtual destructor. The abstract object cannot be instantiated. */
   virtual ~Object() = 0;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to obtain the handle of the object within a world.
   *
   *   \return   The handle to the object, which grants the world containing it access to it.
   */
   inline Object_ID_t getHandle() const { return handle_; }

   /** @} */

protected:
   
   Object_ID_t handle_ = {};
};

}   // namespace simpleNewton

#endif
