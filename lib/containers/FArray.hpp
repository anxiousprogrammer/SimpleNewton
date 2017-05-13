#ifndef FARRAY_HPP
#define FARRAY_HPP

#include <algorithm>
#include <utility>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include "RAIIWrapper.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: The base classes of all fields and mathematical datatypes
*
|***************************************************************************************************************************************///+

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Basic container: can be large, small - whatever.
//////////////////////////////////////////////////////

template< typename TYPE_T, small_t SIZE >
class FArray {

public:

   /* Linear access */
   inline const TYPE_T & operator[]( small_t index ) const   { SN_ASSERT_INDEX_WITHIN_SIZE( index, SIZE ); return data_[index]; }
   
   /* Copy and move control */
   FArray<TYPE_T, SIZE> operator=( const TYPE_T & );
   FArray<TYPE_T, SIZE> operator=( const FArray<TYPE_T, SIZE> & );
   FArray<TYPE_T, SIZE> operator=( FArray<TYPE_T, SIZE> && );

   /* Birth and death */
   FArray() = default;
   explicit FArray( const TYPE_T & );
   FArray( const FArray<TYPE_T, SIZE> & );
   FArray( FArray<TYPE_T, SIZE> && ) = default;
   ~FArray() = default;
   
protected:
   
   /* Member */
   RAIIWrapper< TYPE_T > data_ = createRAIIWrapper< TYPE_T >( SIZE );
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   IMPLEMENTATION
////////////////////

// Non-trivial constructor(s)
template< class TYPE_T, small_t SIZE >
FArray< TYPE_T, SIZE > :: FArray( const TYPE_T & val ) {
   std::fill( data_.raw_ptr(), data_.raw_ptr() + SIZE, val );
}



// Copy constructor
template< class TYPE_T, small_t SIZE >
FArray<TYPE_T, SIZE> :: FArray( const FArray<TYPE_T, SIZE> & ref ) {
   std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + SIZE, data_.raw_ptr() );
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Copy and move control
///////////////////////////

// (Scalar) Copy control
template< class TYPE_T, small_t SIZE >
FArray<TYPE_T, SIZE> FArray<TYPE_T, SIZE> :: operator=( const TYPE_T & ref ) {

   std::fill( data_.raw_ptr(), data_.raw_ptr() + SIZE, ref );
   return *this;
}



// Copy control
template< class TYPE_T, small_t SIZE >
FArray<TYPE_T, SIZE> FArray<TYPE_T, SIZE> :: operator=( const FArray<TYPE_T, SIZE> & ref ) {

   std::copy( ref.data_.raw_ptr(), ref.data_.raw_ptr() + SIZE, data_.raw_ptr() );
   return *this;
}



// Move control
template< class TYPE_T, small_t SIZE >
FArray<TYPE_T, SIZE> FArray<TYPE_T, SIZE> :: operator=( FArray<TYPE_T, SIZE> && ref ) {

   if( this != &ref ) {
      data_ = std::move(ref.data_);
   }
   return *this;
}

}   // namespace simpleNewton

#endif
