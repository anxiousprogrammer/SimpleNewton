#ifndef BASICTYPENAMESTR_HPP
#define BASICTYPENAMESTR_HPP

#include "Types.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Returns a string of typename. Implementation is primitive and allows for only basic types.
*
|***************************************************************************************************************************************///+


// Declaration
template< typename T > string_t SN_BASIC_TYPENAME_STR()   { return "_NOT_KNOWN_"; }

// Specializations
template<> string_t SN_BASIC_TYPENAME_STR< char >()                 { return "char";                }
template<> string_t SN_BASIC_TYPENAME_STR< bool >()                 { return "bool";                }
template<> string_t SN_BASIC_TYPENAME_STR< int >()                  { return "int";                 }
template<> string_t SN_BASIC_TYPENAME_STR< float >()                { return "float";               }
template<> string_t SN_BASIC_TYPENAME_STR< double >()               { return "double";              }
template<> string_t SN_BASIC_TYPENAME_STR< unsigned int >()         { return "unsigned int";        }
template<> string_t SN_BASIC_TYPENAME_STR< unsigned long >()        { return "unsigned long";       }
template<> string_t SN_BASIC_TYPENAME_STR< unsigned long long >()   { return "unsigned long long";  }
template<> string_t SN_BASIC_TYPENAME_STR< std::string >()          { return "std::string";         }

}   // namespace simpleNewton

#endif
