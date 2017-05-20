/**||***************************************************************************************************************************************
*
*   Description: TypeTraits implementation for BasicTypeTraits.hpp
*
|***************************************************************************************************************************************///+

namespace simpleNewton {
namespace typetraits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Type altering actions
/////////////////////////

// Add, remove reference
template< class T > struct add_reference           { using type = T &; };
template< class T > struct add_rvalue_reference    { using type = T &&; };
template< class T > struct remove_reference        { using type = T; };
template< class T > struct remove_reference<T &>   { using type = T; };

// Add, remove const
template< class T > struct add_const                 { using type = const T; };
template< class T > struct remove_const              { using type = T; };
template< class T > struct remove_const< const T >   { using type = T; };

// Add, remove volatile
template< class T > struct add_volatile                    { using type = volatile T; };
template< class T > struct remove_volatile                 { using type = T; };
template< class T > struct remove_volatile< volatile T >   { using type = T; };

// No CVQ_R
template< class T > using essential_type = typename remove_const< typename remove_volatile< typename remove_reference<T>::type >::type 
                                                                >::type;

// The 'opposite' of decltype - pseudo-instantiation
template< class T > T&& declval();
template< class T > T declinst();
//template< class T > using declval = add_rvalue_reference<T>::type;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Implementation of simple typetrait structures
///////////////////////////////////////////

namespace impl {

// Foundations need to be laid. So do I.
struct true_type  { enum : bool { value=true }; };
struct false_type { enum : bool { value=false }; };

// Specialization -> NoCVQ_R (gets rid of cv - type qualifiers and does away with reference types)
template< class TYPE > struct NoCVQ_R                          { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< TYPE & >                { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< const TYPE >            { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< const TYPE & >          { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile TYPE >         { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile TYPE & >       { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile const TYPE >   { using type=TYPE; };
template< class TYPE > struct NoCVQ_R< volatile const TYPE & > { using type=TYPE; };

// Ambiguity void type: if expression is true then int.
template<> struct amb_void<true>    { using type = int; };
template<> struct amb_void<false>   { using type = void; };

}   // namespace impl

// Counts the number of variadic arguments
/* Empty set partial specialization */
template<> struct argument_count< simpleNewton::NullType > { enum { value = 0 }; };
/* Terminator partial specialization */
template< class END > struct argument_count<END> { enum { value = 1 }; };
/* Recurring partial specialization */
template< class HEAD, class... TAIL > struct argument_count<HEAD, TAIL...> {
   enum { value = 1 + argument_count<TAIL...>::value };
};


// The first meal of the day!
template< class TYPE > struct is_void : public impl::false_type {};
template<> struct is_void<void> : public impl::true_type        {};

// Specialization -> int types
template< class TYPE > struct is_integer : public impl::false_type        {};
template<> struct is_integer<char> : public impl::true_type               {};
template<> struct is_integer<unsigned char> : public impl::true_type      {};
template<> struct is_integer<short> : public impl::true_type              {};
template<> struct is_integer<unsigned short> : public impl::true_type     {};
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

template< class TYPE > struct is_ID_t : public impl::false_type {};
template<> struct is_ID_t<ID_t> : public impl::true_type      {};

// Specialization -> string, bool and array types
template< class TYPE > struct is_string_t : public impl::false_type {};
template<> struct is_string_t<string_t> : public impl::true_type    {};

template< class TYPE > struct is_bool : public impl::false_type {};
template<> struct is_bool<bool> : public impl::true_type        {};

template< class TYPE > struct is_array : public impl::false_type                        {};
template< class TYPE, int SIZE > struct is_array< TYPE[SIZE] > : public impl::true_type {};

template< class ARR, class TYPE > struct is_array_of_type : public impl::false_type                     {};
template< class TYPE, int SIZE > struct is_array_of_type< TYPE[SIZE], TYPE > : public impl::true_type   {};

template< typename TYPE > struct is_basic : public is_integer<TYPE>, is_floating_point<TYPE>, is_bool<TYPE> {
   enum : bool { value = is_integer<TYPE>::value || is_floating_point<TYPE>::value || is_bool<TYPE>::value };
};
template<> struct is_basic< char > : public impl::true_type   {};

template< typename TYPE > struct is_array_of_basic_type : public is_array_of_type< TYPE, char >, is_array_of_type< TYPE, short >, 
                                                                 is_array_of_type< TYPE, int >, is_array_of_type< TYPE, long >, 
                                                                 is_array_of_type< TYPE, long long >, 
                                                                 is_array_of_type< TYPE, unsigned char >, 
                                                                 is_array_of_type< TYPE, unsigned short >,
                                                                 is_array_of_type< TYPE, unsigned int >,
                                                                 is_array_of_type< TYPE, unsigned long >,
                                                                 is_array_of_type< TYPE, unsigned long long >,
                                                                 is_array_of_type< TYPE, float >, is_array_of_type< TYPE, double >,
                                                                 is_array_of_type< TYPE, bool > {
                                                                 
   enum : bool { value = is_array_of_type< TYPE, char >::value || is_array_of_type< TYPE, short >::value ||
                         is_array_of_type< TYPE, int >::value || is_array_of_type< TYPE, long >::value ||
                         is_array_of_type< TYPE, long long >::value || is_array_of_type< TYPE, unsigned char >::value ||
                         is_array_of_type< TYPE, unsigned short >::value || is_array_of_type< TYPE, unsigned int >::value ||
                         is_array_of_type< TYPE, unsigned long >::value || is_array_of_type< TYPE, unsigned long long >::value ||
                         is_array_of_type< TYPE, float >::value || is_array_of_type< TYPE, double >::value ||
                         is_array_of_type< TYPE, bool >::value };
};

// Specialization -> function, class and typelist
template< class TYPE > struct is_function : public impl::false_type                                                {};
template< class RET_TYPE, class... PARAM > struct is_function< RET_TYPE( PARAM... ) > : public impl::true_type     {};
template< class RET_TYPE, class... PARAM > struct is_function< RET_TYPE( PARAM...,... ) > : public impl::true_type {}; // printf

template< class TYPE > struct is_class {
   enum : bool { value = is_member_function_pointer< decltype( impl::Class_Type_Return<TYPE>( nullptr ) ) >::value };
};

template< class TL > struct is_typelist : public impl::false_type {};
template< class... PARAM > struct is_typelist< SN_CT_TYPELIST< PARAM... > > : public impl::true_type {};

// Specialization -> ptr, ptr to const, func ptr, member func ptr and reference and a couple others.
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

template< class TYPE > struct is_member_function_pointer : public impl::false_type                                       {};
template< class RET_TYPE, class TYPE > struct is_member_function_pointer< RET_TYPE(TYPE::*) > : public impl::true_type   {};

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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Description: OOP CT control - derived from, derived from (strict), not derived from, not derived from (strict) and operator checks
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Template parameter DERIVED must be derived from BASE
/* Full definition, failing case */
template< class NOT_DERIVED, class NOT_BASE, typename=void >
struct is_derived_from : public impl::false_type {};
/* Partial specialization, true case */
template< class DERIVED, class BASE >
struct is_derived_from< DERIVED, BASE, 
                        impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::true_type {};



// Template parameter CLS must be derived from at least one class in the typelist
// Implementation struct
/* Declaration */
template< class CLS, class... PARAM > struct is_derived_from_list_member_impl;
/* Terminator specialization */
template< class CLS, class END > struct is_derived_from_list_member_impl< CLS, END > {
   enum : bool { value = is_derived_from< CLS, END >::value };
};
/* Acting specialization */
template< class CLS, class HEAD, class... TAIL > 
struct is_derived_from_list_member_impl< CLS, HEAD, TAIL... > {
   enum : bool { value = is_derived_from< CLS, HEAD >::value || is_derived_from_list_member_impl< CLS, TAIL... >::value };
};

/* Full definition, failing case: not typelist */
template< class CLS, class TL >
struct is_derived_from_list_member : public impl::false_type {};
/* Partial specialization */
template< class CLS, template<class...> class TL, class... PARAM >
struct is_derived_from_list_member< CLS, TL<PARAM...> > : public is_derived_from_list_member_impl< CLS, PARAM... > {};



// Template parameter DERIVED must NOT be derived from BASE
/* Full specialization, true case */
template< class TYPE1, class TYPE2, typename=void >
struct not_derived_from : public impl::true_type {};
/* Partial specialization, failing case */
template< class DERIVED, class BASE >
struct not_derived_from< DERIVED, BASE, 
                         impl::a_void< decltype( impl::ptr_accept<BASE>( impl::ptr_return<DERIVED>() ) ) > > : public impl::false_type {};



// The type must be callable
/* Full definition, failing case */
template< class TYPE, typename=void >
struct is_callable : public impl::false_type {};
/* Function, function ptr and pointer to member function types */
template< class RET_TYPE, class... PARAM >
struct is_callable< RET_TYPE( PARAM... ), void > : public impl::true_type    {};
template< class RET_TYPE, class... PARAM >
struct is_callable< RET_TYPE(*)( PARAM... ), void > : public impl::true_type {};
/* Pointer to member function can be type qualified */
template< class RET_TYPE, class CLS, class... PARAM >
struct is_callable< RET_TYPE(CLS::*)( PARAM... ), void > : public impl::true_type {};
template< class RET_TYPE, class CLS, class... PARAM >
struct is_callable< RET_TYPE(CLS::*)( PARAM... ) const, void > : public impl::true_type {};
template< class RET_TYPE, class CLS, class... PARAM >
struct is_callable< RET_TYPE(CLS::*)( PARAM... ) volatile, void > : public impl::true_type {};
template< class RET_TYPE, class CLS, class... PARAM >
struct is_callable< RET_TYPE(CLS::*)( PARAM... ) const volatile, void > : public impl::true_type {};
/* Function object type */
template< class CAL >
struct is_callable< int CAL::*, impl::a_void< decltype(&CAL::operator()) > > : public impl::true_type {};



// Check for callability: functor, pointer to function
/* Full definition, failing case */
template< class CAL, class TL, typename=void > struct can_call : public impl::false_type {};
/* Partial specialization, true case */
template< class CAL, template<class...> class TL, class... PARAM > 
struct can_call< CAL, TL<PARAM...>, impl::a_void< decltype( declval<CAL>()( declval< PARAM >()... ) ) > > : public impl::true_type {};
/* Partial specialization, pointer to member function */
template< class R_TYPE, class CLS, template<class...> class TL, class... PROV_PARAM, class... REQ_PARAM > 
struct can_call< R_TYPE(CLS::*)(REQ_PARAM...), TL<PROV_PARAM...>, 
                 impl::a_void< decltype( (declval<CLS>().*declinst<R_TYPE(CLS::*)(REQ_PARAM...)>())( declval< PROV_PARAM >()... ) ) > >
                 : public impl::true_type {};
/* Partial specialization, pointer to member function (with const) */
template< class R_TYPE, class CLS, template<class...> class TL, class... PROV_PARAM, class... REQ_PARAM > 
struct can_call< R_TYPE(CLS::*)(REQ_PARAM...) const, TL<PROV_PARAM...>, 
                 impl::a_void< decltype( (declval<const CLS>().*declinst<R_TYPE(CLS::*)(REQ_PARAM...) const>())
                                          ( declval< PROV_PARAM >()... ) ) > > : public impl::true_type {};
/* Partial specialization, pointer to member function (with volatile) */
template< class R_TYPE, class CLS, template<class...> class TL, class... PROV_PARAM, class... REQ_PARAM > 
struct can_call< R_TYPE(CLS::*)(REQ_PARAM...) volatile, TL<PROV_PARAM...>, 
                 impl::a_void< decltype( (declval<CLS>().*declinst<R_TYPE(CLS::*)(REQ_PARAM...) volatile>())
                                          ( declval< PROV_PARAM >()... ) ) > > : public impl::true_type {};
/* Partial specialization, pointer to member function (with const volatile) */
template< class R_TYPE, class CLS, template<class...> class TL, class... PROV_PARAM, class... REQ_PARAM > 
struct can_call< R_TYPE(CLS::*)(REQ_PARAM...) const volatile, TL<PROV_PARAM...>, 
                 impl::a_void< decltype( (declval<const CLS>().*declinst<R_TYPE(CLS::*)(REQ_PARAM...) const volatile>())
                                          ( declval< PROV_PARAM >()... ) ) > > : public impl::true_type {};



// The type must be trivially constructible
/* Full definition, failing case */
template< class TYPE, typename=void >
struct is_trivially_constructible : public impl::false_type {};
/* Partial specialization: class type */
template< class TYPE >
struct is_trivially_constructible< TYPE, impl::a_void< decltype( TYPE() ) > > : public impl::true_type {};



// The type must be COPY constructible
/* Full definition, failing case */
template< class TYPE, typename=void >
struct is_copy_constructible : public impl::false_type {};
/* Partial specialization: class type */
template< class TYPE >
struct is_copy_constructible< TYPE, impl::a_void< decltype( TYPE( declinst<TYPE>() ) ) > > : public impl::true_type {};



// The type must be MOVE constructible
/* Full definition, failing case */
template< class TYPE, typename=void >
struct is_move_constructible : public impl::false_type {};
/* Partial specialization: class type */
template< class TYPE >
struct is_move_constructible< TYPE, impl::a_void< decltype( TYPE( declval<TYPE>() ) ) > > : public impl::true_type {};



// The type must be constructible
/* Full definition, failing case */
template< class TYPE, class TL, typename=void >
struct is_constructible : public impl::false_type {};
/* Partial specialization: class type */
template< class TYPE, template< class... > class TL, class... PARAM >
struct is_constructible< TYPE, TL<PARAM...>, impl::a_void< decltype( TYPE( declval<PARAM>()... ) ) > > : public impl::true_type {};



// The type must be strictly comparable with another specific type (==)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct are_strictly_comparable 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, 
         is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct are_strictly_comparable< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class<OTHER_TYPE>::value >::type, 
                                impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator==) ) > > 
                               : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct are_strictly_comparable< int TYPE1::*, int TYPE2::*, void, 
                                impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator==) ) > > 
                                : public impl::true_type {};



// The type must be 'completely' comparable with another specific type (<, >, <=, >=, ==)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void, typename=void, typename=void, typename=void, typename=void >
struct are_comparable 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, 
         is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value ||
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct are_comparable< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class<OTHER_TYPE>::value >::type, 
                       impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator<) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator>) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator<=) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator>=) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator==) ) > > 
                       : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct are_comparable< int TYPE1::*, int TYPE2::*, void, 
                       impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator<) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator>) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator<=) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator>=) ) >, 
                       impl::a_void< decltype( static_cast< bool(TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator==) ) > > 
                       : public impl::true_type {};



