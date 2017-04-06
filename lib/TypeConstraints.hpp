#ifndef TYPECONSTRAINTS_HPP
#define TYPECONSTRAINTS_HPP

#include <BasicTypeTraits.hpp>
/**||***************************************************************************************************************************************
*
*   Description: Compile-time Asserts based on BasicTypeTraits.hpp
*
|***************************************************************************************************************************************///+

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   HACK: TEMPLATE/INLINE OR NO, WE WANT CPP!
///////////////////////////////////////////////
template< class T >
struct TypeConstraints_CPPHackClass {};

#ifdef NDEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   RELEASE mode 
//////////////////

template< class TYPE >
inline void SN_CT_ASSERT_VOID_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_INT_TYPE() {}
#define SN_CT_ASSERT_INT( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_INT_TYPE() {}
#define SN_CT_ASSERT_NOT_INT( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_FLOAT_TYPE() {}
#define SN_CT_ASSERT_FLOAT( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_FLOAT_TYPE() {}
#define SN_CT_ASSERT_NOT_FLOAT( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_SMALL_TYPE() {}
#define SN_CT_ASSERT_SMALL( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_LARGE_TYPE() {}
#define SN_CT_ASSERT_LARGE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_ID_TYPE() {}
#define SN_CT_ASSERT_ID( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_STRING_TYPE() {}
#define SN_CT_ASSERT_STRING( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_BOOL_TYPE() {}
#define SN_CT_ASSERT_BOOL( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_ARRAY_TYPE() {}
#define SN_CT_ASSERT_ARRAY( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_FUNCTION_TYPE() {}
#define SN_CT_ASSERT_FUNCTION( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_CLASS_TYPE() {}
#define SN_CT_ASSERT_CLASS( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_PTR_TYPE() {}
#define SN_CT_ASSERT_PTR( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_PTR_TO_CONST_TYPE() {}
#define SN_CT_ASSERT_PTR_TO_CONST( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_FUNCTION_PTR_TYPE() {}
#define SN_CT_ASSERT_FUNCTION_PTR( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_REFERENCE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_CONST_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_CONST_REFERENCE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_RVALUE_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_RVALUE_REFERENCE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE() {}
#define SN_CT_ASSERT_NOT_RVALUE_REFERENCE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_CONST_TYPE() {}
#define SN_CT_ASSERT_CONST( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_CONST_TYPE() {}
#define SN_CT_ASSERT_NOT_CONST( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_VOLATILE_TYPE() {}
#define SN_CT_ASSERT_VOLATILE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_NOT_VOLATILE_TYPE() {}
#define SN_CT_ASSERT_NOT_VOLATILE( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_UNSIGNED_TYPE() {}
#define SN_CT_ASSERT_UNSIGNED( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_SIGNED_TYPE() {}
#define SN_CT_ASSERT_SIGNED( VAR )

template< class TYPE >
inline void SN_CT_ASSERT_RVALUE( TYPE && INST ) {}

template< class TYPE >
inline void SN_CT_ASSERT_LVALUE( TYPE && INST ) {}

template< class TYPE >
inline void SN_CT_ASSERT_SAME_TYPENAME() {}
inline void SN_CT_ASSERT_STRICTLY_SAME_TYPENAME() {}
#define SN_CT_ASSERT_SAME_TYPE( INST )
#define SN_CT_ASSERT_STRICTLY_SAME_TYPE( INST )
#define SN_CT_ASSERT_TYPE( INST, TYPE )
#define SN_CT_ASSERT_STRICTLY_TYPE( INST, TYPE )



template< class DER, class BASE >
inline void SN_CT_ASSERT_DERIVED_FROM() {}
#define SN_CT_ASSERT_INSTANCE_DERIVED_FROM( DER, BASE )

template< class DER, class BASE >
inline void SN_CT_ASSERT_STRICTLY_DERIVED_FROM() {}
#define SN_CT_ASSERT_INSTANCE_STRICTLY_DERIVED_FROM( DER, BASE )

template< class DER, class BASE >
inline void SN_CT_ASSERT_NOT_DERIVED_FROM() {}
#define SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( DER, BASE )

template< class DER, class BASE >
inline void SN_CT_ASSERT_STRICTLY_NOT_DERIVED_FROM() {}
#define SN_CT_ASSERT_INSTANCE_STRICTLY_NOT_DERIVED_FROM( DER, BASE )

template< class TYPE >
inline void SN_CT_ASSERT_CALLABLE_TYPE() {}
#define SN_CT_ASSERT_CALLABLE( INST )

template< class TYPE >
inline void SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE() {}

