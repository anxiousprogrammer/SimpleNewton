#ifndef SN_TYPECONSTRAINTS_HPP
#define SN_TYPECONSTRAINTS_HPP

#include <iostream>
#include <cstdlib>

#include <types/BasicTypeTraits.hpp>

//========================================================================================================================================
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
///   This file provides numerous compile-time constraints. If any compile-time constraint fails, the compiler will throw fairly readable 
///   compile time errors. All such constraints are prefixed with "SN_CT_".
///   \file
///   \addtogroup typeconstraints TypeConstraints
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   HACK! cpp purely for compilation purposes. Warning! The unit won't instantiate any functional templates from this header.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class T > class TypeConstraints_CPPHackClass {};

namespace typetraits {
namespace impl {
// Error signal function
template< bool > struct CT_ASSERT_ERROR;
template<> struct CT_ASSERT_ERROR<true>  { enum { ASSERT_FAILED = false }; };
template<> struct CT_ASSERT_ERROR<false> {};
}   // namespace impl
}   // namespace typetraits

#endif   // DOXYSKIP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   RELEASE mode constraints: type requirements. Use only when absolutely necessary.
////////////////////////////////////////////////////////////////////////////////


/**   A general purpose, boolean expression triggered compile-time constraint for the release mode.
*
*     \tparam constexpr_expr   A bool expression which formulates the requirement of the assert.
*/
template< bool constexpr_expr >
inline void __attribute__( (optimize("O0")) ) SN_CT_REQUIRE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< static_cast<bool>( constexpr_expr ) >::ASSERT_FAILED ) return;
}



#ifdef NDEBUG
#ifndef DOXYGEN_SHOULD_SKIP_THIS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   RELEASE mode: functions are deactivated. 
/////////////////////////////////////////////

template< bool constexpr_expr >
inline void SN_CT_ASSERT() {}

template< int NUM, class... PARAM >
inline void SN_CT_ASSERT_NUM_TEMPLATE_ARG() {}

template< class TYPE >
inline void SN_CT_ASSERT_VOID_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_INT_TYPE() {}
#define SN_CT_ASSERT_INT( ... )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_INT_TYPE() {}
#define SN_CT_ASSERT_NOT_INT( ... )

template< class TYPE >
inline void SN_CT_ASSERT_FP_TYPE() {}
#define SN_CT_ASSERT_FP( ... )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_FP_TYPE() {}
#define SN_CT_ASSERT_NOT_FP( ... )

template< class TYPE >
inline void SN_CT_ASSERT_SMALL_TYPE() {}
#define SN_CT_ASSERT_SMALL( ... )

template< class TYPE >
inline void SN_CT_ASSERT_LARGE_TYPE() {}
#define SN_CT_ASSERT_LARGE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_ID_TYPE() {}
#define SN_CT_ASSERT_ID( ... )

template< class TYPE >
inline void SN_CT_ASSERT_STRING_TYPE() {}
#define SN_CT_ASSERT_STRING( ... )

template< class TYPE >
inline void SN_CT_ASSERT_BOOL_TYPE() {}
#define SN_CT_ASSERT_BOOL( ... )

template< class TYPE >
inline void SN_CT_ASSERT_BASIC_TYPE() {}
#define SN_CT_ASSERT_BASIC( ... )

template< class TYPE >
inline void SN_CT_ASSERT_ARRAY_TYPE() {}
#define SN_CT_ASSERT_ARRAY( ... )

template< class ARR, class TYPE >
inline void SN_CT_ASSERT_ARRAY_OF_TYPE() {}
#define SN_CT_ASSERT_INSTANCE_ARRAY_OF_TYPE( INST, ... )

template< class TYPE >
inline void SN_CT_ASSERT_ARRAY_OF_BASIC_TYPE() {}
#define SN_CT_ASSERT_INSTANCE_ARRAY_OF_BASIC_TYPE( ... )

#define SN_CT_ASSERT_FUNCTION( ... )

template< class TYPE >
inline void SN_CT_ASSERT_CLASS_TYPE() {}
#define SN_CT_ASSERT_OBJECT( ... )