// A specific type must be copy assignable to the type (COPY=)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct is_copy_assignable 
: public are_type_similar< TYPE1, TYPE2 >, not_const<TYPE1>, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, 
         is_pointer<TYPE1>, is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = not_const<TYPE1>::value && 
                         are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct is_copy_assignable< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class<OTHER_TYPE>::value >::type, 
                           impl::a_void< decltype( static_cast< TYPE&(TYPE::*)( const OTHER_TYPE & ) >(&TYPE::operator=) ) > > 
                           : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct is_copy_assignable< int TYPE1::*, int TYPE2::*, void,
                           impl::a_void< decltype( static_cast< TYPE1&(TYPE1::*)( const TYPE2 & ) >(&TYPE1::operator=) ) > > 
                           : public impl::true_type {};



// A specific type must be move assignable to the type (MOVE=)
/* Full definition, failing case */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct is_move_assignable : public impl::false_type {};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct is_move_assignable< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class<OTHER_TYPE>::value >::type, 
                           impl::a_void< decltype( static_cast< TYPE&(TYPE::*)( OTHER_TYPE && ) >(&TYPE::operator=) ) > > 
                           : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct is_move_assignable< int TYPE1::*, int TYPE2::*, void,
                           impl::a_void< decltype( static_cast< TYPE1&(TYPE1::*)( TYPE2 && ) >(&TYPE1::operator=) ) > > 
                           : public impl::true_type {};



