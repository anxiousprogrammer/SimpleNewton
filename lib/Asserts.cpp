#include <Asserts.hpp>
#include <iostream>

/**||****************************************************************************************************************************************
*
*   Description: 
*
|****************************************************************************************************************************************///+

namespace simpleNewton {
namespace asserts {
namespace impl {

void errorMessage( const char * const msg, const char * const file, int line ) {
   std::cerr << msg << " => From here: " << file << ":" << line << ":\n" << std::endl;
}

}   // namespace impl
}   // namespace asserts
}   // namespace simpleNewton
