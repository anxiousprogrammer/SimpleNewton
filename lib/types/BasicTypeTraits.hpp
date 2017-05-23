#ifndef BASICTYPETRAITS_HPP
#define BASICTYPETRAITS_HPP

#include <Types.hpp>
#include "Typelist.hpp"

namespace simpleNewton {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

template< class TYPE >
struct BasicTypeTraits_CPPHackClass {};



/**||***************************************************************************************************************************************
*
*   Description: Elaborate TypeTraits implementation for the simpleNewton framework. Gentle reminder - these are all compile time checks.
*
|***************************************************************************************************************************************///+

namespace typetraits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Type altering actions and CT utility structures
///////////////////////////////////////////////////

// Add, remove reference
template< class T > struct add_reference;
template< class T > struct add_rvalue_reference;
template< class T > struct remove_reference;

// Add, remove const
template< class T > struct add_const;
template< class T > struct remove_const;

// Add, remove volatile
template< class T > struct add_volatile;
template< class T > struct remove_volatile;

// No CVQ_R
template< class T > using shed_cvqr = typename remove_const< typename remove_volatile< typename remove_reference<T>::type >::type 
                                                                >::type;

// The 'opposite' of decltype - pseudo-instantiation
template< class T > T&& declval();
template< class T > T declinst();
//template< class T > using declval = add_rvalue_reference<T>::type;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Declarations of implementation helpers (should not be in accessible namespace to client)
/////////////////////////////////////////////////////////////////////////////////////////////

namespace impl {

// Shave off cv qualifiers and reference types
template< class TYPE > struct NoCVQ_R;

// Deciding types
struct true_type;
struct false_type;

// An important type-changing function which accepts a class and returns pointer
// to member function, which is a defining characteristic of classes
template< class TYPE > int TYPE::* Class_Type_Return( int TYPE::* );
template< class TYPE > TYPE Class_Type_Return(...);

// A function which takes as parameter a pointer to a template type
template< class CLS >
void ptr_accept( CLS* );

// A function which returns a pointer to a template type
template< class CLS >
CLS* ptr_return();

// Always void type: property checking template parameter enabler
template< class T > using a_void = void;

// Ambiguity void type: if expression is true then int.
template< bool VAL > struct amb_void;

}   // namespace impl



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Declarations of typetrait structures
/////////////////////////////////////////

// Static assert - argument number
template< class... ARG > struct argument_count;

// Declarations -> basic types
template< class TYPE > struct is_void;
template< typename TYPE > struct is_integer;
template< typename TYPE > struct not_integer;
template< typename TYPE > struct is_floating_point;
template< typename TYPE > struct not_floating_point;
template< typename TYPE > struct is_small_t;
template< typename TYPE > struct is_large_t;
template< typename TYPE > struct is_id_t;
template< typename TYPE > struct is_string_t;
template< typename TYPE > struct is_bool;
template< typename TYPE > struct is_array;
template< typename ARR, typename TYPE > struct is_array_of_type;
template< typename TYPE > struct is_basic;
template< typename TYPE > struct is_array_of_basic_type;
template< typename TYPE > struct is_function;
template< typename TYPE > struct is_class;
template< typename TL > struct is_typelist;

// Declarations -> pointer and reference types
template< typename TYPE > struct is_pointer;
template< typename TYPE > struct is_pointer_to_const;
template< typename TYPE > struct is_function_pointer;
template< typename TYPE > struct is_member_function_pointer;
template< typename TYPE > struct is_reference;
template< typename TYPE > struct is_const_reference;
template< typename TYPE > struct is_rvalue_reference;
template< typename TYPE > struct not_rvalue_reference;

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

// OOP CT control - Inheritance, rule of five check, overloaded operator existence check! All using parameter validation.
template< class DERIVED, class BASE, typename >            struct is_derived_from;
template< class CLS, class TL >                            struct is_derived_from_list_member; 
template< class NOT_DERIVED, class NOT_BASE, typename >    struct not_derived_from;
template< class TYPE, typename >                           struct is_callable;
template< class CAL, class TL, typename >                  struct can_call;
template< class TYPE, typename >                           struct is_trivially_constructible;
template< class TYPE, typename >                           struct is_copy_constructible;
template< class TYPE, typename >                           struct is_move_constructible;
template< class TYPE, class TL, typename >                 struct is_constructible;
template< class TYPE1, class TYPE2, typename, typename >   struct are_strictly_comparable;
template< class TYPE1, class TYPE2, typename, typename, typename, typename, typename, typename >
                                                           struct are_comparable;
template< class TYPE1, class TYPE2, typename, typename >   struct is_copy_assignable;
template< class TYPE1, class TYPE2, typename, typename >   struct is_move_assignable;
template< class TYPE1, class TYPE2 >                       struct is_assignable;
template< class TYPE1, class TYPE2, typename, typename >   struct can_add;
template< class TYPE1, class TYPE2, typename, typename >   struct can_subtract;
template< class TYPE1, class TYPE2, typename, typename >   struct can_multiply;
template< class TYPE1, class TYPE2, typename, typename >   struct can_divide;
template< class TYPE >                                     struct is_arithmetic;

}   // namespace typetraits
}   // namespace simpleNewton

#include "BasicTypeTraits.impl.hpp"
#endif