// A specific type must be assignable to the type (=)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2 >
struct is_assignable {
   enum : bool { value = is_copy_assignable<TYPE1, TYPE2>::value || is_move_assignable<TYPE1, TYPE2>::value };
};

// A type must be capable of being added to another specific type (+)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct can_add 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, 
         is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_add< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class< OTHER_TYPE >::value >::type,
                impl::a_void< decltype( static_cast< TYPE (TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator+) ) > > 
                : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_add< int TYPE1::*, int TYPE2::*, void,
                impl::a_void< decltype( static_cast< TYPE1 (TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator+) ) > > 
                : public impl::true_type {};



// A specific type can be subtractable from the type (-)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct can_subtract 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1>, is_pointer<TYPE1>, 
         is_pointer_to_const<TYPE1>, is_function_pointer<TYPE1>, is_rvalue_reference<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_subtract< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class< OTHER_TYPE >::value >::type,
                     impl::a_void< decltype( static_cast< TYPE (TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator-) ) > > 
                     : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_subtract< int TYPE1::*, int TYPE2::*, void, 
                     impl::a_void< decltype( static_cast< TYPE1 (TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator-) ) > > 
                     : public impl::true_type {};



// A specific type can be multiplied with the type (*)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct can_multiply 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_multiply< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class< OTHER_TYPE >::value >::type,
                     impl::a_void< decltype( static_cast< TYPE (TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator*) ) > > 
                     : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_multiply< int TYPE1::*, int TYPE2::*, void, 
                     impl::a_void< decltype( static_cast< TYPE1 (TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator*) ) > > 
                     : public impl::true_type {};



