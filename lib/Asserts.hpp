#ifndef ASSERTS_HPP
#define ASSERTS_HPP

#include <cstdlib>
#include <cmath>
#include <GlobalConstants.hpp>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Run time asserts - equal, inequal, less-than, less-than-or-equal-to, greater-than, greater-than-or-equal-to, 
*
*   equal-to-zero, is positive and is negative.
*
|***************************************************************************************************************************************///+

namespace asserts {
namespace impl {

// Error trigger
template< bool expr > struct TYPE_ERROR;
template<> struct TYPE_ERROR<true>  { enum : bool { ASSERT_FAILED = false }; };
template<> struct TYPE_ERROR<false> {};

// Type or no game
template< class T1, class T2 > struct SAME_TYPE_IN_ASSERT                      { enum : bool { value = false }; };
template< class SAME_TYPE > struct SAME_TYPE_IN_ASSERT< SAME_TYPE, SAME_TYPE > { enum : bool { value = true  }; };

template< class U_INT > struct INT_IN_ASSERT          { enum : bool { value = false }; };
template<> struct INT_IN_ASSERT< short >              { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< int >                { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< long >               { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< long long >          { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< unsigned short >     { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< unsigned int >       { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< unsigned long >      { enum : bool { value = true }; };
template<> struct INT_IN_ASSERT< unsigned long long > { enum : bool { value = true }; };

/* Declaration: errorMessage is a function for generic errors */
void errorMessage( const char * const msg, const char * const file, int line );

template< bool constexpr_expr > 
inline void assert( const char * const file, int line ) {
   if( ! constexpr_expr ) {
      asserts::impl::errorMessage( "Assertion failed - ", file, line );
      std::abort();
   }
}



template< class T1, class T2 > 
inline void assert_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) == static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Equality assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 > 
inline void assert_fp_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) <= globalConstants::ZERO ) ) {
         asserts::impl::errorMessage( "Floating point equality assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) != static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Inequality assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_fp_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) > globalConstants::ZERO ) ) {
         asserts::impl::errorMessage( "Floating point inequality assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_less_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) < static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Less than assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_leq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) <= static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Less than or equal to assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_greater_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) > static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Greater than assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class T1, class T2 >
inline void assert_greq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) >= static_cast<T1>(REFERENCE) ) ) {
         asserts::impl::errorMessage( "Greater than or equal to assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< class TYPE >
inline void assert_zero( const TYPE & VALUE, const char * const file, int line ) {
   if( !static_cast< bool >( std::fabs(VALUE) <= globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Equal to zero assertion failed - ", file, line );
      std::abort();
   }
}



template< class TYPE >
inline void assert_positive( const TYPE & VALUE, const char * const file, int line ) {
   if( !static_cast< bool >( VALUE > globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Positivity assertion failed - ", file, line );
      std::abort();
   }
}



template< class TYPE >
inline void assert_negative( const TYPE & VALUE, const char * const file, int line ) {
   if( !static_cast< bool >( VALUE < globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Negativity assertion failed - ", file, line );
      std::abort();
   }
}



template< bool constexpr_expr >
inline void assert_msg( const char* const MSG, const char * const file, int line ) {
   if( !static_cast< bool >( constexpr_expr ) ) {
   asserts::impl::errorMessage( MSG, file, line );
   std::abort();
   }
}



template< typename U_INT >
inline void assert_size_same( const U_INT & SIZE, const U_INT & REF, const char * const file, int line ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) == static_cast<unsigned long long>(REF) ) ) {
         asserts::impl::errorMessage( "Same size assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< typename U_INT >
inline void assert_size_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) <= static_cast<unsigned long long>(REF) ) ) {
         asserts::impl::errorMessage( "Size less than assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< typename U_INT >
inline void assert_size_strictly_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) < static_cast<unsigned long long>(REF) ) ) {
         asserts::impl::errorMessage( "Size strictly less than assertion failed - ", file, line );
         std::abort();
      }
   }
}



template< typename U_INT >
inline void assert_index_within_size( const U_INT & IND, const U_INT & SIZE, const char * const file, int line ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(IND) < static_cast<unsigned long long>(SIZE) ) ) {
         asserts::impl::errorMessage( "Index within size assertion failed - ", file, line );
         std::abort();
      }
   }
}

}   // namespace impl
}   // namespace asserts

#ifdef NDEBUG

/* RT asserts*/

template< bool constexpr_expr > 
inline void SN_ASSERT() {}

template< class T1, class T2 > 
inline void SN_ASSERT_EQUAL( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_FP_EQUAL( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_INEQUAL( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_FP_INEQUAL( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_LESS_THAN( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_LEQ( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_GREATER_THAN( const T1 &, const T2 & ) {}

template< class T1, class T2 > 
inline void SN_ASSERT_GREQ( const T1 &, const T2 & ) {}

template< class TYPE > 
inline void SN_ASSERT_ZERO( const TYPE & ) {}

template< class TYPE > 
inline void SN_ASSERT_POSITIVE( const TYPE & ) {}

template< class TYPE > 
inline void SN_ASSERT_NEGATIVE( const TYPE & ) {}

template< bool constexpr_expr > 
inline void SN_ASSERT_MSG( const std::string & ) {}


template< typename U_INT >
inline void SN_ASSERT_SIZE_SAME( const U_INT &, const U_INT & ) {}

template< typename U_INT >
inline void SN_ASSERT_SIZE_LESS_THAN( const U_INT &, const U_INT & ) {}

template< typename U_INT >
inline void SN_ASSERT_SIZE_STRICTLY_LESS_THAN( const U_INT &, const U_INT & ) {}

template< typename U_INT >
inline void SN_ASSERT_INDEX_WITHIN_SIZE( const U_INT &, const U_INT & ) {}

#else



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Run-time like that!
/////////////////////////


#define SN_ASSERT( EXPR ) \
do { asserts::impl::assert< EXPR >( __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_EQUAL( VAL, REF ) \
do { asserts::impl::assert_equal( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_FP_EQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_equal( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_inequal( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_FP_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_inequal( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_LESS_THAN( VAL, REF ) \
do { asserts::impl::assert_less_than( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_LEQ( VAL, REF ) \
do { asserts::impl::assert_leq( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_GREATER_THAN( VAL, REF ) \
do { asserts::impl::assert_greater_than( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_GREQ( VAL, REF ) \
do { asserts::impl::assert_greq( VAL, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_ZERO( VAL ) \
do { asserts::impl::assert_zero( VAL, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_POSITIVE( VAL ) \
do { asserts::impl::assert_positive( VAL, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_NEGATIVE( VAL ) \
do { asserts::impl::assert_negative( VAL, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_MSG( EXPR, MSG ) \
do { asserts::impl::assert_msg< EXPR >( MSG, __FILE__, __LINE__ ); } while(false)


/* Run-time constraints related to container sizes */
#define SN_ASSERT_SIZE_SAME( SIZE, REF ) \
do { asserts::impl::assert_size_same( SIZE, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_SIZE_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_less_than( SIZE, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_strictly_less_than( SIZE, REF, __FILE__, __LINE__ ); } while(false)

#define SN_ASSERT_INDEX_WITHIN_SIZE( IND, REF ) \
do { asserts::impl::assert_index_within_size( IND, REF, __FILE__, __LINE__ ); } while(false)

#endif
   
}   // namespace SimpleNewton

#endif
