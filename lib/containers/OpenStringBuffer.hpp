#ifndef OPENSTRINGBUFFER_HPP
#define OPENSTRINGBUFFER_HPP

#include <logger/Logger.hpp>
#include "DArray.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: An un-encapsulated RAII wrapper for MPI communication purposes, among others.
*
|***************************************************************************************************************************************///+

class OpenStringBuffer : public DArray< char > {

private:
   
   small_t cptr_length( const char * );
   
public:
   
   /* Birth and death */
   OpenStringBuffer() = delete;
   OpenStringBuffer( small_t , char = char() );
   OpenStringBuffer( const char * );
   OpenStringBuffer( const OpenStringBuffer & ) = default;
   OpenStringBuffer( OpenStringBuffer && ) = default;
   ~OpenStringBuffer() = default;
   
   /* Concatenation */
   OpenStringBuffer operator+( const OpenStringBuffer & );
};

}   // namespace simpleNewton

#endif
