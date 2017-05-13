#include "MPIRequest.hpp"

/**||**************************************************************************************************************************************
*
*   Description: Explicit instantiation of MPIRequest
*
|**************************************************************************************************************************************///+

namespace simpleNewton {

template<> class MPIRequest< char >;
template<> class MPIRequest< unsigned char >;

template<> class MPIRequest< short >;
template<> class MPIRequest< unsigned short >;

template<> class MPIRequest< int >;
template<> class MPIRequest< unsigned int >;

template<> class MPIRequest< long >;
template<> class MPIRequest< unsigned long >;

template<> class MPIRequest< long long >;
template<> class MPIRequest< unsigned long long >;

template<> class MPIRequest< float >;
template<> class MPIRequest< double >;

}   // namespace simpleNewton
