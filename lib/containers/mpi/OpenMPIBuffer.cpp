#include "OpenMPIBuffer.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: cpp for compilation ease
*
|***************************************************************************************************************************************///+

template class OpenMPIBuffer< char >;
template class OpenMPIBuffer< unsigned char >;
template class OpenMPIBuffer< int >;
template class OpenMPIBuffer< unsigned int >;
template class OpenMPIBuffer< long >;
template class OpenMPIBuffer< unsigned long >;
template class OpenMPIBuffer< long long >;
template class OpenMPIBuffer< unsigned long long >;
template class OpenMPIBuffer< float >;
template class OpenMPIBuffer< double >;

}   // namespace simpleNewton
