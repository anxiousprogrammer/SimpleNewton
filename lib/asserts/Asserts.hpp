#ifndef SN_ASSERTS_HPP
#define SN_ASSERTS_HPP

#include <cstdlib>
#include <cmath>

#include <GlobalConstants.hpp>
#include <logger/Logger.hpp>
#include <core/ProcSingleton.hpp>

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//=========================================================================================================================================
//
//  This file is part of simpleNewton. simpleNewton is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  simpleNewton is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with simpleNewton (see LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
//
///   This file provides a set of commonly used run-time asserts for both release as well as debug modes. The release mode versions of
///   the functions begin with the prefix, "SN_REQUIRE_" whereas the debug mode versions with, "SN_ASSERT_". The failing of the 
///   particular conditions causes the program to exit in a manner as defined by the ProcSingleton class, which should initiate the 
///   calling of some destructors and perform some cleanup. Before exiting, a suitable error message is issued by the logger.
///   \file
///   \addtogroup asserts Asserts
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//=========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   HACK! cpp purely for compilation purposes. Warning! The unit won't instantiate any functional templates from this header.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class T > class Asserts_CPPHackClass {};



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



inline void assert( bool expr, const char * const file, int line, const std::string & func ) {
   if( ! expr ) {
      
      logger::impl::report_error( "An assertion has failed. The process will now be terminated.", file, line, func );
      ProcSingleton::ExitProgram();
   }
}



