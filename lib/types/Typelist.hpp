#ifndef SN_TYPELIST_HPP
#define SN_TYPELIST_HPP

#include <Types.hpp>
#include <BasicBases.hpp>


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
///   Contains the class template SN_CT_TYPELIST, which is the typelist for the framework.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace typelist {
namespace internal {

/* Operations on typelists */
// Calculate length
template< class... TYPES >
struct length;

// Is a type in the list?
template< class TYPE, class... TYPES >
struct is_in_list;

// Append typelist
template< class... ALL_TYPES >
struct append;

// Concatenate typelist
template< class TYPELIST, class... TYPES >
struct concatenate;

// Remove type from typelist
template< class REM_T, class... TYPES >
struct remove;

// Remove type from typelist
template< class... TYPES >
struct removeDuplicates;
/* End: operations on typelists */

}   // namespace internal
}   // namespace typelist

#endif   // DOXYSKIP

//===CLASS==================================================================================================================================

/** This class serves as the standard typelist for the framework.
*
*   \tparam TYPES   The parameter pack with all the types which are associated with the typelist.
*/
//==========================================================================================================================================

template< class... TYPES >
struct SN_CT_TYPELIST : private NonInstantiable {
   
   // ---'Function style' operations associated with typelist---
   
   /** An enumerator which gives the length of the typelist. */
   enum { getSize = typelist::internal::length< TYPES... >::result };
   
   /** A function to find out if a specific type is contained by the typelist.
   *
   *   \tparam TYPE   The type for which it is being checked if it is in the typelist.
   *   \return        True if TYPE is contained in the list.
   */
   template< class TYPE >
   static inline constexpr bool isInList() { return typelist::internal::is_in_list< TYPE, TYPES... >::result; }
   
   /** A typedef which constructs a new typelist by appending additional types to the typelist.
   *
   *   \tparam MORE_TYPES   Additional types which are to be appended to the typelist.
   */
   template< class... MORE_TYPES >
   using appendList = typename typelist::internal::append< TYPES..., MORE_TYPES... >::list;
   
   /** A typedef which constructs a new typelist by concatenating a typelist with this one.
   *
   *   \tparam TYPELIST   A typelist which is to be concatenated with this typelist.
   */
   template< class TYPELIST >
   using concatenateList = typename typelist::internal::concatenate< TYPELIST, TYPES... >::list;
   
   /** A typedef which constructs a new typelist by removing a type from this typelist.
   *
   *   \tparam REM_T   A type which has to be removed from this typelist.
   */
   template< class REM_T >
   using removeFromList = typename typelist::internal::remove< REM_T, TYPES... >::list;
   
   /** A typedef which constructs a new typelist by removing duplicate types from the typelist. */
   using removeDuplicates = typename typelist::internal::removeDuplicates< TYPES... >::list;
};

}   // namespace simpleNewton

#include "Typelist.impl.hpp"
#endif