template< class TYPE >
inline void SN_CT_ASSERT_TYPELIST() {}

template< class TYPE >
inline void SN_CT_ASSERT_PTR_TYPE() {}
#define SN_CT_ASSERT_PTR( ... )

template< class TYPE >
inline void SN_CT_ASSERT_PTR_TO_CONST_TYPE() {}
#define SN_CT_ASSERT_PTR_TO_CONST( ... )

template< class TYPE >
inline void SN_CT_ASSERT_FUNCTION_PTR_TYPE() {}
#define SN_CT_ASSERT_FUNCTION_PTR( ... )

template< class TYPE >
inline void SN_CT_ASSERT_MEMBER_FUNCTION_PTR_TYPE() {}
#define SN_CT_ASSERT_MEMBER_FUNCTION_PTR( ... )

template< class TYPE >
inline void SN_CT_ASSERT_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_REFERENCE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_CONST_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_CONST_REFERENCE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_RVALUE_REFERENCE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_NOT_RVALUE_REFERENCE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_CONST_TYPE() {}
#define SN_CT_ASSERT_CONST( ... )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_CONST_TYPE() {}
#define SN_CT_ASSERT_NOT_CONST( ... )

template< class TYPE >
inline void SN_CT_ASSERT_VOLATILE_TYPE() {}
#define SN_CT_ASSERT_VOLATILE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_VOLATILE_TYPE() {}
#define SN_CT_ASSERT_NOT_VOLATILE( ... )

template< class TYPE >
inline void SN_CT_ASSERT_UNSIGNED_TYPE() {}
#define SN_CT_ASSERT_UNSIGNED( ... )

template< class TYPE >
inline void SN_CT_ASSERT_SIGNED_TYPE() {}
#define SN_CT_ASSERT_SIGNED( ... )

