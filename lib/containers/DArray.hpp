#ifndef DARRAY_HPP
#define DARRAY_HPP

#include <algorithm>
#include <utility>

#include <Types.hpp>
#include <asserts/Asserts.hpp>

#include "RAIIWrapper.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: The base class of all dynamic, access free (!!) arrays
*
|***************************************************************************************************************************************///+

template< typename TYPE_T >
class DArray {

public:

   /* Linear access */
   inline const TYPE_T & operator[]( small_t index ) const   { SN_ASSERT_INDEX_WITHIN_SIZE( index, size_ ); return data_[index]; }
   inline small_t getSize() const                            { return size_; }
   
   /* Helper functions */
   void resize( small_t );
   void fill( const TYPE_T & );
   
   /* Copy and move control */
   DArray<TYPE_T> operator=( const TYPE_T & );
   DArray<TYPE_T> operator=( const DArray<TYPE_T> & );
   DArray<TYPE_T> operator=( DArray<TYPE_T> && );

   /* Birth and death */
   DArray() = delete;
   DArray( small_t size, const TYPE_T & val = TYPE_T() );
   DArray( const DArray<TYPE_T> & );
   DArray( DArray<TYPE_T> && ) = default;
   ~DArray() = default;
   
protected:

   /* Members */
   RAIIWrapper< TYPE_T > data_;
   small_t size_ = 0;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Implementation
////////////////////

// Non-trivial constructor(s)
template< class TYPE_T >
DArray< TYPE_T > :: DArray( small_t size, const TYPE_T & val ) : data_( createRAIIWrapper<TYPE_T>( size ) ) {

   size_ = size;
   std::fill( data_.raw_ptr(), data_.raw_ptr() + size, val );
}



// Copy constructor
template< class TYPE_T >
DArray< TYPE_T > :: DArray( const DArray< TYPE_T > & ref ) : data_( createRAIIWrapper<TYPE_T>( ref.size_ ) ), size_(ref.size_) {
   std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + ref.size_, data_.raw_ptr() );
}



// Resizing the array
template< class TYPE_T >
void DArray<TYPE_T>::resize( small_t new_size ) {
   
   size_ = new_size;
   data_ = createRAIIWrapper< TYPE_T >( size_ );
}



// Filling the array
template< class TYPE_T >
void DArray<TYPE_T>::fill( const TYPE_T & val ) {
   std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, val );
}



// (Scalar) Copy control
template< class TYPE_T >
DArray< TYPE_T > DArray< TYPE_T > :: operator=( const TYPE_T & ref ) {

   std::fill( data_.raw_ptr(), data_.raw_ptr() + size_, ref );
   return *this;
}



// Copy control
template< class TYPE_T >
DArray< TYPE_T > DArray< TYPE_T > :: operator=( const DArray< TYPE_T > & ref ) {

   if( size_ != ref.size_ ) {
   
      size_ = ref.size_;
      data_ = createRAIIWrapper<TYPE_T>( ref.size_ );
   }
   
   std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + ref.size_, data_.raw_ptr() );
   return *this;
}



// Move control
template< class TYPE_T >
DArray< TYPE_T > DArray< TYPE_T > :: operator=( DArray< TYPE_T > && ref ) {

   if( this != &ref ) {
   
      data_ = std::move(ref.data_);
      size_ = std::move(ref.size_);
      
      ref.size_ = 0;
   }
   return *this;
}

}   // namespace simpleNewton

#endif
