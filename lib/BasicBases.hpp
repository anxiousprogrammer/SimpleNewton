#ifndef SN_BASICBASES_HPP
#define SN_BASICBASES_HPP

#include <Types.hpp>

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
///   Contains important classes which restrict the creation, lifecycle and destruction of those classes which derive from them.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** When a class inherits privately from this class, it cannot be constructed trivially, by copying or even by moving. */
//==========================================================================================================================================

class NonConstructible {

private:
   NonConstructible() = delete;
   NonConstructible( const NonConstructible & ) = delete;
   NonConstructible( NonConstructible && ) = delete;
   ~NonConstructible() = delete;
};



//===CLASS==================================================================================================================================

/** When a class inherits privately from this class, it cannot be instantiated. */
//==========================================================================================================================================

class NonInstantiable {
   virtual void cannot_create_an_instance() = 0;
};



//===CLASS==================================================================================================================================

/** When a class inherits privately from this class, it cannot be constructed publicly or by copying. However, it can be constructed from
*   within the class scope and can also be moved.
*/
//==========================================================================================================================================

class Singleton {

private:
   Singleton( const Singleton & ) = delete;   // Copying is not allowed.
   Singleton( Singleton && ) = default;       // Can be moved if that is required.

protected:
   Singleton() = default;    // Private inheritance == private creation.
   ~Singleton() = default;   // Born within, died within.
};



//===CLASS==================================================================================================================================

/** When a class inherits privately from this class, it cannot be copy constructed or copied after construction. */
//==========================================================================================================================================

class NonCopyable {

   NonCopyable( const NonCopyable & ) = delete;

protected:
   
   NonCopyable() = default;
   NonCopyable( NonCopyable && ) = default;
   ~NonCopyable() = default;
};



//===CLASS==================================================================================================================================

/** When a class inherits privately from this class, it cannot be move constructed or moved after construction. */
//==========================================================================================================================================

class NonMovable {

   NonMovable( NonMovable && ) = delete;

protected:
   NonMovable() = default;
   NonMovable( const NonMovable & ) = default;
   ~NonMovable() = default;
};

}   // namespace simpleNewton

#endif
