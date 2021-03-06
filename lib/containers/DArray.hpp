#ifndef SN_DARRAY_HPP
#define SN_DARRAY_HPP

#include <algorithm>
#include <utility>

#include <Types.hpp>
#include <asserts/Asserts.hpp>

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
///   Contains the class template DArray, which serves as the base class for every dynamic resource allocated array.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** This class serves as the base class for all dynamic resource allocated arrays. DArray is recommended as a large sized data container.
*
*   \tparam TYPE_T   The underlying data type of the array.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class DArray {

public:

   /** \name Constructors and Destructor
   *   @{
   */
   /** Trivial constructor is deleted. */
   DArray() = delete;
   
   /** Direct initialization: constructor which takes a size and a default value.
   *
   *   \param size   The desired size of the DArray.
   *   \param val    The default value with which to initialize the DArray.
   */
   DArray( large_t size, const TYPE_T & val = {} ) : data_( createRAIIWrapper<TYPE_T>( size ) ) {

      SN_ASSERT_POSITIVE( size );
      
      size_ = size;
      
      std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, val );
   }
   
   /** Copy constructor is explicitly defined.
   *
   *   \param ref   The prvalue reference from which to copy data while constructing the new DArray.
   */
   DArray( const DArray<TYPE_T> & ref ) : data_( createRAIIWrapper<TYPE_T>( ref.size_ ) ), size_(ref.size_) {
      std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + ref.size_, data_.raw_ptr() );
   }
   
   /** Default move constructor. */
   DArray( DArray<TYPE_T> && ) = default;
   
   /** Default destructor. */
   ~DArray() = default;

   /** @} */
   
   
   
   /** \name Access
   *   @{
   */
   /** Operator (const): primary access function.
   *
   *   \param index   An index to access elements of the DArray.
   *   \return        A const qualified reference to the element.
   */
   inline const TYPE_T & operator[]( large_t index ) const {
      
      SN_ASSERT_INDEX_WITHIN_SIZE( index, size_ );
      
      return data_[index];
   }
   
   /** A function to get the size of the DArray.
   *
   *   \return   The size of the array.
   */
   inline large_t getSize() const        { return size_; }
   
   /** A function which returns an iterator to the head of the array. 
   *
   *   \return   A const type qualified pointer to the head of the array.
   */
   inline const TYPE_T * begin() const   { return &data_[0]; }
   
   /** A function which returns an iterator to the tail of the array. 
   *
   *   \return   A const type qualified pointer to the tail of the array.
   */
   inline const TYPE_T * end() const     { return &data_[size_-1]; }
   
   /** @} */
   
   /** \name Utility
   *   @{
   */
   /** A function to resize the DArray. Notes on exception safety: strong safety guaranteed. An instance of AllocError or AllocSizeError
   *   will be thrown if there resource allocation were not possible.
   *
   *   \param new_size   The new size with which it is desired to resize the DArray.
   */
   void resize( large_t new_size ) {
   
      SN_ASSERT_POSITIVE( new_size );
      
      size_ = new_size;
      data_ = createRAIIWrapper< TYPE_T >( size_ );
      
      std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, TYPE_T() );
   }
   
   /** A function to fill the DArray with a specified value.
   *
   *   \param val   The value with which to fill the DArray.
   */
   void fill( const TYPE_T & val ) {
      std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, val );
   }
   
   /** A function to ascertain if the DArray is empty i.e., containing elements having only TYPE_T() value.
   *
   *   \return true if the DArray is empty, false if not.
   */
   bool isEmpty() {
   
      bool ret_val = true;   // optimistic approach
      for( large_t i = 0; i < size_; ++i ) {
      
         if( data_[i] != TYPE_T() )
            ret_val = false;   // Disillusionment!
      }
      return ret_val;
   }
   
   /** @} */
   
   /** \name Assignment control
   *   @{
   */
   /** Copy control for scalar reference value. 
   *
   *   \param ref   A value with which the DArray will be populated.
   *   \return      A new DArray upon assignment.
   */
   DArray<TYPE_T> operator=( const TYPE_T & ref ) {
      
      std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, ref );
      
      return *this;
   }
   
   /** Copy control for DArray reference value. If the sizes of the two containers are not equal, the assigned DArray shall resize itself
   *   appropriately before the copying.
   *
   *   \param ref   A reference DArray with which the DArray will be populated.
   *   \return      A new DArray upon assignment.
   */
   DArray<TYPE_T> operator=( const DArray<TYPE_T> & ref ) {

      if( size_ != ref.size_ ) {
   
         size_ = ref.size_;
         data_ = createRAIIWrapper<TYPE_T>( ref.size_ );
      }
      
      std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + ref.size_, data_.raw_ptr() );

      return *this;
   }
   
   /** Move control for DArray rvalue.
   *
   *   \param ref   An rvalue DArray from which the data shall be assigned to the DArray object.
   *   \return      A new DArray upon assignment.
   */
   void operator=( DArray<TYPE_T> && ref ) {

      if( this != &ref ) {
   
         data_ = std::move(ref.data_);
         size_ = ref.size_;
         ref.size_ = 0;
      }
   }
   
   /** @} */
   
protected:

   /* Members */
   RAIIWrapper< TYPE_T > data_;   ///< Basic data member. Packed in an RAIIWrapper.
   large_t size_ = 0;             ///< The size data member.
};

}   // namespace simpleNewton

#endif
