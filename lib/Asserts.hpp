#ifndef ASSERTS_HPP
#define ASSERTS_HPP

#include <cstdlib>
#include <cmath>
#include <GlobalConstants.hpp>

namespace simpleNewton {
namespace asserts {

/**||***************************************************************************************************************************************
*
*   Description: Compile and run time asserts - equal, inequal, less-than, less-than-or-equal-to, greater-than, greater-than-or-equal-to, 
*
*   equal to zero, is positive and is negative.
*
|***************************************************************************************************************************************///+

/* Declaration: errorMessage is a function for generic errors */
void errorMessage( const char * const msg, const char * const file, int line );

/* Abstract template struct telling us that an assert failed */
template< bool > struct CT_ASSERT_FAILED;
/* Specialization(s) of above */
template<> struct CT_ASSERT_FAILED<false> { enum : bool { value = true }; };
/* non-type template assert tester */
template< int pseudoSize > void declareAssertFailed() {}

#ifdef NDEBUG

#define SN_CT_ASSERT( expression )
#define SN_CT_ASSERT_EQUAL( VALUE, REFERENCE )
#define SN_CT_ASSERT_INEQUAL( VALUE, REFERENCE )
#define SN_CT_ASSERT_LESS_THAN( VALUE, REFERENCE )
#define SN_CT_ASSERT_LEQ( VALUE, REFERENCE )
#define SN_CT_ASSERT_GREATER_THAN( VALUE, REFERENCE )
#define SN_CT_ASSERT_GREQ( VALUE, REFERENCE )
#define SN_CT_ASSERT_ZERO( VALUE )
#define SN_CT_ASSERT_POSITIVE( VALUE )
#define SN_CT_ASSERT_NEGATIVE( VALUE )

#define SN_ASSERT( expression )
#define SN_ASSERT_EQUAL( VALUE, REFERENCE )
#define SN_ASSERT_INEQUAL( VALUE, REFERENCE )
#define SN_ASSERT_LESS_THAN( VALUE, REFERENCE )
#define SN_ASSERT_LEQ( VALUE, REFERENCE )
#define SN_ASSERT_GREATER_THAN( VALUE, REFERENCE )
#define SN_ASSERT_GREQ( VALUE, REFERENCE )
#define SN_ASSERT_ZERO( VALUE )
#define SN_ASSERT_POSITIVE( VALUE )
#define SN_ASSERT_NEGATIVE( VALUE )
#define SN_ASSERT_MSG( expression, MSG )

#define SN_ASSERT_SIZE_SAME( VAR, REF )
#define SN_ASSERT_SIZE_LESS_THAN( VAR, REF )
#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( VAR, REF )
#define SN_ASSERT_INDEX_WITHIN_SIZE( IND, REF )

#else

/* Compile time asserts */
#define SN_CT_ASSERT( expression ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( expression ) > ) >(); } while(false)

#define SN_CT_ASSERT_EQUAL( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( std::fabs(VALUE - REFERENCE) <= simpleNewton::globalConstants::ZERO ) > ) >(); } while(false)

#define SN_CT_ASSERT_INEQUAL( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( std::fabs(VALUE - REFERENCE) > simpleNewton::globalConstants::ZERO ) > ) >(); } while(false)

#define SN_CT_ASSERT_LESS_THAN( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE < REFERENCE ) > ) >(); } while(false)

#define SN_CT_ASSERT_LEQ( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE <= REFERENCE ) > ) >(); } while(false)

#define SN_CT_ASSERT_GREATER_THAN( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE > REFERENCE ) > ) >(); } while(false)

#define SN_CT_ASSERT_GREQ( VALUE, REFERENCE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE >= REFERENCE ) > ) >(); } while(false)

#define SN_CT_ASSERT_ZERO( VALUE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( std::fabs(VALUE) <= simpleNewton::globalConstants::ZERO ) > ) >(); } while(false)

#define SN_CT_ASSERT_POSITIVE( VALUE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE > simpleNewton::globalConstants::ZERO ) > ) >(); } while(false)

#define SN_CT_ASSERT_NEGATIVE( VALUE ) \
   do { simpleNewton::asserts::declareAssertFailed< sizeof( simpleNewton::asserts::CT_ASSERT_FAILED< !static_cast<bool>( VALUE < simpleNewton::globalConstants::ZERO ) > ) >(); } while(false)


/* Run-time asserts */
#define SN_ASSERT( expression ) \
   do { if( !static_cast< bool >( expression ) ) { \
           simpleNewton::asserts::errorMessage( "Assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_EQUAL( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) <= simpleNewton::globalConstants::ZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Equality assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_INEQUAL( VALUE, REFERENCE ) \
   do { if( !static_cast< bool >( std::fabs(VALUE - REFERENCE) > simpleNewton::globalConstants::ZERO ) ) { \
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
   do { if( !static_cast< bool >( std::fabs(VALUE) <= simpleNewton::globalConstants::ZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Equal-to-zero assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_POSITIVE( VALUE ) \
   do { if( !static_cast< bool >( VALUE > simpleNewton::globalConstants::ZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Positivity assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_NEGATIVE( VALUE ) \
   do { if( !static_cast< bool >( VALUE < simpleNewton::globalConstants::ZERO ) ) { \
           simpleNewton::asserts::errorMessage( "Negativity assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_MSG( expression, MSG ) \
   do { if( !static_cast< bool >( expression ) ) { \
           simpleNewton::asserts::errorMessage( static_cast<const char * const>(MSG), __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)


/* Run-time constraints related to container sizes */
#define SN_ASSERT_SIZE_SAME( SIZE, REF ) \
   do { if( !static_cast< bool >( static_cast<unsigned int>(SIZE) == static_cast<unsigned int>(REF) ) ) { \
           simpleNewton::asserts::errorMessage( "Size-less-than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_SIZE_LESS_THAN( SIZE, REF ) \
   do { if( !static_cast< bool >( static_cast<unsigned int>(SIZE) > 0 && static_cast<unsigned int>(SIZE) <= static_cast<unsigned int>(REF) ) ) { \
           simpleNewton::asserts::errorMessage( "Size-less-than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, REF ) \
   do { if( !static_cast< bool >( SIZE > 0 && SIZE < REF ) ) { \
           simpleNewton::asserts::errorMessage( "Size-strictly-less-than assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#define SN_ASSERT_INDEX_WITHIN_SIZE( IND, REF ) \
   do { if( !static_cast< bool >( static_cast<unsigned int>(IND) >= 0 && static_cast<unsigned int>(IND) < static_cast<unsigned int>(REF) ) ) { \
           simpleNewton::asserts::errorMessage( "Index-within-size assertion failed - ", __FILE__, __LINE__ ); \
           std::abort(); \
   } } while(false)

#endif
   
}   // namespace asserts
}   // namespace SimpleNewton

#endif
