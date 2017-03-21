#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP 

#include <Types.hpp>
#include <BasicTypeTraits.hpp>

/**||***************************************************************************************************************************************
*
*   Description: Inheritance control - derived from, derived from (strict), not derived from, not derived from (strict)
*
|***************************************************************************************************************************************///+

namespace simpleNewton {
namespace types {

// Compile time constraint that template parameter DERIVED must be derived from BASE
template< class DERIVED, class BASE >
struct Assert_Derived_From_Failed { 
   operator DERIVED*()   { return nullptr; }
   static void AssertDerivedFromFailed( BASE* ) {}
};


// Compile time constraint that template parameter DERIVED must be derived from BASE. Additionally DERIVED != BASE.
template< class DERIVED, class BASE >
struct Assert_Strictly_Derived_From_Failed { 
   operator DERIVED*()   { return nullptr; }
   static void AssertStrictlyDerivedFromFailed( BASE* ) {}
};
template< class CLS > struct Assert_Strictly_Derived_From_Failed< CLS, CLS > {
   static void TEMPLATE_ARGUMENTS_ARE_SAME_CLASS( int );
   operator CLS*()   { return nullptr; }
   static void AssertStrictlyDerivedFromFailed( CLS* ) { TEMPLATE_ARGUMENTS_ARE_SAME_CLASS(); }
};


// Compile time constraint that template parameter DERIVED must not be derived from BASE
template< class DERIVED, class BASE >
struct Assert_Not_Derived_From_Failed {
   
   static void AssertFailed( int );
   operator DERIVED*() const  { return nullptr; }
   operator int()             { return true; }

   template< class OTHER > static void AssertNotDerivedFromFailed( int, OTHER ) {}
   static void AssertNotDerivedFromFailed( BASE*, int ) { AssertFailed(); }
};


// Compile time constraint that template parameter DERIVED must not be derived from BASE. Additionally DERIVED != BASE.
template< class DERIVED, class BASE >
struct Assert_Strictly_Not_Derived_From_Failed {
   
   static void AssertFailed( int );
   operator DERIVED*() const  { return nullptr; }
   operator int()             { return true; }

   template< class OTHER > static void AssertStrictlyNotDerivedFromFailed( int, OTHER ) {}
   static void AssertStrictlyNotDerivedFromFailed( BASE*, int ) { AssertFailed(); }
};
template< class CLS > struct Assert_Strictly_Not_Derived_From_Failed< CLS, CLS > {
   static void TEMPLATE_ARGUMENTS_ARE_SAME_CLASS( int );
   operator CLS*() const   { return nullptr; }
   static void AssertStrictlyNotDerivedFromFailed( CLS*, int ) { TEMPLATE_ARGUMENTS_ARE_SAME_CLASS(); } 
};

}   // namespace types
}   // namespace simpleNewton

#ifdef NDEBUG

#define SN_CT_ASSERT_DERIVED_FROM( DER, BASE )
#define SN_CT_ASSERT_STRICTLY_DERIVED_FROM( DER, BASE )
#define SN_CT_ASSERT_NOT_DERIVED_FROM( DER, BASE )
#define SN_CT_ASSERT_STRICTLY_NOT_DERIVED_FROM( DER, BASE )

#else

#define SN_CT_ASSERT_DERIVED_FROM( DER, BASE ) \
   do { simpleNewton::types::Assert_Derived_From_Failed<DER, BASE>::AssertDerivedFromFailed( simpleNewton::types::Assert_Derived_From_Failed<DER, BASE>() ); } while(false)

#define SN_CT_ASSERT_STRICTLY_DERIVED_FROM( DER, BASE ) \
   do { simpleNewton::types::Assert_Strictly_Derived_From_Failed<DER, BASE>::AssertStrictlyDerivedFromFailed( simpleNewton::types::Assert_Strictly_Derived_From_Failed<DER, BASE>() ); } while(false)

#define SN_CT_ASSERT_NOT_DERIVED_FROM( DER, BASE ) \
   do { simpleNewton::types::Assert_Not_Derived_From_Failed<DER, BASE>::AssertNotDerivedFromFailed( simpleNewton::types::Assert_Not_Derived_From_Failed<DER, BASE>(), int() ); } while(false)

#define SN_CT_ASSERT_STRICTLY_NOT_DERIVED_FROM( DER, BASE ) \
   do { simpleNewton::types::Assert_Strictly_Not_Derived_From_Failed<DER, BASE>::AssertStrictlyNotDerivedFromFailed( simpleNewton::types::Assert_Strictly_Not_Derived_From_Failed<DER, BASE>(), int() ); } while(false)

#endif   // NDEBUG 

#endif
