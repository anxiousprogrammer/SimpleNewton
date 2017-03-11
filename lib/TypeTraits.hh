#pragma once

namespace simpleNewton {
namespace types {

/**//***************************************************************************************************************************************
*
*   Description: TypeTraits implementation for the simpleNewton framework. Gentle reminder - this is all compile time.
*
/***************************************************************************************************************************************///+

// Declaration
template< class TYPE > struct AssertIntBased;

// Specialization
template<> struct AssertIntBased<int> { enum : bool { result = true }; };

}   // namespace simpleNewton
}   // namespace types

// Global Function
template< class TYPE > inline void SN_ASSERT_INT_BASED( TYPE var ) {
   if( !simpleNewton::types::AssertIntBased<TYPE>::result ) {
      std::cerr << "Type-based static assert failed - File:Line: " << __FILE__ << ":" << __LINE__ << ":" << std::endl;
      std::abort();
   }
}
