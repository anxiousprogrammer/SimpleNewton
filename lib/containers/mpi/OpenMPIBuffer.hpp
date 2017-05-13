#ifndef OPENMPIBUFFER_HPP
#define OPENMPIBUFFER_HPP

#include <logger/Logger.hpp>
#include <containers/DArray.hpp>

namespace simpleNewton {

/**||**************************************************************************************************************************************
*
*   Description: An un-encapsulated RAII wrapper for MPI communication purposes, among others.
*
|**************************************************************************************************************************************///+

template< typename TYPE_T >
class OpenMPIBuffer : public DArray< TYPE_T > {

private:
   
   /* Ancestral visibility */
   using DArray<TYPE_T>::data_;
   using DArray<TYPE_T>::size_;
   
   small_t cptr_length( const TYPE_T * );
   
public:

   /* Deliberate breach of encapsulation */
   inline operator TYPE_T*()               { return DArray< TYPE_T >::data_; }
   inline operator const TYPE_T*() const   { return DArray< TYPE_T >::data_; }
   
   /* Birth and death */
   OpenMPIBuffer() = delete;
   OpenMPIBuffer( const TYPE_T * );
   OpenMPIBuffer( small_t , const TYPE_T & = TYPE_T() );
   
   /* Concatenation */
   OpenMPIBuffer operator+( const OpenMPIBuffer & );
   
   /* Logger compatibility */
   template< typename T >
   friend Logger & operator<<( Logger & , const OpenMPIBuffer<T> & );
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   IMPLEMENTATION
////////////////////


// Private Helper
template< typename TYPE_T >
small_t OpenMPIBuffer<TYPE_T>::cptr_length( const TYPE_T * ptr ) {
   
   small_t size = 0;
   while( ptr[size] != TYPE_T() )
      size++;
   return size;
}



// Primary, non-trivial constructor
template< typename TYPE_T >
OpenMPIBuffer<TYPE_T>::OpenMPIBuffer( small_t size, const TYPE_T & val ) : DArray<TYPE_T>( size, val ) {}



// Secondary constructor
template< typename TYPE_T >
OpenMPIBuffer<TYPE_T>::OpenMPIBuffer( const TYPE_T * arr ) : DArray<TYPE_T>( cptr_length( arr ) ) {
   std::copy( arr, arr + size_, data_.raw_ptr() );
}



// Concatenation may be useful
template< typename TYPE_T >
OpenMPIBuffer<TYPE_T> OpenMPIBuffer<TYPE_T>::operator+( const OpenMPIBuffer<TYPE_T> & operand ) {
   
   OpenMPIBuffer<TYPE_T> newOMPIB( size_ + operand.size_ );

   std::copy( data_.raw_ptr(), data_.raw_ptr() + size_, newOMPIB.data_.raw_ptr() );
   std::copy( operand.data_.raw_ptr(), operand.data_.raw_ptr() + operand.size_, newOMPIB.data_.raw_ptr() + size_ );
   
   return newOMPIB;
}



// Logger requires a friend
template< typename T >
Logger & operator<<( Logger & lg, const OpenMPIBuffer<T> & buff ) {
   
   lg << std::string( buff );
   return lg;
}

}   // namespace simpleNewton

#endif
