#ifndef SN_ASSERTS_HPP
#define SN_ASSERTS_HPP

#include <cstdlib>
#include <cmath>
#include <sstream>

#include <Global.hpp>

#include <logger/Logger.hpp>


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

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   HACK! cpp purely for compilation purposes. Warning! The unit won't instantiate any functional templates from this header.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class T > class Asserts_CPPHackClass {};



namespace asserts {
namespace internal {

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
      
      logger::internal::report_error( "An assertion has failed. The process will now be terminated.", file, line, func );
      ExitProgram();
   }
}



template< class T1, class T2 > 
inline void assert_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) == static_cast<T1>(REFERENCE) ) ) {
         
         logger::internal::report_error( "Equality assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 > 
inline void assert_fp_equal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) <= globalConstants::ZERO ) ) {
         
         logger::internal::report_error( "Floating point equality assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) != static_cast<T1>(REFERENCE) ) ) {
         
         logger::internal::report_error( "Inequality assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_fp_inequal( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( std::fabs( static_cast<T2>(VALUE) - static_cast<T1>(REFERENCE) ) > globalConstants::ZERO ) ) {
         
         logger::internal::report_error( "Floating point inequality assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_less_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) < static_cast<T1>(REFERENCE) ) ) {
         
         logger::internal::report_error( "Less than assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_leq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) <= static_cast<T1>(REFERENCE) ) ) {
         
         logger::internal::report_error( "Less than or equal to assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_greater_than( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) > static_cast<T1>(REFERENCE) ) ) {
        
         logger::internal::report_error( "Greater than assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class T1, class T2 >
inline void assert_greq( const T1 & VALUE, const T2 & REFERENCE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< SAME_TYPE_IN_ASSERT< T1, T2 >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<T2>(VALUE) >= static_cast<T1>(REFERENCE) ) ) {
         
         logger::internal::report_error( "Greater than or equal to assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< class TYPE >
inline void assert_zero( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( std::fabs(VALUE) <= globalConstants::ZERO ) ) {
      
      logger::internal::report_error( "Equal to zero assertion failed. The process will now be terminated.", file, line, func );
      ExitProgram();
   }
}



template< class TYPE >
inline void assert_not_zero( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( std::fabs(VALUE) > globalConstants::ZERO ) ) {
      
      logger::internal::report_error( "Not equal to zero assertion failed. The process will now be terminated.", file, line, func );
      ExitProgram();
   }
}



template< class TYPE >
inline void assert_positive( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( VALUE > globalConstants::ZERO ) ) {
      
      logger::internal::report_error( "Positivity assertion failed. The process will now be terminated.", file, line, func );
      ExitProgram();
   }
}



template< class TYPE >
inline void assert_negative( const TYPE & VALUE, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( VALUE < globalConstants::ZERO ) ) {
     
      logger::internal::report_error( "Negativity assertion failed. The process will now be terminated.", file, line, func );
      ExitProgram();
   }
}



template< bool constexpr_expr >
inline void assert_msg( const char* const MSG, const char * const file, int line, const std::string & func ) {
   if( !static_cast< bool >( constexpr_expr ) ) {
     
      logger::internal::report_error( MSG, file, line, func );
      std::exit( EXIT_FAILURE );
   }
}



template< typename U_INT >
inline void assert_size_same( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) == static_cast<unsigned long long>(REF) ) ) {
        
         logger::internal::report_error( "Same size assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_size_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) <= static_cast<unsigned long long>(REF) ) ) {
       
         logger::internal::report_error( "Size less than assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_size_strictly_less_than( const U_INT & SIZE, const U_INT & REF, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(SIZE) < static_cast<unsigned long long>(REF) ) ) {
       
         logger::internal::report_error( "Size strictly less than assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}



template< typename U_INT >
inline void assert_index_within_size( const U_INT & IND, const U_INT & SIZE, const char * const file, int line, const std::string & func ) {
   if( ! TYPE_ERROR< INT_IN_ASSERT< U_INT >::value >::ASSERT_FAILED ) { // cast guard
      if( !static_cast< bool >( static_cast<unsigned long long>(IND) < static_cast<unsigned long long>(SIZE) ) ) {
      
         logger::internal::report_error( "Index within size assertion failed. The process will now be terminated.", file, line, func );
         ExitProgram();
      }
   }
}

}   // namespace internal
}   // namespace asserts

#endif   // DOXYSKIP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RELEASE mode assert
//////////////////////

/**   Run-time requirement failing which the program will exit with a suitable error message. The macro will direct its output at the 
*     logger with information about the file, line and function. The ellipsis captures the bool expression which formulates the requirement.
*/
#define SN_REQUIRE( ... ) \
do { asserts::internal::assert( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of equality failing which the program will exit with a suitable error message. The macro will direct its output 
*     at the logger with information about the file, line and function. Note: the ellipsis captures the variable. This is to 
*     accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_EQUAL( REF, ... ) \
do { asserts::internal::assert_equal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of equality in floating point arithmetic failing which the program will exit with a suitable error message. The 
*     macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis captures the 
*     variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_FP_EQUAL( REF, ... ) \
do { asserts::internal::assert_fp_equal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)




/**   Run-time requirement of inequality failing which the program will exit with a suitable error message. The macro will direct its 
*     output at the logger with information about the file, line and function. Note: the ellipsis captures the variable. This is to 
*     accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF An instance which needs to be compared with another.
*/
#define SN_REQUIRE_INEQUAL( REF, ... ) \
do { asserts::internal::assert_inequal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement of inequality in floating point arithmetic failing which the program will exit with a suitable error message. 
*     The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis captures the 
*     reference value. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_FP_INEQUAL( REF, ... ) \
do { asserts::internal::assert_fp_inequal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be less than another, failing which the program will exit with a suitable error message. The 
*     macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis captures the 
*     variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_LESS_THAN( REF, ... ) \
do { asserts::internal::assert_less_than( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be less than or equal to another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_LEQ( REF, ... ) \
do { asserts::internal::assert_leq( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be greater than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_GREATER_THAN( REF, ... ) \
do { asserts::internal::assert_greater_than( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one value be greater than or equal to another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*
*     \param REF The reference value provided.
*/
#define SN_REQUIRE_GREQ( REF, ... ) \
do { asserts::internal::assert_greq( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be equal to zero in floating point arithmetic, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_REQUIRE_ZERO( ... ) \
do { asserts::internal::assert_zero( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value not be equal to zero in floating point arithmetic, failing which the program will exit with a 
*     suitable error message. The macro will direct its output at the logger with information about the file, line and function. Note: the 
*     ellipsis captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*/
#define SN_REQUIRE_NOT_ZERO( ... ) \
do { asserts::internal::assert_not_zero( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be positive, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_REQUIRE_POSITIVE( ... ) \
do { asserts::internal::assert_positive( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that a value be negative, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_REQUIRE_NEGATIVE( ... ) \
do { asserts::internal::assert_negative( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement failing which the program will exit with a user-defined error message. The macro will direct its output at the 
*     logger with information about the file, line and function. Note: the ellipsis captures the requirement. This is to accommodate for 
*     template function and class names which may have multiple template parameters.
*
*     \param MSG  Error message which will be passed to the constructor of std::string.
*/
#define SN_REQUIRE_MSG( MSG, ... ) \
do { \
      std::stringstream oss; \
      oss << MSG; \
      asserts::internal::assert_msg< __VA_ARGS__ >( oss.str().c_str(), __FILE__, __LINE__, __func__ ); } while(false)



/* Run-time constraints related to container sizes */

/**   Run-time requirement that two sizes be the same, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_REQUIRE_SIZE_SAME( SIZE, ... ) \
do { asserts::internal::assert_size_same( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(__VA_ARGS__), \
                                      __FILE__, __LINE__, __func__ ); } while(false)


/**   Run-time requirement that one size be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_REQUIRE_SIZE_LESS_THAN( SIZE, ... ) \
do { asserts::internal::assert_size_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(__VA_ARGS__), \
                                           __FILE__, __LINE__, __func__ ); } while(false)



/**   Run-time requirement that one size be strictly less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_REQUIRE_SIZE_STRICTLY_LESS_THAN( SIZE, ... ) \
do { asserts::internal::assert_size_strictly_less_than( static_cast< const unsigned long >(SIZE), \
                                                        static_cast< const unsigned long >(__VA_ARGS__), \
                                                        __FILE__, __LINE__, __func__ ); } while(false)


/**   Run-time requirement that an index be less than its corresponding container's size, failing which the program will exit with a 
*     suitable error message. The macro will direct its output at the logger with information about the file, line and function. Note: the 
*     ellipsis captures the size variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*
*     \param IND  An integer-valued container size.
*/
#define SN_REQUIRE_INDEX_WITHIN_SIZE( IND, ... ) \
do { asserts::internal::assert_index_within_size( static_cast< const unsigned long >(IND), static_cast< const unsigned long >(__VA_ARGS__),\
                                              __FILE__, __LINE__, __func__ ); } while(false)



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DEBUG mode run time asserts
/////////////////////////////////

#ifdef NDEBUG
#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define SN_ASSERT( ... )
#define SN_ASSERT_EQUAL( REF, ... )
#define SN_ASSERT_FP_EQUAL( REF, ... )
#define SN_ASSERT_INEQUAL( REF, ... )
#define SN_ASSERT_FP_INEQUAL( REF, ... )
#define SN_ASSERT_LESS_THAN( REF, ... )
#define SN_ASSERT_LEQ( REF, ... )
#define SN_ASSERT_GREATER_THAN( REF, ... )
#define SN_ASSERT_GREQ( REF, ... )
#define SN_ASSERT_ZERO( ... )
#define SN_ASSERT_NOT_ZERO( ... )
#define SN_ASSERT_POSITIVE( ... )
#define SN_ASSERT_NEGATIVE( ... )
#define SN_ASSERT_MSG( MSG, ... )
#define SN_ASSERT_SIZE_SAME( SIZE, ... )
#define SN_ASSERT_SIZE_LESS_THAN( SIZE, ... )
#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, ... )
#define SN_ASSERT_INDEX_WITHIN_SIZE( SIZE, ... )

#endif   // DOXYSKIP
#else



/**   DEBUG mode run-time requirement failing which the program will exit with a suitable error message. The macro will direct its 
*     output at the logger with information about the file, line and function. Note: the ellipsis captures the bool expression. This is to 
*     accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_ASSERT( ... ) \
do { asserts::internal::assert( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of equality failing which the program will exit with a suitable error message. The macro will 
*     direct its output at the logger with information about the file, line and function. Note: the ellipsis captures the variable. This is 
*     to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_EQUAL( REF, ... ) \
do { asserts::internal::assert_equal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of equality in floating point arithmetic failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_FP_EQUAL( REF, ... ) \
do { asserts::internal::assert_fp_equal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of inequality failing which the program will exit with a suitable error message. The macro will 
*     direct its output at the logger with information about the file, line and function. Note: the ellipsis captures the variable. This is 
*     to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_INEQUAL( REF, ... ) \
do { asserts::internal::assert_inequal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement of inequality in floating point arithmetic failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_FP_INEQUAL( REF, ... ) \
do { asserts::internal::assert_fp_inequal( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_LESS_THAN( REF, ... ) \
do { asserts::internal::assert_less_than( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be less than or equal to another, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_LEQ( REF, ... ) \
do { asserts::internal::assert_leq( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be greater than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_GREATER_THAN( REF, ... ) \
do { asserts::internal::assert_greater_than( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that one value be greater than or equal to another, failing which the program will exit with a 
*     suitable error message. The macro will direct its output at the logger with information about the file, line and function. Note: the 
*     ellipsis captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*
*     \param REF The reference value provided.
*/
#define SN_ASSERT_GREQ( REF, ... ) \
do { asserts::internal::assert_greq( REF, __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be equal to zero in floating point arithmetic, failing which the program will exit with 
*     a suitable error message. The macro will direct its output at the logger with information about the file, line and function. Note: 
*     the ellipsis captures the variable. This is to accommodate for template function and class names which may have multiple template 
*     parameters.
*/
#define SN_ASSERT_ZERO( ... ) \
do { asserts::internal::assert_zero( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value not be equal to zero in floating point arithmetic, failing which the program will exit 
*     with a suitable error message. The macro will direct its output at the logger with information about the file, line and function. 
*     Note: the ellipsis captures the variable. This is to accommodate for template function and class names which may have multiple 
*     template parameters.
*/
#define SN_ASSERT_NOT_ZERO( ... ) \
do { asserts::internal::assert_not_zero( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be positive, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_ASSERT_POSITIVE( ... ) \
do { asserts::internal::assert_positive( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that a value be negative, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*/
#define SN_ASSERT_NEGATIVE( ... ) \
do { asserts::internal::assert_negative( __VA_ARGS__, __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement failing which the program will exit with a user-defined error message. The macro will direct its 
*     output at the logger with information about the file, line and function. Note: the ellipsis captures the variable. This is to 
*     accommodate for template function and class names which may have multiple template parameters.
*
*     \param MSG  Error message which will be passed to the constructor of std::string.
*/
#define SN_ASSERT_MSG( MSG, ... ) \
do { \
      std::stringstream oss; \
      oss << MSG; \
      asserts::internal::assert_msg< __VA_ARGS__ >( oss.str().c_str(), __FILE__, __LINE__, __func__ ); } while(false)



/* Run-time constraints related to container sizes */

/**   DEBUG mode run-time requirement that two sizes be the same, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_ASSERT_SIZE_SAME( SIZE, ... ) \
do { asserts::internal::assert_size_same( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(__VA_ARGS__), \
                                      __FILE__, __LINE__, __func__ ); } while(false)


/**   DEBUG mode run-time requirement that one size be less than another, failing which the program will exit with a suitable error 
*     message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_ASSERT_SIZE_LESS_THAN( SIZE, ... ) \
do { asserts::internal::assert_size_less_than( static_cast< const unsigned long >(SIZE), static_cast< const unsigned long >(__VA_ARGS__), \
                                           __FILE__, __LINE__, __func__ ); } while(false)


/**   DEBUG mode run-time requirement that one size be strictly less than another, failing which the program will exit with a suitable 
*     error message. The macro will direct its output at the logger with information about the file, line and function. Note: the ellipsis 
*     captures the variable. This is to accommodate for template function and class names which may have multiple template parameters.
*
*     \param SIZE An integer-valued container size.
*/
#define SN_ASSERT_SIZE_STRICTLY_LESS_THAN( SIZE, ... ) \
do { asserts::internal::assert_size_strictly_less_than( static_cast< const unsigned long >(SIZE), \
                                                        static_cast< const unsigned long >(__VA_ARGS__), \
                                                        __FILE__, __LINE__, __func__ ); } while(false)



/**   DEBUG mode run-time requirement that an index be less than its corresponding container's size, failing which the program will exit 
*     with a suitable error message. The macro will direct its output at the logger with information about the file, line and function. 
*     Note: the ellipsis captures the size variable. This is to accommodate for template function and class names which may have multiple 
*     template parameters.
*
*     \param IND  An integer-valued container size.
*/
#define SN_ASSERT_INDEX_WITHIN_SIZE( IND, ... ) \
do { asserts::internal::assert_index_within_size( static_cast< const unsigned long >(IND), static_cast< const unsigned long >(__VA_ARGS__),\
                                              __FILE__, __LINE__, __func__ ); } while(false)

#endif
   
}   // namespace SimpleNewton

#endif
