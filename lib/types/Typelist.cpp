#include "Typelist.hpp"

namespace simpleNewton {

/**|||**************************************************************************************************************************************
*
*   Description: Explicit instantiation, forming a compiling unit
*
|***************************************************************************************************************************************///+

template struct SN_CT_TYPELIST< char, int, unsigned int, short, unsigned short, long, unsigned long, long long, unsigned long long >;
template struct SN_CT_TYPELIST< float, double >;

}   // namespace simpleNewton
