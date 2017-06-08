#ifndef SN_FIELD_HPP
#define SN_FIELD_HPP

#include <algorithm>
#include <utility>

#include <Types.hpp>
#include <BasicBases.hpp>

#include <asserts/Asserts.hpp>

#include "DArray.hpp"

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
///   Contains the class template Field, which serves as the push-back enabled, fast container for World. 
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** This class adds push-back and associated functionality to the dynamic array and can be used as a fast, large container in World.
*/
//==========================================================================================================================================

template< typename TYPE_T, small_t INIT_SIZE = 10000 >
class Field : private NonCopyable, public DArray<TYPE_T> {

public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Near-default trivial constructor */
   Field() : DArray<TYPE_T>( INIT_SIZE ) { size_ = 0; }

   /** Default move constructor */
   Field( Field && ) = default;
   
   /** Explicitly defined destructor */
   ~Field() {
   }
   
   /** @} */
   
   /** \name Utility
   *   @{
   */
   /** A function which adds an element at the end of the array */
   void pushBack( TYPE_T && _elem ) {
      
      if( size_ == capacity_ ) {
         
         capacity_ = capacity_ + size_ * factor_;

         try {
         
            auto new_data = createRAIIWrapper<TYPE_T>( capacity_ );
            std::copy( data_.raw_ptr(), data_.raw_ptr() + size_, new_data.raw_ptr() );
         
            data_ = std::move( new_data );
         }
         catch( const AllocError & ) {
            SN_THROW_ALLOC_ERROR();
         }
      }
      
      // Inserting and size update
      data_[ size_ ] = std::move( _elem );
      size_++;
   }
   
   /** A function which removes the element at the end of the array.
   *
   *   \return   The removed element.
   */
   TYPE_T popBack() {
      
      SN_ASSERT_INEQUAL( size_, uint_cast(0) );
      
      #ifdef NDEBUG
      if( size_ == 0 )
         SN_THROW_PRECONDITION_ERROR( "PREC_Popback_Size_Error" );
      #endif
      
      // Update size
      size_--;
      
      return data_[size_];
   }
   
   /** @} */

private:
   
   /** Ancestral visibility */
   using DArray<TYPE_T>::data_;
   using DArray<TYPE_T>::size_;
   
   small_t capacity_ = INIT_SIZE;
   small_t factor_ = 2;
};

}   // namespace simpleNewton

#endif
