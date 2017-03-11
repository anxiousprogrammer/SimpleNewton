#pragma once

#include <cstdlib>
#include <cmath>
#include "GlobalConstants.hh"

namespace simpleNewton {
namespace asserts {

/**//***************************************************************************************************************************************
*
*   Description: Compile and run time asserts - equal, inequal, less than, less than or equal to, greater than, greater than or equal to, 
*
*   equal to zero, is positive and is negative.
*
/***************************************************************************************************************************************///+

/* Declaration: errorMessage is a function for generic errors */
void errorMessage( const char * const msg, const char * const file, int line );

/* Abstract template struct telling us that an assert failed */
template< bool > struct CT_ASSERT_FAILED;
/* Specialization(s) of above */
template<> struct CT_ASSERT_FAILED<false> { enum : bool { value = true }; };
/* non-type template assert tester */
template< int > struct CT_ASSERT_TEST {};

#ifndef NDEBUG

/* Compile time asserts */
#define SN_CT_ASSERT( expression ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( expression ) > ) >; } while(false)

#define SN_CT_ASSERT_EQUAL( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( std::fabs(VALUE - REFERENCE) <= simpleNewton::globalConstants::POSITIVEZERO ) > ) >; } while(false)

#define SN_CT_ASSERT_INEQUAL( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( std::fabs(VALUE - REFERENCE) > simpleNewton::globalConstants::POSITIVEZERO ) > ) >; } while(false)

#define SN_CT_ASSERT_LESS_THAN( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE < REFERENCE ) > ) >; } while(false)

#define SN_CT_ASSERT_LEQ( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE <= REFERENCE ) > ) >; } while(false)

#define SN_CT_ASSERT_GREATER_THAN( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE > REFERENCE ) > ) >; } while(false)

#define SN_CT_ASSERT_GREQ( VALUE, REFERENCE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE >= REFERENCE ) > ) >; } while(false)

#define SN_CT_ASSERT_ZERO( VALUE ) \
   do { using CT_ASSERT_TESTER = simpleNewton::asserts::CT_ASSERT_TEST< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE >= simpleNewton::globalConstants::NEGATIVEZERO && VALUE <= simpleNewton::globalConstants::POSITIVEZERO ) > ) >; } while(false)


/* Run-time asserts */
#define SN_ASSERT( expression ) \
   do { if( !static_cast< bool >( expression ) ) { \
           simpleNewton::asserts::errorMessage( "Assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_EQUAL( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) <= simpleNewton::globalConstants::POSITIVEZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Equality assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_INEQUAL( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) > simpleNewton::globalConstants::POSITIVEZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Inequality assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_LESS_THAN( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( VALUE < REFERENCE ) ) { \
           simpleNewton::asserts::errorMessage( "Less-than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_LEQ( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( VALUE <= REFERENCE ) ) { \
           simpleNewton::asserts::errorMessage( "Less-than-or-equal-to assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_GREATER_THAN( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( VALUE > REFERENCE ) ) { \
           simpleNewton::asserts::errorMessage( "Greater-than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_GREQ( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( VALUE >= REFERENCE ) ) { \
           simpleNewton::asserts::errorMessage( "Greater-than-or-equal-to assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_ZERO( VALUE ) \
   do { if( !static_cast< bool >( std::fabs(VALUE) <= simpleNewton::globalConstants::POSITIVEZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Less than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_MSG( expression, MSG ) \
   do { if( !static_cast< bool >( expression ) ) { \
           simpleNewton::asserts::errorMessage( static_cast<const char * const>(MSG), __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#else

#define SN_CT_ASSERT             ( expression )
#define SN_CT_ASSERT_EQUAL       ( VALUE, REFERENCE )
#define SN_CT_ASSERT_INEQUAL     ( VALUE, REFERENCE )
#define SN_CT_ASSERT_LESS_THAN   ( VALUE, REFERENCE )
#define SN_CT_ASSERT_LEQ         ( VALUE, REFERENCE )
#define SN_CT_ASSERT_GREATER_THAN( VALUE, REFERENCE )
#define SN_CT_ASSERT_GREQ        ( VALUE, REFERENCE )
#define SN_CT_ASSERT_ZERO        ( VALUE )

#define SN_ASSERT             ( expression )
#define SN_ASSERT_EQUAL       ( VALUE, REFERENCE )
#define SN_ASSERT_INEQUAL     ( VALUE, REFERENCE )
#define SN_ASSERT_LESS_THAN   ( VALUE, REFERENCE )
#define SN_ASSERT_LEQ         ( VALUE, REFERENCE )
#define SN_ASSERT_GREATER_THAN( VALUE, REFERENCE )
#define SN_ASSERT_GREQ        ( VALUE, REFERENCE )
#define SN_ASSERT_ZERO        ( VALUE )
#define SN_ASSERT_MSG         ( expression, MSG )

#endif
   
}   // namespace asserts
}   // namespace SimpleNewton
