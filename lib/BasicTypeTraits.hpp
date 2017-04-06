#ifndef BASICTYPETRAITS_HPP
#define BASICTYPETRAITS_HPP

#include <Types.hpp>

// The opposite of decltype
template< class T > T&& declval();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   HACK: TEMPLATE/INLINE OR NO, WE WANT CPP!
///////////////////////////////////////////////
template< class T > struct BasicTypeTraits_CPPHackClass {};

namespace simpleNewton {
namespace typetraits {

/**||***************************************************************************************************************************************
*
*   Description: Elaborate TypeTraits implementation for the simpleNewton framework. Gentle reminder - this are all compile time checks.
*
|***************************************************************************************************************************************///+


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Declarations of typetrait structures
/////////////////////////////////////////

// Helpers, should not be in accessible namespace to client
namespace impl {
// Shave off cv qualifiers and reference types
template< class TYPE > struct NoCVQ_R;

// Deciding types
struct true_type  { enum : bool { value=true }; };
struct false_type { enum : bool { value=false }; };

// A function which takes as parameter a pointer to a template type
template< class CLS >
void ptr_accept( CLS* );
// A function which returns a pointer to a template type
template< class CLS >
CLS* ptr_return();
// Always void type: property checking template parameter enabler
template< class T > using a_void = void;
}   // namespace impl

// Declarations -> basic types
template< class TYPE > struct is_void;
template< class TYPE > struct is_integer;
template< class TYPE > struct not_integer;
template< class TYPE > struct is_floating_point;
template< class TYPE > struct not_floating_point;
template< class TYPE > struct is_small_t;
template< class TYPE > struct is_large_t;
template< class TYPE > struct is_id_t;
template< class TYPE > struct is_string_t;
template< class TYPE > struct is_bool;
template< class TYPE > struct is_array;
template< class TYPE > struct is_function;
template< class TYPE > struct is_class;

// Declarations -> pointer and reference types
template< class TYPE > struct is_pointer;
template< class TYPE > struct is_pointer_to_const;
template< class TYPE > struct is_function_pointer;
template< class TYPE > struct is_reference;
template< class TYPE > struct is_const_reference;
template< class TYPE > struct is_rvalue_reference;
template< class TYPE > struct not_rvalue_reference;

// Declarations -> const, volatile and sign qualifiers
template< class TYPE > struct is_const;
template< class TYPE > struct not_const;
template< class TYPE > struct is_volatile;
template< class TYPE > struct not_volatile;
template< typename TYPE > struct is_unsigned;
template< typename TYPE > struct is_signed;

// Functions -> is the instance rvalue or lvalue
template< class TYPE > constexpr bool is_rvalue( TYPE && INST );
template< class TYPE > constexpr bool is_lvalue( TYPE && INST );

// Declaration -> exact type similarity
template< class T1, class T2 > struct are_type_similar;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definitions of typetrait structures
/////////////////////////////////////////

namespace impl {
// Specialization -> NoCVQ_R (gets rid of cv - type qualifiers and does away with reference types)
template< class TYPE > struct NoCVQ_R                          { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< TYPE & >                { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< const TYPE >            { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< const TYPE & >          { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile TYPE >         { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile TYPE & >       { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile const TYPE >   { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile const TYPE & > { using type=TYPE; };

// An important type-changing function which accepts a class and returns pointer
// to member function, which is a defining characteristic of classes
template< class TYPE > int TYPE::* Class_Type_Return( int TYPE::* );
template< class TYPE > TYPE Class_Type_Return(...);
}   // namespace impl

// The first meal of the day!
template< class TYPE > struct is_void : public impl::false_type {};
template<> struct is_void<void> : public impl::true_type        {};

// Specialization -> int types
template< class TYPE > struct is_integer : public impl::false_type        {};
template<> struct is_integer<short> : public impl::true_type              {};
template<> struct is_integer<int> : public impl::true_type                {};
template<> struct is_integer<unsigned int> : public impl::true_type       {};
template<> struct is_integer<long> : public impl::true_type               {};
template<> struct is_integer<unsigned long> : public impl::true_type      {};
template<> struct is_integer<long long> : public impl::true_type          {};
template<> struct is_integer<unsigned long long> : public impl::true_type {};

// Specialization -> NOT int types
template< class TYPE > struct not_integer : public impl::true_type          {};
template<> struct not_integer<int> : public impl::false_type                {};
template<> struct not_integer<unsigned int> : public impl::false_type       {};
template<> struct not_integer<long> : public impl::false_type               {};
template<> struct not_integer<unsigned long> : public impl::false_type      {};
template<> struct not_integer<long long> : public impl::false_type          {};
template<> struct not_integer<unsigned long long> : public impl::false_type {};

// Specialization -> float types
template< class TYPE > struct is_floating_point : public impl::false_type {};
template<> struct is_floating_point<float> : public impl::true_type       {};
template<> struct is_floating_point<double> : public impl::true_type      {};

// Specialization -> NOT float types
template< class TYPE > struct not_floating_point : public impl::true_type {};
template<> struct not_floating_point<float> : public impl::false_type     {};
template<> struct not_floating_point<double> : public impl::false_type    {};

// Specialization -> size types
template< class TYPE > struct is_small_t : public impl::false_type {};
template<> struct is_small_t<small_t> : public impl::true_type     {};

template< class TYPE > struct is_large_t : public impl::false_type {};
template<> struct is_large_t<large_t> : public impl::true_type     {};

template< class TYPE > struct is_id_t : public impl::false_type {};
template<> struct is_id_t<double> : public impl::true_type      {};

// Specialization -> string, bool and array types
template< class TYPE > struct is_string_t : public impl::false_type {};
template<> struct is_string_t<string_t> : public impl::true_type    {};

template< class TYPE > struct is_bool : public impl::false_type {};
template<> struct is_bool<bool> : public impl::true_type        {};

template< class TYPE > struct is_array : public impl::false_type                        {};
template< class TYPE, int SIZE > struct is_array< TYPE[SIZE] > : public impl::true_type {};

// Specialization -> function and class
template< class TYPE > struct is_function : public impl::false_type                                                {};
template< class RET_TYPE, class... PARAM > struct is_function< RET_TYPE( PARAM... ) > : public impl::true_type     {};
template< class RET_TYPE, class... PARAM > struct is_function< RET_TYPE( PARAM...,... ) > : public impl::true_type {}; // printf and ellipsis

template< class TYPE > struct is_class : public impl::false_type                                        {};
template< class MEMB_TYPE, class TYPE > struct is_class< MEMB_TYPE TYPE::* > : public impl::true_type   {};

// Specialization -> pointer and reference
template< class TYPE > struct is_pointer : public impl::false_type                         {};
template< class TYPE > struct is_pointer< TYPE* > : public impl::true_type                 {};
template< class TYPE > struct is_pointer< std::unique_ptr<TYPE> > : public impl::true_type {};
template< class TYPE > struct is_pointer< std::shared_ptr<TYPE> > : public impl::true_type {};
template< class TYPE > struct is_pointer< std::weak_ptr<TYPE> > : public impl::true_type   {};

template< class TYPE > struct is_pointer_to_const : public impl::false_type                                 {};
template< class TYPE > struct is_pointer_to_const< const TYPE * > : public impl::true_type                  {};
template< class TYPE > struct is_pointer_to_const< std::unique_ptr< const TYPE > > : public impl::true_type {};
template< class TYPE > struct is_pointer_to_const< std::shared_ptr< const TYPE > > : public impl::true_type {};
template< class TYPE > struct is_pointer_to_const< std::weak_ptr< const TYPE > > : public impl::true_type   {};

template< class TYPE > struct is_function_pointer : public impl::false_type                                             {};
template< class RET_TYPE, class... PARAM > struct is_function_pointer< RET_TYPE(*)(PARAM...) > : public impl::true_type {};

template< class TYPE > struct is_reference : public impl::false_type          {};
template< class TYPE > struct is_reference< TYPE & > : public impl::true_type {};

template< class TYPE > struct is_const_reference : public impl::false_type                {};
template< class TYPE > struct is_const_reference< const TYPE & > : public impl::true_type {};

template< class TYPE > struct is_rvalue_reference : public impl::false_type           {};
template< class TYPE > struct is_rvalue_reference< TYPE && > : public impl::true_type {};

template< class TYPE > struct not_rvalue_reference : public impl::true_type             {};
template< class TYPE > struct not_rvalue_reference< TYPE && > : public impl::false_type {};

// Specialization -> type qaulification: const and non-const, signed and unsigned, volatile and non-volatile
template< class TYPE > struct is_const : public impl::false_type              {};
template< class TYPE > struct is_const< const TYPE > : public impl::true_type {};

template< class TYPE > struct not_const : public impl::true_type                {};
template< class TYPE > struct not_const< const TYPE > : public impl::false_type {};

template< class TYPE > struct is_volatile : public impl::false_type                       {};
template< class TYPE > struct is_volatile< volatile TYPE > : public impl::true_type       {};
template< class TYPE > struct is_volatile< const volatile TYPE > : public impl::true_type {};

template< class TYPE > struct not_volatile : public impl::true_type                         {};
template< class TYPE > struct not_volatile< volatile TYPE > : public impl::false_type       {};
template< class TYPE > struct not_volatile< const volatile TYPE > : public impl::false_type {};

template< typename TYPE > struct is_unsigned : public impl::false_type       {};
template<> struct is_unsigned< unsigned char > : public impl::true_type      {};
template<> struct is_unsigned< unsigned int > : public impl::true_type       {};
template<> struct is_unsigned< unsigned short > : public impl::true_type     {};
template<> struct is_unsigned< unsigned long > : public impl::true_type      {};
template<> struct is_unsigned< unsigned long long > : public impl::true_type {};

template< typename TYPE > struct is_signed : public impl::true_type         {};
template<> struct is_signed< unsigned char > : public impl::false_type      {};
template<> struct is_signed< unsigned short > : public impl::false_type     {};
template<> struct is_signed< unsigned int > : public impl::false_type       {};
template<> struct is_signed< unsigned long > : public impl::false_type      {};
template<> struct is_signed< unsigned long long > : public impl::false_type {};

// Specialization -> exact type similarity
template< class T1, class T2 > struct are_type_similar : public impl::false_type {};
template< class T > struct are_type_similar< T, T > : public impl::true_type     {};

// Functions -> is the instance rvalue or lvalue
template< class TYPE > constexpr bool is_rvalue( TYPE && INST )  { return !are_type_similar< decltype(INST), TYPE & >::value; }
template< class TYPE > constexpr bool is_lvalue( TYPE && INST )  { return  are_type_similar< decltype(INST), TYPE & >::value; }




/**||***************************************************************************************************************************************
*
*   Description: OOP CT control - derived from, derived from (strict), not derived from, not derived from (strict) and operator checks
*
|***************************************************************************************************************************************///+

// Compile time constraint that template parameter DERIVED must be derived from BASE
/* Full definition, failing case */
template< class NOT_DERIVED, class NOT_BASE, typename=void >
struct is_derived_from : public impl::false_type {};
/* Full specialization, true case */
template< class DERIVED, class BASE >
struct is_derived_from< int DERIVED::*, int BASE::*, impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::true_type {};



// Compile time constraint that template parameter DERIVED must be derived from BASE. Additionally DERIVED != BASE.
/* Full definition, failing case */
template< class NOT_DERIVED, class NOT_BASE, typename=void >
struct is_strictly_derived_from : public impl::false_type {};
/* Full specialization, failing case: same class */
template< class SAME_CLASS >
struct is_strictly_derived_from< int SAME_CLASS::*, int SAME_CLASS::*, void > : public impl::false_type {};
/* Full specialization, true case */
template< class DERIVED, class BASE >
struct is_strictly_derived_from< int DERIVED::*, int BASE::*, impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::true_type {};



// Compile time constraint that template parameter DERIVED must not be derived from BASE
/* Full definition, failing case: not classes */
template< class NOT_CLASS1, class NOT_CLASS2, typename=void >
struct not_derived_from : public impl::false_type {};
/* Full specialization, true case */
template< class NOT_DERIVED, class NOT_BASE >
struct not_derived_from< int NOT_DERIVED::*, int NOT_BASE::*, void > : public impl::true_type {};
/* Full specialization, failing case */
template< class DERIVED, class BASE >
struct not_derived_from< int DERIVED::*, int BASE::*, impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::false_type {};



// Compile time constraint that template parameter DERIVED must not be derived from BASE. Additionally DERIVED != BASE.
/* Full definition, failing case: not classes */
template< class NOT_CLASS1, class NOT_CLASS2, typename=void >
struct not_strictly_derived_from : public impl::false_type {};
/* Full specialization, failing case: same class */
template< class SAME_CLASS >
struct not_strictly_derived_from< int SAME_CLASS::*, int SAME_CLASS::*, void > : public impl::false_type {};
/* Full specialization, true case */
template< class NOT_DERIVED, class NOT_BASE >
struct not_strictly_derived_from< int NOT_DERIVED::*, int NOT_BASE::*, void > : public impl::true_type {};
/* Full specialization, failing case */
template< class DERIVED, class BASE >
struct not_strictly_derived_from< int DERIVED::*, int BASE::*, impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::false_type {};



// Compile time constraint that a type must be callable
/* Full definition, failing case */
template< class TYPE, typename = void >
struct is_callable : public impl::false_type {};
/* Function, function ptr and pointer to member function types */
template< class RET_TYPE, class... PARAM >
struct is_callable< RET_TYPE( PARAM... ), void > : public impl::true_type    {};
template< class RET_TYPE, class... PARAM >
struct is_callable< RET_TYPE(*)( PARAM... ), void > : public impl::true_type {};
template< class RET_TYPE, class CLS, class... PARAM >
struct is_callable< RET_TYPE(CLS::*)( PARAM... ), void > : public impl::true_type {};
/* Function object type */
template< class CAL >
struct is_callable< int CAL::*, impl::a_void<decltype(&CAL::operator())> > : public impl::true_type {};



// Compile time constraint that a type must be trivially constructible
/* Full definition, failing case */
template< class TYPE, typename=void >
struct is_trivially_constructible : public impl::false_type {};
/* Full specialization: class type */
template< class TYPE >
struct is_trivially_constructible< int TYPE::*, impl::a_void<decltype( TYPE() )> > : public impl::true_type {};



// Compile time constraint that a type must be constructible
/* Full definition, failing case */
template< typename, class TYPE, class... PARAM >
struct is_constructible : public impl::false_type {};
/* Full specialization: class type */
template< class TYPE, class... PARAM >
struct is_constructible< impl::a_void<decltype( TYPE( declval<PARAM>()... ) )>, int TYPE::*, PARAM... > : public impl::true_type {};



// Compile time constraint that a type must be strictly comparable with another specific type (==)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename = void >
struct are_strictly_comparable : public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE1, class OTHER_TYPE >
struct are_strictly_comparable<int TYPE1::*, OTHER_TYPE, impl::a_void<decltype(declval<TYPE1>().operator==(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct are_strictly_comparable<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator==(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct are_strictly_comparable<int TYPE1::*, int TYPE2::*, impl::a_void<decltype(declval<TYPE1>().operator==(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a type must be 'completely' comparable with another specific type (<, >, <=, >=, ==)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename = void, typename = void, typename = void, typename = void, typename = void >
struct are_comparable : public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct are_comparable<int TYPE::*, OTHER_TYPE, impl::a_void<decltype(declval<TYPE>().operator<(declval<OTHER_TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator>(declval<OTHER_TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator<=(declval<OTHER_TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator>=(declval<OTHER_TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator==(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct are_comparable<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator<(declval<TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator>(declval<TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator<=(declval<TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator>=(declval<TYPE>()))>, impl::a_void<decltype(declval<TYPE>().operator==(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct are_comparable<int TYPE1::*, int TYPE2::*, impl::a_void<decltype(declval<TYPE1>().operator<(declval<TYPE2>()))>, impl::a_void<decltype(declval<TYPE1>().operator>(declval<TYPE2>()))>, impl::a_void<decltype(declval<TYPE1>().operator<=(declval<TYPE2>()))>, impl::a_void<decltype(declval<TYPE1>().operator>=(declval<TYPE2>()))>, impl::a_void<decltype(declval<TYPE1>().operator==(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a specific type must be assignable to the type (=)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename = void >
struct is_assignable : public are_type_similar< TYPE1, TYPE2 >, not_const<TYPE1>, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = is_lvalue<TYPE1>() && not_const<TYPE1>::value && are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct is_assignable<int TYPE::*, OTHER_TYPE, impl::a_void<decltype(declval<TYPE>().operator=(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct is_assignable<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator=(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct is_assignable<int TYPE1::*, int TYPE2::*, impl::a_void<decltype(declval<TYPE1>().operator=(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a type must be capable of being added to another specific type (+)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename = void >
struct can_add : public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_add<int TYPE::*, OTHER_TYPE, impl::a_void<decltype(declval<TYPE>().operator+(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct can_add<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator+(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_add<int TYPE1::*, int TYPE2::*, impl::a_void<decltype(declval<TYPE1>().operator+(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a specific type can be subtractable from the type (-)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE2, class TYPE1, typename = void >
struct can_subtract : public are_type_similar< TYPE2, TYPE1 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE2, TYPE1 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class OTHER_TYPE, class TYPE >
struct can_subtract<OTHER_TYPE, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator-(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct can_subtract<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator-(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE2, class TYPE1 >
struct can_subtract<int TYPE2::*, int TYPE1::*, impl::a_void<decltype(declval<TYPE1>().operator-(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a specific type can be multiplied with the type (*)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename = void >
struct can_multiply : public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_multiply<int TYPE::*, OTHER_TYPE, impl::a_void<decltype(declval<TYPE>().operator*(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct can_multiply<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator*(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_multiply<int TYPE1::*, int TYPE2::*, impl::a_void<decltype(declval<TYPE1>().operator*(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a type can be divided by a specific type (/)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE2, class TYPE1, typename = void >
struct can_divide : public are_type_similar< TYPE2, TYPE1 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1> {
   enum : bool { value = are_type_similar< TYPE2, TYPE1 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class OTHER_TYPE, class TYPE >
struct can_divide<OTHER_TYPE, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator/(declval<OTHER_TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, same class type */
template< class TYPE >
struct can_divide<int TYPE::*, int TYPE::*, impl::a_void<decltype(declval<TYPE>().operator*(declval<TYPE>()))> > : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE2, class TYPE1 >
struct can_divide<int TYPE2::*, int TYPE1::*, impl::a_void<decltype(declval<TYPE1>().operator*(declval<TYPE2>()))> > : public impl::true_type {};



// Compile time constraint that a type can be assigned, added, subtracted and multiplied i.e., is arithmetic
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE >
struct is_arithmetic : public is_assignable<TYPE, TYPE>, can_add<TYPE, TYPE>, can_subtract<TYPE, TYPE>, can_multiply<TYPE, TYPE> {
   enum : bool { value = is_assignable<TYPE, TYPE>::value && can_add<TYPE, TYPE>::value && can_subtract<TYPE, TYPE>::value && can_multiply<TYPE, TYPE>::value };
};

}   // namespace typetraits
}   // namespace simpleNewton

#endif





