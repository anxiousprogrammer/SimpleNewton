#include <Asserts.hh>
#include <iostream>

/**//****************************************************************************************************************************************
*
*   Description: 
*
/****************************************************************************************************************************************///+

namespace simpleNewton {
namespace asserts {

void errorMessage( const char * const msg, const char * const file, int line ) {
   std::cerr << msg << " => From here: " << file << ":" << line << ":\n" << std::endl;
}

}   // namespace asserts
}   // namespace simpleNewton