template< class T1, class T2 > 
inline void assert_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) == static_cast<T1>(REFERENCE) ) ) {
         
         logger::impl::report_error( "Equality assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 > 
inline void assert_fp_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) <= globalConstants::ZERO ) ) {
         
         logger::impl::report_error( "Floating point equality assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) != static_cast<T1>(REFERENCE) ) ) {
         
         logger::impl::report_error( "Inequality assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_fp_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) > globalConstants::ZERO ) ) {
         
         logger::impl::report_error( "Floating point inequality assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_less_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) < static_cast<T1>(REFERENCE) ) ) {
         
         logger::impl::report_error( "Less than assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_leq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) <= static_cast<T1>(REFERENCE) ) ) {
         
         logger::impl::report_error( "Less than or equal to assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_greater_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) > static_cast<T1>(REFERENCE) ) ) {
        
         logger::impl::report_error( "Greater than assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_greq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) >= static_cast<T1>(REFERENCE) ) ) {
         
         logger::impl::report_error( "Greater than or equal to assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< class TYPE >
inline void assert_zero( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( std::fabs(VALUE) <= globalConstants::ZERO ) ) {
      
      logger::impl::report_error( "Equal to zero assertion failed. The process will now be terminated.", file, line, func );
      ProcSingleton::ExitProgram();
   }
}



template< class TYPE >
inline void assert_positive( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( VALUE > globalConstants::ZERO ) ) {
      
      logger::impl::report_error( "Positivity assertion failed. The process will now be terminated.", file, line, func );
      ProcSingleton::ExitProgram();
   }
}



template< class TYPE >
inline void assert_negative( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( VALUE < globalConstants::ZERO ) ) {
     
      logger::impl::report_error( "Negativity assertion failed. The process will now be terminated.", file, line, func );
      ProcSingleton::ExitProgram();
   }
}



template< bool constexpr_expr >
inline void assert_msg( const char* const MSG, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( constexpr_expr ) ) {
     
      logger::impl::report_error( MSG, file, line, func );
      std::exit( EXIT_FAILURE );
   }
}



template< typename U_INT >
inline void assert_size_same( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) == static_cast<unsigned long long>(REF) ) ) {
        
         logger::impl::report_error( "Same size assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_size_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) <= static_cast<unsigned long long>(REF) ) ) {
       
         logger::impl::report_error( "Size less than assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_size_strictly_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) < static_cast<unsigned long long>(REF) ) ) {
       
         logger::impl::report_error( "Size strictly less than assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_index_within_size( const U_INT & IND, const U_INT & SIZE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(IND) < static_cast<unsigned long long>(SIZE) ) ) {
      
         logger::impl::report_error( "Index within size assertion failed. The process will now be terminated.", file, line, func );
         ProcSingleton::ExitProgram();
      }
   }
}

}   // namespace impl
}   // namespace asserts

#endif   // DOXYSKIP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RELEASE mode assert
//////////////////////

/**   Run-time requirement failing which the program will exit with a suitable error message. The macro will direct its output at the 
*     logger with information about the file, line and function.
*
*     \param EXPR bool expression which needs to be evaluated.
*/
#define SN_REQUIRE( EXPR ) \
do { asserts::impl::assert( EXPR, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of equality failing which the program will exit with a suitable error message. The macro will direct its output 
*     at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for equality.
*/
#define SN_REQUIRE_EQUAL( VAL, REF ) \
do { asserts::impl::assert_equal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of equality in floating point arithmetic failing which the program will exit with a suitable error message. The 
*     macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for equality.
*/
#define SN_REQUIRE_FP_EQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_equal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)




/**   Run-time requirement of inequality failing which the program will exit with a suitable error message. The macro will direct its 
*     output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for inequality.
*/
#define SN_REQUIRE_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_inequal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of inequality in floating point arithmetic failing which the program will exit with a suitable error message. 
*     The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for inequality.
*/
#define SN_REQUIRE_FP_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_inequal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be less than another, failing which the program will exit with a suitable error message. The 
*     macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_REQUIRE_LESS_THAN( VAL, REF ) \
do { asserts::impl::assert_less_than( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be less than or equal to another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_REQUIRE_LEQ( VAL, REF ) \
do { asserts::impl::assert_leq( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be greater than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_REQUIRE_GREATER_THAN( VAL, REF ) \
do { asserts::impl::assert_greater_than( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be greater than or equal to another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_REQUIRE_GREQ( VAL, REF ) \
do { asserts::impl::assert_greq( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be equal to zero in floating point arithmetic, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be zero valued.
*/
#define SN_REQUIRE_ZERO( VAL ) \
do { asserts::impl::assert_zero( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be positive, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be positive.
*/
#define SN_REQUIRE_POSITIVE( VAL ) \
do { asserts::impl::assert_positive( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be negative, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be negative.
*/
#define SN_REQUIRE_NEGATIVE( VAL ) \
do { asserts::impl::assert_negative( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement failing which the program will exit with a user-defined error message. The macro will direct its output at the 
*     logger with information about the file, line and function.
*
*     \param EXPR A bool expression.
*     \param MSG  Error message which will be passed to the constructor of std::string.
*/
#define SN_REQUIRE_MSG( EXPR, MSG ) \
do { asserts::impl::assert_msg< EXPR >( MSG, __FILE__, __LINE__, __func__ ); } while(false)



/* Run-time constraints related to container sizes */

/**   Run-time requirement that two sizes be the same, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_REQUIRE_SIZE_SAME( SIZE, REF ) \
do { asserts::impl::assert_size_same( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                      __FILE__, __LINE__, __func__ ); } while(false)


/**   Run-time requirement that one size be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_REQUIRE_SIZE_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                           __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one size be strictly less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_REQUIRE_SIZE_STRICTLY_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_strictly_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                                    __FILE__, __LINE__, __func__ ); } while(false)


/**   Run-time requirement that an index be less than its corresponding container's size, failing which the program will exit with a 
*     suitable error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param IND  An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_REQUIRE_INDEX_WITHIN_SIZE( IND, REF ) \
do { asserts::impl::assert_index_within_size( static_cast< const unsigned long >(IND), static_cast< const unsigned long >(REF), \
                                              __FILE__, __LINE__, __func__ ); } while(false)



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DEBUG mode run time asserts
/////////////////////////////////

#ifdef NDEBUG
#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define SN_ASSERT( EXPR )
#define SN_ASSERT_EQUAL( VAL, REF )
#define SN_ASSERT_FP_EQUAL( VAL, REF )
#define SN_ASSERT_INEQUAL( VAL, REF )
#define SN_ASSERT_FP_INEQUAL( VAL, REF )
#define SN_ASSERT_LESS_THAN( VAL, REF )
#define SN_ASSERT_LEQ( VAL, REF )
#define SN_ASSERT_GREATER_THAN( VAL, REF )
#define SN_ASSERT_GREQ( VAL, REF )
#define SN_ASSERT_ZERO( VAL )
#define SN_ASSERT_POSITIVE( VAL )
#define SN_ASSERT_NEGATIVE( VAL )
#define SN_ASSERT_MSG( EXPR, MSG )
#define SN_ASSERT_SIZE_SAME( SIZE, REF )
#define SN_ASSERT_SIZE_LESS_THAN( SIZE, REF )
#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, REF )
#define SN_ASSERT_INDEX_WITHIN_SIZE( SIZE, REF )

#endif   // DOXYSKIP
#else



/**   DEBUG mode run-time requirement failing which the program will exit with a suitable error message. The macro will direct its 
*     output at the logger with information about the file, line and function.
*
*     \param EXPR bool expression which needs to be evaluated.
*/
#define SN_ASSERT( EXPR ) \
do { asserts::impl::assert( EXPR, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of equality failing which the program will exit with a suitable error message. The macro will 
*     direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for equality.
*/
#define SN_ASSERT_EQUAL( VAL, REF ) \
do { asserts::impl::assert_equal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of equality in floating point arithmetic failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for equality.
*/
#define SN_ASSERT_FP_EQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_equal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of inequality failing which the program will exit with a suitable error message. The macro will 
*     direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for inequality.
*/
#define SN_ASSERT_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_inequal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of inequality in floating point arithmetic failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for inequality.
*/
#define SN_ASSERT_FP_INEQUAL( VAL, REF ) \
do { asserts::impl::assert_fp_inequal( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_ASSERT_LESS_THAN( VAL, REF ) \
do { asserts::impl::assert_less_than( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be less than or equal to another, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_ASSERT_LEQ( VAL, REF ) \
do { asserts::impl::assert_leq( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be greater than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_ASSERT_GREATER_THAN( VAL, REF ) \
do { asserts::impl::assert_greater_than( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be greater than or equal to another, failing which the program will exit with a 
*     suitable error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be compared with another.
*     \param REF An instance of the same type as VAL which serves as reference for comparison.
*/
#define SN_ASSERT_GREQ( VAL, REF ) \
do { asserts::impl::assert_greq( VAL, REF, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be equal to zero in floating point arithmetic, failing which the program will exit with 
*     a suitable error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be zero valued.
*/
#define SN_ASSERT_ZERO( VAL ) \
do { asserts::impl::assert_zero( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be positive, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be positive.
*/
#define SN_ASSERT_POSITIVE( VAL ) \
do { asserts::impl::assert_positive( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be negative, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param VAL An instance which needs to be negative.
*/
#define SN_ASSERT_NEGATIVE( VAL ) \
do { asserts::impl::assert_negative( VAL, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement failing which the program will exit with a user-defined error message. The macro will direct its 
*     output at the logger with information about the file, line and function.
*
*     \param EXPR A bool expression.
*     \param MSG  Error message which will be passed to the constructor of std::string.
*/
#define SN_ASSERT_MSG( EXPR, MSG ) \
do { asserts::impl::assert_msg< EXPR >( MSG, __FILE__, __LINE__, __func__ ); } while(false)



/* Run-time constraints related to container sizes */

/**   DEBUG mode run-time requirement that two sizes be the same, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_ASSERT_SIZE_SAME( SIZE, REF ) \
do { asserts::impl::assert_size_same( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                      __FILE__, __LINE__, __func__ ); } while(false)


/**   DEBUG mode run-time requirement that one size be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_ASSERT_SIZE_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                           __FILE__, __LINE__, __func__ ); } while(false)


/**   DEBUG mode run-time requirement that one size be strictly less than another, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param SIZE An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, REF ) \
do { asserts::impl::assert_size_strictly_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(REF), \
                                                    __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that an index be less than its corresponding container's size, failing which the program will exit 
*     with a suitable error message. The macro will direct its output at the logger with information about the file, line and function.
*
*     \param IND  An integer-valued container size.
*     \param REF  An integer-valued container size reference.
*/
#define SN_ASSERT_INDEX_WITHIN_SIZE( IND, REF ) \
do { asserts::impl::assert_index_within_size( static_cast< const unsigned long >(IND), static_cast< const unsigned long >(REF), \
                                              __FILE__, __LINE__, __func__ ); } while(false)

#endif
   
}   // namespace SimpleNewton

#endif
