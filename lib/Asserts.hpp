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

/* Declaration: errorMessage is a function for generic errors */
void errorMessage( const char * const msg, const char * const file, int line );

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
inline void SN_ASSERT_MSG( const std:.string & ) {}


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


template< bool constexpr_expr > 
inline void SN_ASSERT() {
   if( !static_cast< bool >( constexpr_expr ) ) {
      asserts::impl::errorMessage( "Assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 > 
inline void SN_ASSERT_EQUAL( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE == REFERENCE ) ) {
      asserts::impl::errorMessage( "Equality assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 > 
inline void SN_ASSERT_FP_EQUAL( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) <= globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Floating point equality assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 >
inline void SN_ASSERT_INEQUAL( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE != REFERENCE ) ) {
      asserts::impl::errorMessage( "Inequality assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}


template< class T1, class T2 >
inline void SN_ASSERT_FP_INEQUAL( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) > globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Floating point inequality assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 >
inline void SN_ASSERT_LESS_THAN( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE < REFERENCE ) ) {
      asserts::impl::errorMessage( "Less than assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 >
inline void SN_ASSERT_LEQ( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE <= REFERENCE ) ) {
      asserts::impl::errorMessage( "Less than or equal to assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 >
inline void SN_ASSERT_GREATER_THAN( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE > REFERENCE ) ) {
      asserts::impl::errorMessage( "Greater than assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class T1, class T2 >
inline void SN_ASSERT_GREQ( const T1 & VALUE, const T2 & REFERENCE ) {
   if( !static_cast< bool >( VALUE >= REFERENCE ) ) {
      asserts::impl::errorMessage( "Greater than or equal to assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class TYPE >
inline void SN_ASSERT_ZERO( const TYPE & VALUE ) {
   if( !static_cast< bool >( std::fabs(VALUE) <= globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Equal to zero assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class TYPE >
inline void SN_ASSERT_POSITIVE( const TYPE & VALUE ) {
   if( !static_cast< bool >( VALUE > globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Positivity assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< class TYPE >
inline void SN_ASSERT_NEGATIVE( const TYPE & VALUE ) {
   if( !static_cast< bool >( VALUE < globalConstants::ZERO ) ) {
      asserts::impl::errorMessage( "Negativity assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< bool constexpr_expr >
inline void SN_ASSERT_MSG( const std::string & MSG ) {
   if( !static_cast< bool >( constexpr_expr ) ) {
      asserts::impl::errorMessage( static_cast<const char * const>(MSG.c_str()) , __FILE__, __LINE__ );
      std::abort();
   }
}



/* Run-time constraints related to container sizes */
template< typename U_INT >
inline void SN_ASSERT_SIZE_SAME( const U_INT & SIZE, const U_INT & REF ) {
   if( !static_cast< bool >( SIZE == REF ) ) {
      asserts::impl::errorMessage( "Same size assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< typename U_INT >
inline void SN_ASSERT_SIZE_LESS_THAN( const U_INT & SIZE, const U_INT & REF ) {
   if( !static_cast< bool >( SIZE <= REF ) ) {
      asserts::impl::errorMessage( "Size less than assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< typename U_INT >
inline void SN_ASSERT_SIZE_STRICTLY_LESS_THAN( const U_INT & SIZE, const U_INT & REF ) {
   if( !static_cast< bool >( SIZE < REF ) ) {
      asserts::impl::errorMessage( "Size strictly less than assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}



template< typename U_INT >
inline void SN_ASSERT_INDEX_WITHIN_SIZE( const U_INT & IND, const U_INT & SIZE ) {
   if( !static_cast< bool >( IND < SIZE ) ) {
      asserts::impl::errorMessage( "Index within size assertion failed - ", __FILE__, __LINE__ );
      std::abort();
   }
}

#endif
   
}   // namespace SimpleNewton

#endif
