#ifndef SN_FARRAY_HPP
#define SN_FARRAY_HPP

#include <algorithm>
#include <utility>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include "RAIIWrapper.hpp"

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
///   Contains the class template FArray, which serves as the base class for every automatic resource allocated array.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//=== CLASS ================================================================================================================================

/** This class serves as the base class for all automatic resource allocated arrays. The size of the container is a compile time constant
*   therefore lending operations upon its members open to compiler optimizations such as loop unrolling, SIMD and such.
*
*   \tparam TYPE_T   The underlying data type of the array.
*   \tparam SIZE     The size of the FArray
*/
//==========================================================================================================================================

template< typename TYPE_T, small_t SIZE >
class FArray {

public:

   /** \name Constructors and Destructor
   *   @{
   */
   /** Default trivial constructor */
   FArray() = default;

   /** Copy constructor with scalar reference.
   *
   *   \param val   The value with which the FArray is to be initialized.
   */
   explicit FArray( const TYPE_T & val ) {
      
      try {
         std::fill( data_, data_ + SIZE, val );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
   }   
   
   /** Default copy constructor. */
   FArray( const FArray<TYPE_T, SIZE> & ) = default;
   
   /** Default move constructor. */
   FArray( FArray<TYPE_T, SIZE> && ) = default;
   
   /** Default destructor. */
   ~FArray() = default;
   
   /** @} */
   
   
   
   /** \name Access
   *   @{
   */
   /** Operator (const): element wise access.
   *
   *   \param index   The index with which to access the elements of the FArray.
   *   \return        A const reference to the element.
   */
   inline const TYPE_T & operator[]( small_t index ) const   { SN_ASSERT_INDEX_WITHIN_SIZE( index, SIZE ); return data_[index]; }
   
   /** Operator (non-const): element wise access.
   *
   *   \param index   The index with which to access the elements of the FArray.
   *   \return        A reference to the element.
   */
   inline TYPE_T & operator[]( small_t index )               { SN_ASSERT_INDEX_WITHIN_SIZE( index, SIZE ); return data_[index]; }
   
   /** @} */
   
   
   
   /** \name Assignment control
   *   @{
   */
   /** Copy control with scalar reference.
   *
   *   \param ref   The scalar value with which to populate the FArray.
   *   \return      An FArray upon assignment.
   */
   FArray<TYPE_T, SIZE> operator=( const TYPE_T & ref ) {
      
      try {
         std::fill( data_, data_ + SIZE, ref );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      return *this;
   }
   
   /** @} */
   
protected:
   
   /* Member */
   TYPE_T data_[SIZE];   ///< Basic data array.
};

}   // namespace simpleNewton

#endif