// A type can be divided by a specific type (/)
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE1, class TYPE2, typename=void, typename=void >
struct can_divide 
: public are_type_similar< TYPE1, TYPE2 >, is_integer<TYPE1>, is_floating_point<TYPE1>, is_bool<TYPE1> {
   enum : bool { value = are_type_similar< TYPE1, TYPE2 >::value && (is_integer<TYPE1>::value || is_floating_point<TYPE1>::value || 
                         is_bool<TYPE1>::value || is_pointer<TYPE1>::value || is_pointer_to_const<TYPE1>::value || 
                         is_function_pointer<TYPE1>::value || is_rvalue_reference<TYPE1>::value) };
};
/* Specialization: true case - class type, other type */
template< class TYPE, class OTHER_TYPE >
struct can_divide< int TYPE::*, OTHER_TYPE, typename impl::amb_void< is_class< OTHER_TYPE >::value >::type,
                   impl::a_void< decltype( static_cast< TYPE (TYPE::*)( const OTHER_TYPE & ) const >(&TYPE::operator/) ) > > 
                   : public impl::true_type {};
/* Specialization: true case - class type, other class type */
template< class TYPE1, class TYPE2 >
struct can_divide< int TYPE1::*, int TYPE2::*, void,
                   impl::a_void< decltype( static_cast< TYPE1 (TYPE1::*)( const TYPE2 & ) const >(&TYPE1::operator/) ) > > 
                   : public impl::true_type {};



// A type can be assigned, added and subtracted i.e., is arithmetic
/* Full definition, typetraits for non-class types which comply are inherited */
template< class TYPE >
struct is_arithmetic 
: public is_assignable<TYPE, TYPE>, can_add<TYPE, TYPE>, can_subtract<TYPE, TYPE> {
   enum : bool { value = is_assignable<TYPE, TYPE>::value && can_add<TYPE, TYPE>::value && can_subtract<TYPE, TYPE>::value };
};


}   // namespace typetraits
}   // namespace simpleNewton
