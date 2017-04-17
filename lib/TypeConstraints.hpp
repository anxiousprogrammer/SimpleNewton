#ifndef TYPECONSTRAINTS_HPP
#define TYPECONSTRAINTS_HPP

#include <iostream>
#include <cstdlib>

#include <Asserts.hpp>
#include <BasicTypeTraits.hpp>

/**||**************************************************************************************************************************************
*
*   Description: Compile-time Asserts based on BasicTypeTraits.hpp
*
|**************************************************************************************************************************************///+

namespace simpleNewton {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

template< class TYPE >
struct TypeConstraints_CPPHackClass {};



namespace typetraits {
namespace impl {
// Error signal function
template< bool > struct CT_ASSERT_ERROR;
template<> struct CT_ASSERT_ERROR<true>  { enum { ASSERT_FAILED = false }; };
template<> struct CT_ASSERT_ERROR<false> {};
}   // namespace impl
}   // namespace typetraits



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   RELEASE mode constraints: requirements. Use only when absolutely necessary.
/////////////////////////////////////////////////////////////////////////////////

/* Constraint - Compile time assert */
template< bool constexpr_expr >
inline void __attribute__( (optimize("O0")) ) SN_CT_REQUIRE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< static_cast<bool>( constexpr_expr ) >::ASSERT_FAILED ) return;
}



#ifdef NDEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   RELEASE mode 
//////////////////

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
inline void SN_CT_ASSERT_ARRAY_TYPE() {}
#define SN_CT_ASSERT_ARRAY( ... )

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

template< class TYPE >
inline void SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE() {}

template< class TYPE, class TL >
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

template< class CLS, class MEMB_FUNC >
inline void SN_CT_ASSERT_HAS_MEMBER_FUNCTION() {}

template< class TYPE >
inline void SN_CT_ASSERT_ARITHMETIC_TYPE() {}
template< class TYPE >
inline void SN_CT_ASSERT_ARITHMETIC( const TYPE & ) {}

#else

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode 
//////////////////



/* Constraint - Compile time assert */
template< bool constexpr_expr >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT() {
   if( !typetraits::impl::CT_ASSERT_ERROR< static_cast<bool>( constexpr_expr ) >::ASSERT_FAILED ) return;
}



/* Constraint - number of template arguments must be determinate */
template< int NUM, class... ARG >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NUM_TEMPLATE_ARG() {
   if( !typetraits::impl::CT_ASSERT_ERROR< (NUM == typetraits::argument_count<ARG...>::value) >::ASSERT_FAILED ) return;
}



/* Constraint - type must be void type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOID_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_void< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be integer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INT_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_integer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INT( ... ) \
   do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_integer< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
   } while(false)


/* Constraint - instance/type must NOT be integer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_INT_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_integer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_INT( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_integer< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be floating point type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FP_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_floating_point< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_FP( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_floating_point< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must NOT be floating point type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_FP_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_floating_point< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_FP( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_floating_point< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be small type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SMALL_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_small_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_SMALL( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_small_t< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be large type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_LARGE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_large_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_LARGE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_large_t< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be ID type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ID_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_ID_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_ID( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_ID_t< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be string type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRING_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_string_t< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_STRING( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_string_t< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be bool type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_BOOL_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_bool< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_BOOL( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_bool< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be array type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARRAY_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_array< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_ARRAY( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_array< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - must be function type */
#define SN_CT_ASSERT_FUNCTION( FUNC_NAME ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_function< decltype(FUNC_NAME) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be class type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CLASS_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_OBJECT( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPELIST() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_typelist< TYPE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be pointer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_pointer< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be pointer to const type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TO_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_pointer_to_const< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_PTR_TO_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_pointer_to_const< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be function pointer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FUNCTION_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_function_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_FUNCTION_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_function_pointer< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be member function pointer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MEMBER_FUNCTION_PTR_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_member_function_pointer< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_MEMBER_FUNCTION_PTR( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_member_function_pointer< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_reference< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_reference< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be const reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const_reference< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CONST_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const_reference< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - type must be rvalue reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_RVALUE_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_rvalue_reference< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must NOT be rvalue reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_rvalue_reference< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_RVALUE_REFERENCE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_rvalue_reference< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be const qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_const< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be NOT be const qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_CONST_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_const< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_CONST( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_const< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be volatile qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOLATILE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_volatile< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_VOLATILE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_volatile< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must NOT be volatile qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_VOLATILE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_volatile< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_VOLATILE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::not_volatile< decltype(__VA_ARGS__) >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be unsigned qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_UNSIGNED_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_unsigned< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_UNSIGNED( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_unsigned< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance/type must be signed qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SIGNED_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_signed< typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_SIGNED( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_signed< \
   typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - instance must be rvalue/lvalue */
#define SN_CT_ASSERT_RVALUE( ... ) \
   do { if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_rvalue(__VA_ARGS__) >::ASSERT_FAILED ) break; } while(false)
#define SN_CT_ASSERT_LVALUE( ... ) \
   do { if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue(__VA_ARGS__) >::ASSERT_FAILED ) break; } while(false)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode - in case all the above typetrait devices didn't quite cut it, these certainly should.
//////////////////////////////////////////////////////////////////////////////////////////////////////

/* IMPORTANT, GENERAL Constraint - typetraits must be the same */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SAME_TYPENAME() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< typename typetraits::impl::NoCVQ_R<TYPE1>::type, typename typetraits::impl::NoCVQ_R<TYPE2>::type >::value >::ASSERT_FAILED ) return;
}



template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_SAME_TYPENAME() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< TYPE1, TYPE2 >::value >::ASSERT_FAILED ) return;
}



template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SAME_TYPE( const TYPE1 &, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< TYPE1, TYPE2 >::value >::ASSERT_FAILED ) return;
}



