#include <types/BasicTypeTraits.hpp>
#include "OpenStringBuffer.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Implementation of the OpenStringBuffer class.
*
|***************************************************************************************************************************************///+

// Private Helper
small_t OpenStringBuffer::cptr_length( const char * ptr ) {
   
   small_t size = 0;
   while( ptr[size] != char() )
      size++;
   return size;
}



// Primary, non-trivial constructor
OpenStringBuffer::OpenStringBuffer( small_t size, char val ) : DArray<char>( size, val ) {}



// Secondary constructor
OpenStringBuffer::OpenStringBuffer( const char * arr ) : DArray<char>( cptr_length( arr ) ) {
   std::copy( arr, arr + getSize(), getData() );
}



// Concatenation may be useful
OpenStringBuffer OpenStringBuffer::operator+( const OpenStringBuffer & operand ) {
   
   OpenStringBuffer newOSB( size_ + operand.size_ );

   std::copy( getData(), getData() + getSize(), newOSB.getData() );
   std::copy( operand.getData(), operand.getData() + operand.getSize(), newOSB.getData() + getSize() );
   
   return newOSB;
}

}   // namespace simpleNewton
