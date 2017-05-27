#ifndef SN_TYPES_HPP
#define SN_TYPES_HPP
 
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

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
///   Contains the basic type typedefs and typecast functions for the framework. This header file may well be included by almost every other
///   header file in the framework.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Basic types for the framework
//////////////////////////////////

/** This struct is a placeholder for the empty template parameter. */
struct NullType {};

/** This typedef identifies the full floating point precision basic data type. */
using real_t         = double;

/** This typedef identifies the single precision floating point data type. */
using single_t       = float;

/** This convenience typedef identifies an immutable instance of real_t  */
using const_real_t   = const double;

/** This convenience typedef identifies an immutable instance of single_t  */
using const_single_t = const float;



/** This typedef identifies the smallest data type. */
using byte_t        = char;

/** This typedef identifies the smallest unsigned integral data type. */
using uint_t        = unsigned int;

/** This typedef identifies a basic data type for small container sizes. */
using small_t       = unsigned int;

/** This typedef identifies a basic data type for large container sizes. */
using large_t       = unsigned long;

/** This typedef identifies a basic data type intended for use with IDs and handles. */
using ID_t          = unsigned long;

/** This convenience typedef identifies an immutable instance of byte_t. */
using const_byte_t  = const unsigned int;

/** This convenience typedef identifies an immutable instance of small_t. */
using const_small_t = const unsigned int;

/** This convenience typedef identifies an immutable instance of large_t. */
using const_large_t = const unsigned long;

/** This convenience typedef identifies an immutable instance of ID_t. */
using const_ID_t    = const unsigned long;



// Other
/** This typedef identifies a basic string data type for common use in the framework. */
using string_t       = std::string;

/** This convenience typedef identifies an immutable instance of string_t. */
using const_string_t = const std::string;

/** This typedef is synonymous for bool and may help improve readability. */
using flag_t         = bool;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Casts for the framework
////////////////////////////

/** This function performs an up-cast i.e., it casts a pointer to an instance of a derived class to that of a base class. */
template< class CLS1, class CLS2 >
CLS1* SN_UP_CAST( CLS2* p ) { return p; }

/** This function performs an down-cast i.e., it casts a pointer to an instance of a base class to that of a derived class. */
template< class CLS1, class CLS2 >
CLS1* SN_DOWN_CAST( CLS2* p ) { return static_cast<CLS1*>(p); }



/** This macro casts the argument to real_t.
*   \param X   The instance to be cast to real_t
*/
#define real_cast(X)     static_cast< real_t >(X)

/** This macro casts the argument to single_t.
*   \param X   The instance to be cast to single_t
*/
#define single_cast(X)   static_cast< single_t >(X)

/** This macro casts the argument to byte_t.
*   \param X   The instance to be cast to byte_t
*/
#define byte_cast(X)     static_cast< char >(X)

/** This macro casts the argument to signed int.
*   \param X   The instance to be cast to signed int.
*/
#define int_cast(X)      static_cast< int >(X)

/** This macro casts the argument to unsigned int.
*   \param X   The instance to be cast to unsigned int
*/
#define uint_cast(X)     static_cast< uint_t >(X)

/** This macro casts the argument to small_t.
*   \param X   The instance to be cast to small_t
*/
#define small_cast(X)    static_cast< small_t >(X)

/** This macro casts the argument to large_t.
*   \param X   The instance to be cast to large_t
*/
#define large_cast(X)    static_cast< large_t >(X)

/** This macro casts the argument to ID_t.
*   \param X   The instance to be cast to ID_t
*/
#define ID_cast(X)       static_cast< ID_t >(X)

/** This macro casts the argument to string_t.
*   \param X   The instance to be cast to string_t
*/
#define string_cast(X)   static_cast< string_t >(X)

/** This macro casts the argument to flag_t.
*   \param X   The instance to be cast to flag_t
*/
#define flag_cast(X)     static_cast< flag_t >(X)

}   // namespace simpleNewton

#endif