template< class TYPE >
inline void SN_CT_ASSERT_CONSTRUCTIBLE_TYPE() {}

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE() {}
#define SN_CT_ASSERT_STRICTLY_COMPARABLE( INST1, INST2 )

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_COMPARABLE_TYPE() {}
#define SN_CT_ASSERT_COMPARABLE( INST1, INST2 )

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_ASSIGNABLE_TYPE() {}
#define SN_CT_ASSERT_STRICTLY_ASSIGNABLE( INST1, INST2 )

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_ADD_TYPE() {}
#define SN_CT_ASSERT_CAN_ADD( INST1, INST2 )

template< class TYPE2, class TYPE1 >
inline void SN_CT_ASSERT_CAN_SUBTRACT_TYPE() {}
#define SN_CT_ASSERT_CAN_SUBTRACT( INST2, INST1 )

template< class TYPE1, class TYPE2 >
inline void SN_CT_ASSERT_CAN_MULTIPLY_TYPE() {}
#define SN_CT_ASSERT_CAN_MULTIPLY( INST1, INST2 )

template< class TYPE2, class TYPE1 >
inline void SN_CT_ASSERT_CAN_DIVIDE_TYPE() {}
#define SN_CT_ASSERT_CAN_DIVIDE( INST2, INST1 )

template< class TYPE >
inline void SN_CT_ASSERT_ARITHMETIC_TYPE() {}
#define SN_CT_ASSERT_ARITHMETIC( INST )

#else

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode 
//////////////////


namespace simpleNewton {
namespace typetraits {
namespace impl {
// Error signal function
template< bool > struct CT_ASSERT_ERROR;
template<> struct CT_ASSERT_ERROR<true>  { enum { ASSERT_FAILED = false }; };
template<> struct CT_ASSERT_ERROR<false> {};
}   // namespace impl
}   // namespace typetraits
}   // namespace simpleNewton



/* Constraint - instance/type must be void type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOID_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_void< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be integer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_INT_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_integer< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INT( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_integer< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must NOT be integer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_INT_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_integer< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_INT( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_integer< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be float type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FLOAT_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_floating_point< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_FLOAT( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_floating_point< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must NOT be float type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_FLOAT_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_floating_point< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_FLOAT( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_floating_point< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) return; } while(false)



/* Constraint - instance/type must be small type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SMALL_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_small_t< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_SMALL( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_small_t< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be large type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_LARGE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_large_t< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_LARGE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_large_t< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be ID type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ID_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_id_t< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_ID( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_id_t< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be string type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRING_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_string_t< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_STRING( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_string_t< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be bool type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_BOOL_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_bool< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_BOOL( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_bool< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be array type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ARRAY_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_array< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_ARRAY( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_array< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be function type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FUNCTION_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_function< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_FUNCTION( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_function< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be class type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CLASS_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_class< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CLASS( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_class< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be pointer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_pointer< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_PTR( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_pointer< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be pointer to const type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_PTR_TO_CONST_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_pointer_to_const< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_PTR_TO_CONST( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_pointer_to_const< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be function pointer type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_FUNCTION_PTR_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_function_pointer< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_FUNCTION_PTR( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_function_pointer< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_REFERENCE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_REFERENCE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be const reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_REFERENCE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_const_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CONST_REFERENCE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_const_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be rvalue reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_RVALUE_REFERENCE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_rvalue_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_RVALUE_REFERENCE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_rvalue_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must NOT be rvalue reference type */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_rvalue_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_RVALUE_REFERENCE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_rvalue_reference< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be const qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONST_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_const< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CONST( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_const< decltype(VAR) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be NOT be const qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_CONST_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_const< TYPE >::ASSERT_FAILED >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_CONST( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_const< decltype(VAR) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be volatile qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_VOLATILE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_volatile< TYPE >::ASSERT_FAILED >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_VOLATILE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_volatile< decltype(VAR) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must NOT be volatile qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_NOT_VOLATILE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_volatile< TYPE >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_NOT_VOLATILE( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_volatile< decltype(VAR) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be unsigned qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_UNSIGNED_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_unsigned< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_UNSIGNED( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_unsigned< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be signed qualified */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SIGNED_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_signed< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_SIGNED( VAR ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_signed< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(VAR)>::type >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be rvalue/lvalue */
#define SN_CT_ASSERT_RVALUE( INST ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_rvalue(INST) >::ASSERT_FAILED ) break; } while(false)
#define SN_CT_ASSERT_LVALUE( INST ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_lvalue(INST) >::ASSERT_FAILED ) break; } while(false)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode - in case all the above typetrait devices didn't quite cut it, these certainly should.
//////////////////////////////////////////////////////////////////////////////////////////////////////

/* IMPORTANT, GENERAL Constraint - typetraits must be the same */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_SAME_TYPENAME() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type, typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >::value >::ASSERT_FAILED ) return;
}

template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_SAME_TYPENAME() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< TYPE1, TYPE2 >::value >::ASSERT_FAILED ) return;
}

#define SN_CT_ASSERT_SAME_TYPE( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type, typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >::value >::ASSERT_FAILED ) break; } while(false)

#define SN_CT_ASSERT_STRICTLY_SAME_TYPE( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< decltype(INST1), decltype(INST2) >::value >::ASSERT_FAILED ) break; } while(false)

#define SN_CT_ASSERT_TYPE( INST, TYPE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST)>::type, typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >::value >::ASSERT_FAILED ) break; } while(false)

#define SN_CT_ASSERT_STRICTLY_TYPE( INST, TYPE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_type_similar< decltype(INST), TYPE >::value >::ASSERT_FAILED ) break; } while(false)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   DEBUG mode - OOP Compile-time constraints for basic inheritance and operator checks
/////////////////////////////////////////////////////////////////////////////////////////

/* Constraint - instance/type DER must be derived from BASE */
template< class DER, class BASE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_DERIVED_FROM() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<DER>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<BASE>::type >(nullptr) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INSTANCE_DERIVED_FROM( DER, BASE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(DER)>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(BASE)>::type >(nullptr) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type DER must be strictly derived from BASE */
template< class DER, class BASE >
inline void SN_CT_ASSERT_STRICTLY_DERIVED_FROM() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_strictly_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<DER>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<BASE>::type >(nullptr) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INSTANCE_STRICTLY_DERIVED_FROM( DER, BASE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_strictly_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(DER)>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(BASE)>::type >(nullptr) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type DER must NOT be derived from BASE */
template< class DER, class BASE >
inline void SN_CT_ASSERT_NOT_DERIVED_FROM() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<DER>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<BASE>::type >(nullptr) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( DER, BASE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(DER)>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(BASE)>::type >(nullptr) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type DER must be strictly NOT derived from BASE */
template< class DER, class BASE >
inline void SN_CT_ASSERT_STRICTLY_NOT_DERIVED_FROM() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_strictly_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<DER>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<BASE>::type >(nullptr) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_INSTANCE_STRICTLY_NOT_DERIVED_FROM( DER, BASE ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::not_strictly_derived_from< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(DER)>::type >(nullptr) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(BASE)>::type >(nullptr) ) >::value >::ASSERT_FAILED ) return; } while(false)



/* Constraint - instance/type must be callable */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CALLABLE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_callable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CALLABLE( INST ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_callable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be trivially constructible */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_trivially_constructible< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be constructible */
template< class TYPE, class... PARAM >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CONSTRUCTIBLE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_constructible< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ), PARAM... >::value >::ASSERT_FAILED ) return;
}