#define SN_CT_ASSERT_STRICTLY_SAME_TYPE( INST1, INST2 ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< \
   typetraits::are_type_similar< decltype(INST1), decltype(INST2) >::value >::ASSERT_FAILED ) break; \
} while(false)



template< class TYPE, class GTYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPE( const GTYPE & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< typename typetraits::impl::NoCVQ_R<GTYPE>::type, typename typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}



#define SN_CT_ASSERT_STRICTLY_TYPE( INST, ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_type_similar< decltype(INST), __VA_ARGS__ >::value >::ASSERT_FAILED ) break; \
} while(false)



template< class TYPE, class TYPELIST >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TYPE_IN_TYPELIST() {
   if( !typetraits::impl::CT_ASSERT_ERROR< TYPELIST:: template isInList<TYPE>() >::ASSERT_FAILED ) return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode - OOP Compile-time constraints for basic inheritance and operator checks
/////////////////////////////////////////////////////////////////////////////////////////

/* Constraint - instance/type DER must be derived from BASE */
template< class DER, class BASE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_DERIVED_FROM() {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::is_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}
template< class DER, class BASE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INSTANCE_DERIVED_FROM( const DER &, const BASE & ) {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::is_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type CLS must be derived from a member of the typelist TL */
template< class CLS, class TL >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER() {
   using STRIPPED_CLS = typename typetraits::impl::NoCVQ_R<CLS>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_CLS >::value && 
                                           typetraits::is_typelist< TL >::value && 
                                           typetraits::is_derived_from_list_member< STRIPPED_CLS, TL >::value >::ASSERT_FAILED ) return;
}
template< class TL, class CLS >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INSTANCE_DERIVED_FROM_LIST_MEMBER( const CLS & ) {
   using STRIPPED_CLS = typename typetraits::impl::NoCVQ_R<CLS>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_CLS >::value && 
                                           typetraits::is_typelist< TL >::value && 
                                           typetraits::is_derived_from_list_member< STRIPPED_CLS, TL >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type DER must NOT be derived from BASE */
template< class DER, class BASE >
inline void SN_CT_ASSERT_NOT_DERIVED_FROM() {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::not_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}
template< class DER, class BASE >
inline void SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( const DER &, const BASE & ) {
   using STRIPPED_DER = typename typetraits::impl::NoCVQ_R<DER>::type;
   using STRIPPED_BASE = typename typetraits::impl::NoCVQ_R<BASE>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_DER >::value && 
                                           typetraits::is_class< STRIPPED_BASE >::value && 
                                           typetraits::not_derived_from< STRIPPED_DER, STRIPPED_BASE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be callable */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CALLABLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_callable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CALLABLE( ... ) \
do { \
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_callable< \
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<decltype(__VA_ARGS__)>::type >( nullptr ) ) \
   >::value >::ASSERT_FAILED ) break; \
} while(false)



/* Constraint - type must be trivially constructible */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_trivially_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - type must be copy constructible */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_copy_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - type must be move constructible */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_move_constructible< STRIPPED_TYPE >::value >::ASSERT_FAILED ) return;
}



/* Constraint - type must be constructible */
template< class TYPE, class PARAM_TYPELIST >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONSTRUCTIBLE_TYPE() {
   using STRIPPED_TYPE = typename typetraits::impl::NoCVQ_R<TYPE>::type;
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_class< STRIPPED_TYPE >::value && 
                                           typetraits::is_constructible< STRIPPED_TYPE, PARAM_TYPELIST >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be strictly comparable with another specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_strictly_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value>::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_COMPARABLE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_strictly_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value>::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be comparable with another specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COMPARABLE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value>::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COMPARABLE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::are_comparable< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value>::ASSERT_FAILED ) return;
}



/* Constraint - a specific instance/type must be COPY assignable to instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_copy_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COPY_ASSIGNABLE( const TYPE1 & INST, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( INST ) && typetraits::is_copy_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - a specific instance/type must be MOVE assignable to instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_move_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_MOVE_ASSIGNABLE( const TYPE1 & INST1, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( INST1 ) && typetraits::is_move_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - a specific instance/type must be assignable to instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ASSIGNABLE_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( TYPE1() ) && typetraits::is_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ASSIGNABLE( const TYPE1 &, const TYPE2 & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_lvalue( TYPE1() ) && typetraits::is_assignable< 
   decltype( typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be addable with a specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_ADD_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_add< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_ADD( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_add< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - a specific instance/type must be subtractible from instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_SUBTRACT_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_subtract< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_SUBTRACT( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_subtract< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be multipliable with a specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_MULTIPLY_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_multiply< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_MULTIPLY( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_multiply< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - a specific instance/type must be able to divide instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_DIVIDE_TYPE() {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_divide< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_DIVIDE( const TYPE1 &, const TYPE2 & ) {
   using STRIPPED_TYPE1 = typename typetraits::impl::NoCVQ_R<TYPE1>::type;
   using STRIPPED_TYPE2 = typename typetraits::impl::NoCVQ_R<TYPE2>::type;
   
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::can_divide< 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE1 >( nullptr ) ), 
   decltype( typetraits::impl::Class_Type_Return< STRIPPED_TYPE2 >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be arithmetic (with itself) */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARITHMETIC_TYPE() {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_arithmetic< 
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARITHMETIC( const TYPE & ) {
   if( !typetraits::impl::CT_ASSERT_ERROR< typetraits::is_arithmetic< 
   decltype( typetraits::impl::Class_Type_Return< typename typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) 
   >::value >::ASSERT_FAILED ) return;
}



#endif   // NDEBUG

}   // namespace simpleNewton

#endif