#define SN_CT_ASSERT_RVALUE( ... )
#define SN_CT_ASSERT_LVALUE( ... )

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_SAME_TYPENAME() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_STRICTLY_SAME_TYPENAME() {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_SAME_TYPE( const TYPE1 &, const TYPE2 & ) {}
#define SN_CT_ASSERT_STRICTLY_SAME_TYPE( INST1, INST2 )

template< class TYPE, class GTYPE >
inline void SN_CT_ASSERT_TYPE( const GTYPE & ) {}
#define SN_CT_ASSERT_STRICTLY_TYPE( INST, ... )

template< class TYPE, class TYPELIST >
inline void SN_CT_ASSERT_TYPE_IN_TYPELIST() {}


template< class DER, class BASE >
inline void SN_CT_ASSERT_DERIVED_FROM() {}
template< class DER, class BASE >
inline void SN_CT_ASSERT_INSTANCE_DERIVED_FROM( const DER &, const BASE & ) {}

template< class CLS, class TL >
inline void SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER() {}
template< class TL, class CLS >
inline void SN_CT_ASSERT_INSTANCE_DERIVED_FROM_LIST_MEMBER( const CLS & ) {}

template< class DER, class BASE >
inline void SN_CT_ASSERT_NOT_DERIVED_FROM() {}
template< class DER, class BASE >
inline void SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( const DER &, const BASE & ) {}

template< class TYPE >
inline void SN_CT_ASSERT_CALLABLE_TYPE() {}
#define SN_CT_ASSERT_CALLABLE( ... )

template< class CAL, class... PARAM >
inline void SN_CT_ASSERT_FUNCTOR_CAN_CALL() {}
template< class... PARAM, class CAL >
inline void SN_CT_ASSERT_CAN_CALL( const CAL ) {}

template< class TYPE >
inline void SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE() {}

template< class TYPE, class... PARAM >
inline void SN_CT_ASSERT_CONSTRUCTIBLE_TYPE() {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_STRICTLY_COMPARABLE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_COMPARABLE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_COMPARABLE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_COPY_ASSIGNABLE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_COPY_ASSIGNABLE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_MOVE_ASSIGNABLE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_MOVE_ASSIGNABLE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_ASSIGNABLE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_ASSIGNABLE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_ADD_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_ADD( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE2, class TYPE1 >
inline void SN_CT_ASSERT_CAN_SUBTRACT_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_SUBTRACT( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_MULTIPLY_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_MULTIPLY( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE2, class TYPE1 >
inline void SN_CT_ASSERT_CAN_DIVIDE_TYPE() {}
template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_DIVIDE( const TYPE1 &, const TYPE2 & ) {}

template< class TYPE >
inline void SN_CT_ASSERT_ARITHMETIC_TYPE() {}
template< class TYPE >
inline void SN_CT_ASSERT_ARITHMETIC( const TYPE & ) {}

#endif   // DOXYSKIP
#else   // If debug

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DEBUG mode 
///////////////



/**   A general boolean compile-time constraint.
*
*     \tparam constexpr_expr   A constexpr bool expression.
*/
template< bool constexpr_expr >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT() {
   if( !typetraits::impl::CT_ASSERT_ERROR< static_cast<bool>( constexpr_expr ) >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the number of template parameters in a parameter pack must be equal to a certain value.
*
*     \tparam NUM   The number of template parameters.
*     \tparam ARG   The parameter pack.
*/
template< int NUM, class... ARG >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NUM_TEMPLATE_ARG() {
   if( !typetraits::impl::CT_ASSERT_ERROR< (NUM == typetraits::argument_count<ARG...>::value) >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that a given type be void.
*
*     \tparam TYPE   The type which is required to be void.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOID_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_void< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) 
      return;
}



/**   A compile-time constraint that a given type be of integer type.
*
*     \tparam TYPE   The type which is required to be of integer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INT_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_integer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance be of integer type. */
#define SN_CT_ASSERT_INT( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
                                           typetraits::is_integer< \
                                                                   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                 >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should not be of integer type.
*
*     \tparam TYPE   The type which is required to not be of integer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_INT_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::not_integer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should not be of integer type. */
#define SN_CT_ASSERT_NOT_INT( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
                                           typetraits::not_integer< \
                                                                    typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                  >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of floating point type.
*
*     \tparam TYPE   The type which is required to be of floating point type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FP_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_floating_point< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of floating point type. */
#define SN_CT_ASSERT_FP( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
                                           typetraits::is_floating_point< \
                                                                          typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                        >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should not be of floating point type.
*
*     \tparam TYPE   The type which is required to not be of floating point type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_FP_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::not_floating_point< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should not be of floating point type. */
#define SN_CT_ASSERT_NOT_FP( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_floating_point< \
                                                                          typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                         >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be small_t.
*
*     \tparam TYPE   The type which is required to be small_t.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SMALL_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_small_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of small_t type. */
#define SN_CT_ASSERT_SMALL( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_small_t< \
                                                                   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                 >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be large_t.
*
*     \tparam TYPE   The type which is required to be large_t.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_LARGE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_large_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of large_t type. */
#define SN_CT_ASSERT_LARGE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_large_t< \
                                                                   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                 >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be ID_t.
*
*     \tparam TYPE   The type which is required to be ID_t.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ID_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_ID_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of ID_t. */
#define SN_CT_ASSERT_ID( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_ID_t< \
                                                                typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                              >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be std::string.
*
*     \tparam TYPE   The type which is required to be std::string.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRING_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_string_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of std::string type. */
#define SN_CT_ASSERT_STRING( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_string_t< \
                                                                    typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                  >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be bool.
*
*     \tparam TYPE   The type which is required to be bool.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_BOOL_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_bool< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of bool type. */
#define SN_CT_ASSERT_BOOL( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_bool< \
                                                                typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                              >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be basic.
*
*     \tparam TYPE   The type which is required to be basic.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_BASIC_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_basic< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be of bool type. */
#define SN_CT_ASSERT_BASIC( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_basic< \
                                                                typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                              >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)


/**   A compile-time constraint that a given type should be an array.
*
*     \tparam TYPE   The type which is required to be an array.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARRAY_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_array< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be an array. */
#define SN_CT_ASSERT_ARRAY( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_array< \
                                                                 typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                               >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be an array of a specific type.
*
*     \tparam ARR    The type which is required to be an array of specific type.
*     \tparam TYPE   The specified type of which ARR should be an array.
*/
template< class ARR, class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARRAY_OF_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_array_of_type< 
                                                                         typename typetraits::impl::NoCVQ_R<ARR>::type,
                                                                         typename typetraits::impl::NoCVQ_R<TYPE>::type 
                                                                       >::value
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be an array of specified type. */
#define SN_CT_ASSERT_INSTANCE_ARRAY_OF_TYPE( INST, ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_array_of_type< \
                                                                 typename typetraits::impl::NoCVQ_R<decltype(INST)>::type, \
                                                                 typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                       >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be an array of basic type.
*
*     \tparam ARR    The type which is required to be an array of basic type.
*/
template< class ARR >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARRAY_OF_BASIC_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_array_of_basic_type< typename typetraits::impl::NoCVQ_R<ARR>::type >::value
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an instance should be an array of specified type. */
#define SN_CT_ASSERT_INSTANCE_ARRAY_OF_BASIC_TYPE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_array< \
                                                                 typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                               >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that the provided name should be of a function. */
#define SN_CT_ASSERT_FUNCTION( FUNC_NAME ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_function< decltype(FUNC_NAME) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of class type.
*
*     \tparam TYPE    The type which is required to be of class type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CLASS_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_class< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be an object. */
#define SN_CT_ASSERT_OBJECT( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< \
                                                                 typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                               >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be a typelist.
*
*     \tparam TYPE    The type which is required to be a typelist.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPELIST() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_typelist< TYPE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that a given type should be of pointer type.
*
*     \tparam TYPE    The type which is required to be of pointer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be a pointer. */
#define SN_CT_ASSERT_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_pointer< \
                                                                   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
                                                                 >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of pointer to const type.
*
*     \tparam TYPE    The type which is required to be of pointer to const type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TO_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_pointer_to_const< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be a pointer to const. */
#define SN_CT_ASSERT_PTR_TO_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::is_pointer_to_const< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of function pointer type.
*
*     \tparam TYPE    The type which is required to be of function pointer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FUNCTION_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_function_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be a function pointer. */
#define SN_CT_ASSERT_FUNCTION_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::is_function_pointer< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of pointer to member function type.
*
*     \tparam TYPE    The type which is required to be of pointer to member function type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MEMBER_FUNCTION_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_member_function_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be of pointer to member function type. */
#define SN_CT_ASSERT_MEMBER_FUNCTION_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::is_member_function_pointer< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be reference.
*
*     \tparam TYPE    The type which is required to be reference.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_reference< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be a reference. */
#define SN_CT_ASSERT_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_reference< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be a const reference.
*
*     \tparam TYPE    The type which is required to be a const reference.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const_reference< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be of const reference type. */
#define SN_CT_ASSERT_CONST_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const_reference< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be an rvalue reference.
*
*     \tparam TYPE    The type which is required to be an rvalue reference.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_RVALUE_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_rvalue_reference< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that a given type should not be an rvalue reference.
*
*     \tparam TYPE    The type which is required to not be an rvalue reference.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::not_rvalue_reference< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should not be an rvalue reference. */
#define SN_CT_ASSERT_NOT_RVALUE_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::not_rvalue_reference< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be const qualified.
*
*     \tparam TYPE    The type which is required to be const qualified.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be const qualified. */
#define SN_CT_ASSERT_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should not be const qualified.
*
*     \tparam TYPE    The type which is required to not be const qualified.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_const< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should not be const qualified. */
#define SN_CT_ASSERT_NOT_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_const< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be volatile qualified.
*
*     \tparam TYPE    The type which is required to be volatile qualified.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOLATILE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_volatile< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be volatile qualified. */
#define SN_CT_ASSERT_VOLATILE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_volatile< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should not be volatile qualified.
*
*     \tparam TYPE    The type which is required to not be volatile qualified.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_VOLATILE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_volatile< TYPE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should not be volatile qualified. */
#define SN_CT_ASSERT_NOT_VOLATILE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_volatile< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of unsigned integer type.
*
*     \tparam TYPE    The type which is required to be of unsigned integer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_UNSIGNED_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_unsigned< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be of unsigned integer type. */
#define SN_CT_ASSERT_UNSIGNED( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::is_unsigned< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type should be of signed integer type.
*
*     \tparam TYPE    The type which is required to be of signed integer type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SIGNED_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
   typetraits::is_signed< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value 
                                         >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that a given instance should be of signed integer type. */
#define SN_CT_ASSERT_SIGNED( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::is_signed< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >::value \
                                         >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given instance should be an rvalue. */
#define SN_CT_ASSERT_RVALUE( ... ) \
   do { if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_rvalue(__VA_ARGS__) >::ASSERT_FAILED ) break; } while(false)
/**   A compile-time constraint that a given instance should be an lvalue. */
#define SN_CT_ASSERT_LVALUE( ... ) \
   do { if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue(__VA_ARGS__) >::ASSERT_FAILED ) break; } while(false)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DEBUG mode - in case all the above typetrait devices didn't quite cut it, these certainly should.
//////////////////////////////////////////////////////////////////////////////////////////////////////


/**   A compile-time constraint that two types must be the same.
*
*     \tparam TYPE1    A given type which is required to be the same as TYPE2.
*     \tparam TYPE2    A given type which is required to be the same as TYPE1.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SAME_TYPENAME() {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
   typetraits::are_type_similar< 
                                 typename typetraits::impl::NoCVQ_R<TYPE1>::type, 
                                 typename typetraits::impl::NoCVQ_R<TYPE2>::type 
                               >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that two types must have the same typename.
*
*     \tparam TYPE1    A given type which is required to have the same typename as TYPE2.
*     \tparam TYPE2    A given type which is required to have the same typename as TYPE1.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_SAME_TYPENAME() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< TYPE1, TYPE2 >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that two instances must be of the same type.
*
*     \tparam TYPE1    Type of instance1 which is required to be of the same type as TYPE2.
*     \tparam TYPE2    Type of instance2 which is required to be of the same type as TYPE1.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SAME_TYPE( const TYPE1 &, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< TYPE1, TYPE2 >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that two instances must be strictly of the same type.
*
*     \tparam INST1    A given instance which is required to be of the same type as TYPE2.
*     \tparam INST2    A given instance which is required to be of the same type as TYPE1.
*/
#define SN_CT_ASSERT_STRICTLY_SAME_TYPE( INST1, INST2 ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::are_type_similar< decltype(INST1), decltype(INST2) >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given instance must be of a specific type.
*
*     \tparam TYPE     The type specified for the instance.
*     \tparam GTYPE    A given instance which is required to be of the specified type.
*/
template< class TYPE, class GTYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPE( const GTYPE & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< 
   typetraits::are_type_similar< 
                                 typename typetraits::impl::NoCVQ_R<GTYPE>::type, 
                                 typename typetraits::impl::NoCVQ_R<TYPE>::type 
                               >::value >::ASSERT_FAILED ) return;
}



#define SN_CT_ASSERT_STRICTLY_TYPE( INST, ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< decltype(INST), __VA_ARGS__ >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that a given type must be in a specified typelist.
*
*     \tparam TYPE        The type which is required to be in the specified typelist.
*     \tparam TYPELIST    The specified typelist must be of type SN_CT_TYPELIST.
*/
template< class TYPE, class TYPELIST >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPE_IN_TYPELIST() {
   if( !typetraits::impl::CT_ASSERT_ERROR< TYPELIST:: template isInList<TYPE>() >::ASSERT_FAILED ) return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DEBUG mode - OOP Compile-time constraints for basic inheritance and operator checks
/////////////////////////////////////////////////////////////////////////////////////////

/**   A compile-time constraint that a class has to be derived from another.
*
*     \tparam DER    The derived class.
*     \tparam BASE   The base class.
*/
template< class DER, class BASE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_DERIVED_FROM() {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::is_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that an object has to be of a class derived from another, of whose type is the object provided as the
*     second argument.
*
*     \tparam DER    The derived class.
*     \tparam BASE   The base class.
*/
template< class DER, class BASE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INSTANCE_DERIVED_FROM( const DER &, const BASE & ) {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::is_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that a class has to be derived from at least one class contained in a specified typelist.
*
*     \tparam CLS    The derived class.
*     \tparam TL     The specified typelist (of SN_CT_TYPELIST) which is required to have at least one class as the base class of CLS.
*/
template< class CLS, class TL >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER() {
   using STRIPPED_CLS = typename typetraits::impl::NoCVQ_R<CLS>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_CLS >::value && 
                                           typetraits::is_typelist< TL >::value && 
                                           typetraits::is_derived_from_list_member< STRIPPED_CLS, TL >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the given object is of a class which is derived from any class in a specified typelist.
*
*     \tparam CLS    The derived class.
*     \tparam TL     The specified typelist which is required to have atleast one class which is the base class of CLS.
*/
template< class TL, class CLS >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INSTANCE_DERIVED_FROM_LIST_MEMBER( const CLS & ) {
   using STRIPPED_CLS = typename typetraits::impl::NoCVQ_R<CLS>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_CLS >::value && 
                                           typetraits::is_typelist< TL >::value && 
                                           typetraits::is_derived_from_list_member< STRIPPED_CLS, TL >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type DER must NOT be derived from BASE */
/**   A compile-time constraint that a class should not be derived from a specified class.
*
*     \tparam DER      A class which should not be derived from BASE.
*     \tparam BASE     A class which is not the base of DER.
*/
template< class DER, class BASE >
inline void SN_CT_ASSERT_NOT_DERIVED_FROM() {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::not_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that there is no inheritance relationship between the classes of the given objects.
*
*     \tparam DER    A class which should not be derived from BASE.
*     \tparam BASE   A class which is not the base of DER.
*/
template< class DER, class BASE >
inline void SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( const DER &, const BASE & ) {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::not_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that there the provided type must be of callable type: function pointer, functor class or pointer to 
*     member function.
*
*     \tparam TYPE    A class which should be callable.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CALLABLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_callable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE >( nullptr ) ) 
                                                                  >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that there the provided instance must be callable: function pointer, functor or pointer to member function.
*/
#define SN_CT_ASSERT_CALLABLE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_callable< \
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >( nullptr ) ) \
                                                                  >::value >::ASSERT_FAILED ) break; \
} while(false)



/**   A compile-time constraint that the provided functor must be callable with the specified parameters.
*
*     \tparam CAL     A class which should be of functor type. The provided argument is an object of this type.
*     \tparam PARAM   A parameter pack of the parameters with which the functor can be called.
*/
template< class CAL, class... PARAM >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FUNCTOR_CAN_CALL() {
   using STRIPPED_CAL = typename typetraits::impl::NoCVQ_R<CAL>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_CAL >::value &&
                                           typetraits::can_call< STRIPPED_CAL, SN_CT_TYPELIST<PARAM...> >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the provided function pointer/pointer to member function must be callable with the specified 
*     parameters.
*
*     \tparam CAL     A type which is either a function pointer or a pointer to a member function.
*     \tparam PARAM   A parameter pack of the parameters with which the CAL can be called.
*/
template< class... PARAM, class CAL >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_CALL( const CAL ) {
   using STRIPPED_CAL = typename typetraits::impl::NoCVQ_R<CAL>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_call< STRIPPED_CAL, SN_CT_TYPELIST<PARAM...> >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided class must be trivially constructible.
*
*     \tparam TYPE   The provided class.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_trivially_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided class must be copy-constructible.
*
*     \tparam TYPE   The provided class.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_copy_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided class must be move-constructible.
*
*     \tparam TYPE   The provided class.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_move_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided class must be constructible.
*
*     \tparam TYPE    The provided class.
*     \tparam PARAM   The parameter pack containing the parameters with which the provided class can be constructed.
*/
template< class TYPE, class... PARAM >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< 
                                           typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_constructible< STRIPPED_TYPE, SN_CT_TYPELIST<PARAM...> >::value 
                                         >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided types must be equality comparable.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_strictly_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                              >::value>::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the provided instances must be equality comparable.
*
*     \tparam TYPE1   The type of the first instance.
*     \tparam TYPE2   The type of the second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_COMPARABLE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_strictly_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                              >::value>::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the provided types must be <, >, <=, >= and == comparable.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COMPARABLE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                     >::value>::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the provided instances must be <, >, <=, >= and == comparable.
*
*     \tparam TYPE1   The type of the first instance.
*     \tparam TYPE2   The type of the second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COMPARABLE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                     >::value>::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that instances of the first type can be copied from those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_copy_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
                                                                         >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that first instance can be copied from the second.
*
*     \tparam TYPE1   The type of the first instance.
*     \tparam TYPE2   The type of the second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_ASSIGNABLE( const TYPE1 & INST, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( INST ) && typetraits::is_copy_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that objects of the first class can be moved from those of the second.
*
*     \tparam TYPE1   The first class.
*     \tparam TYPE2   The second class.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_move_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
                                                                         >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first object can be moved from the second.
*
*     \tparam TYPE1   The class of first object.
*     \tparam TYPE2   The class of second object.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_ASSIGNABLE( const TYPE1 & INST1, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( INST1 ) && typetraits::is_move_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that instances of the first type must be assignable with values of those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( TYPE1() ) && typetraits::is_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first instance must be assignable with the value of the second.
*
*     \tparam TYPE1   The type of first instance.
*     \tparam TYPE2   The type of second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ASSIGNABLE( const TYPE1 &, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( TYPE1() ) && typetraits::is_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that instances of the first type must be capable of addition with those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_ADD_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_add< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                              >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first instance must be capable of addition with the value of the second.
*
*     \tparam TYPE1   The type of first instance.
*     \tparam TYPE2   The type of second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_ADD( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_add< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                              >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the instances of the first type must be capable of subtraction with those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_SUBTRACT_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_subtract< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                   >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first instance must be capable of subtraction with the value of the second.
*
*     \tparam TYPE1   The type of first instance.
*     \tparam TYPE2   The type of second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_SUBTRACT( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_subtract< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                   >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the instances of the first type must be capable of multiplication with those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_MULTIPLY_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_multiply< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                   >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first instance must be capable of multiplication with the value of the second.
*
*     \tparam TYPE1   The type of first instance.
*     \tparam TYPE2   The type of second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_MULTIPLY( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_multiply< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                   >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the instances of the first type must be capable of division with those of the second.
*
*     \tparam TYPE1   The first type.
*     \tparam TYPE2   The second type.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_DIVIDE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_divide< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                 >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the first instance must be capable of division with the value of the second.
*
*     \tparam TYPE1   The type of first instance.
*     \tparam TYPE2   The type of second instance.
*/
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_DIVIDE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_divide< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
                                                                 >::value >::ASSERT_FAILED ) return;
}



/**   A compile-time constraint that the instances of the provided type must be capable of being assigned, added with and subtracted from *     instances of the same type. This definition has been broadened to allow for entities such as matrices and vectors, which may not be 
*     capable of being multiplied with or divided by themselves.
*
*     \tparam TYPE   The arithmetic type.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARITHMETIC_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_arithmetic< 
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) 
                                                                    >::value >::ASSERT_FAILED ) return;
}
/**   A compile-time constraint that the provided instance must be capable of being assigned, added with and subtracted from      
*     instances of its own type. This definition has been broadened to allow for entities such as matrices and vectors, which may not be 
*     capable of being multiplied with or divided by themselves.
*
*     \tparam TYPE   The type of the provided instance.
*/
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARITHMETIC( const TYPE & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_arithmetic< 
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) 
                                                                    >::value >::ASSERT_FAILED ) return;
}



#endif   // NDEBUG

}   // namespace simpleNewton

#endif