/* Constraint - instance/type must be strictly comparable with another specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_strictly_comparable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ) >::value>::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_STRICTLY_COMPARABLE( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_strictly_comparable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be comparable with another specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_COMPARABLE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_comparable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_COMPARABLE( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::are_comparable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - a specific instance/type must be assignable to instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_ASSIGNABLE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_assignable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< TYPE1 >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< TYPE2 >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_ASSIGNABLE( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_assignable< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be addable with a specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_ADD_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_add< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CAN_ADD( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_add< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - a specific instance/type must be subtractible from instance/type */
template< class TYPE2, class TYPE1 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_SUBTRACT_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_subtract< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CAN_SUBTRACT( INST2, INST1 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_subtract< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be multipliable with a specific instance/type */
template< class TYPE1, class TYPE2 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_MULTIPLY_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_multiply< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CAN_MULTIPLY( INST1, INST2 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_multiply< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - a specific instance/type must be able to divide instance/type */
template< class TYPE2, class TYPE1 >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_CAN_DIVIDE_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_divide< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE2>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE1>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_CAN_DIVIDE( INST2, INST1 ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_divide< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST2)>::type >( nullptr ) ), decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST1)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



/* Constraint - instance/type must be arithmetic (with itself) */
template< class TYPE >
inline void __attribute__( (optimize("O0")) ) SN_CT_ASSERT_IS_ARITHMETIC_TYPE() {
   if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::is_arithmetic< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<TYPE>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) return;
}
#define SN_CT_ASSERT_IS_ARITHMETIC( INST ) \
   do { if( !simpleNewton::typetraits::impl::CT_ASSERT_ERROR< simpleNewton::typetraits::can_multiply< decltype( simpleNewton::typetraits::impl::Class_Type_Return< typename simpleNewton::typetraits::impl::NoCVQ_R<decltype(INST)>::type >( nullptr ) ) >::value >::ASSERT_FAILED ) break; } while(false)



#endif   // NDEBUG

#endif
