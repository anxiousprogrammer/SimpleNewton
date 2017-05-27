#ifndef SN_BASICTYPETRAITS_HPP
#define SN_BASICTYPETRAITS_HPP

#include <Types.hpp>
#include "Typelist.hpp"

//==========================================================================================================================================
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
///   Contains a full set of typetraits specialized for the framework.
///   \file
///   \defgroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template< class TYPE >
struct BasicTypeTraits_CPPHackClass {};
#endif   // DOXYSKIP

/** The space in which all typetrait structs and functions are accessible */
namespace typetraits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Type altering actions and CT utility structures
////////////////////////////////////////////////////


/** A struct whose member, type, is lvalue reference of the template parameter.
*   \tparam T   A type of which it is desired to express an lvalue reference.
*/
template< class T > struct add_reference;

/** A struct whose member, type, is rvalue reference of the template parameter.
*   \tparam T   A type of which it is desired to express an rvalue reference.
*/
template< class T > struct add_rvalue_reference;

/** A struct whose member, type, is the template parameter with lvalue reference removed.
*   \tparam T   A type of which it is desired to strip the lvalue reference.
*/
template< class T > struct remove_reference;


/** A struct whose member, type, is the const qualified template parameter.
*   \tparam T   A type which is desired to have const qualified.
*/
template< class T > struct add_const;

/** A struct whose member, type, is the non-const qualified template parameter.
*   \tparam T   A type of which it is desired to strip the const type qualification.
*/
template< class T > struct remove_const;


/** A struct whose member, type, is the volatile qualified template parameter.
*   \tparam T   A type which is desired to have volatile qualififed.
*/
template< class T > struct add_volatile;

/** A struct whose member, type, is the non-volatile qualified template parameter.
*   \tparam T   A type of which it is desired to strip the volatile type qualification.
*/
template< class T > struct remove_volatile;


/** A typedef which strips its template parameter of its const and volatile qualifications, as well as lvalue reference type.
*   \tparam T   A type of which it is desired to strip const and volatile type qualifications, as well as lvalue reference.
*/
template< class T > using shed_cvqr = typename remove_const< typename remove_volatile< typename remove_reference<T>::type >::type >::type;


/** A function which declares a return type of rvalue reference and is without definition. As long as this function is called within sizeof
*   or decltype operators, the compiler throws no error.
*   \tparam T   A type which is desired to be pseudo-instantiated as rvalue.
*/
template< class T > T&& declval();

/** A function which declares a return type of template parameter type and is without definition. As long as this function is called within 
*   sizeof or decltype operators, the compiler throws no error.
*   \tparam T   A type which is desired to be pseudo-instantiated.
*/
template< class T > T declinst();



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Declarations of implementation helpers (should not be in accessible namespace to client)
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace internal {

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

}   // namespace internal
#endif   // DOXYSKIP


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Basic type typetrait structures
////////////////////////////////////////////


/** A struct whose compile-time constant member, value, gives the number of template arguments contained in the parameter pack
*   \tparam ARG   Parameter pack which is to be counted.
*/
template< class... ARG > struct argument_count;



/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of void type, and false if not.
*   \tparam TYPE   The type which is to be tested for void type.
*/
template< class TYPE > struct is_void;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of any of the integral types, and 
*   false if not.
*   \tparam TYPE   A type which is to be tested for integral type.
*/
template< typename TYPE > struct is_integer;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is not of integral type, and false if it 
*   is.
*   \tparam TYPE   A type which is to be tested for necessarily non-integral type.
*/
template< typename TYPE > struct not_integer;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of floating point type, and false if 
*   not.
*   \tparam TYPE   A type which is to be tested for floating point type.
*/
template< typename TYPE > struct is_floating_point;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is not of floating point type, and false 
*   if it is.
*   \tparam TYPE   A type which is to be tested for void type.
*/
template< typename TYPE > struct not_floating_point;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of small_t type, and false if not.
*   \tparam TYPE   A type which is to be tested for small_t type.
*/
template< typename TYPE > struct is_small_t;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of large_t type, and false if not.
*   \tparam TYPE   A type which is to be tested for large_t type.
*/
template< typename TYPE > struct is_large_t;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of id_t type, and false if not.
*   \tparam TYPE   A type which is to be tested for id_t type.
*/
template< typename TYPE > struct is_id_t;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of string_t type, and false if not.
*   \tparam TYPE   A type which is to be tested for string_t type.
*/
template< typename TYPE > struct is_string_t;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of boolean type, and false if not.
*   \tparam TYPE   A type which is to be tested for bool type.
*/
template< typename TYPE > struct is_bool;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is an array, and false if not.
*   \tparam TYPE   A template parameter which could be an array of unknown type.
*/
template< typename TYPE > struct is_array;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is an array of specified type, and false 
*   if not.
*   \tparam ARR    A template parameter which could be an array of specified type.
*   \tparam TYPE   The specified type.
*/
template< typename ARR, typename TYPE > struct is_array_of_type;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of basic data type, and false if not.
*   \tparam TYPE   A type which is to be tested for basic data type.
*/
template< typename TYPE > struct is_basic;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is an array of basic data type, and false 
*   if not.
*   \tparam TYPE   A template parameter which could be an array of basic data type.
*/
template< typename TYPE > struct is_array_of_basic_type;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is a function, and false if not.
*   \tparam TYPE   A type which is to be tested for a function.
*/
template< typename TYPE > struct is_function;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of class type, and false if not.
*   \tparam TYPE   A type which is to be tested for class type.
*/
template< typename TYPE > struct is_class;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter of SN_CT_TYPELIST type, and false if not.
*   \tparam TYPE   A type which is to be tested for SN_CT_TYPELIST type, which is defined in Typelist.hpp.
*/
template< typename TL > struct is_typelist;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of pointer type, and false if not.
*   \tparam TYPE   A type which is to be tested for pointer type.
*/
template< typename TYPE > struct is_pointer;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of pointer to const type, and false if 
*   not.
*   \tparam TYPE   A type which is to be tested for pointer to const type.
*/
template< typename TYPE > struct is_pointer_to_const;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of function pointer type, and false if 
*   not.
*   \tparam TYPE   A type which is to be tested for function pointer type.
*/
template< typename TYPE > struct is_function_pointer;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of pointer to member function type, 
*   and false if not.
*   \tparam TYPE   A type which is to be tested for pointer to member function type.
*/
template< typename TYPE > struct is_member_function_pointer;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of lvalue reference type, and false if 
*   not.
*   \tparam TYPE   A type which is to be tested for lvalue reference type.
*/
template< typename TYPE > struct is_reference;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of const qualified lvalue reference 
*   type, and false if not.
*   \tparam TYPE   A type which is to be tested for const qualified lvalue reference type.
*/
template< typename TYPE > struct is_const_reference;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of rvalue reference type, and false if 
*   not.
*   \tparam TYPE   A type which is to be tested for rvalue reference type.
*/
template< typename TYPE > struct is_rvalue_reference;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is not of rvalue reference type, and 
*   false if it is.
*   \tparam TYPE   A type which is required to not be rvalue reference type for true value.
*/
template< typename TYPE > struct not_rvalue_reference;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Type qualifier typetrait structures
////////////////////////////////////////


/** A struct whose compile-time constant boolean member, value, is true if the template parameter is const qualified, and false if not.
*   \tparam TYPE   A type which is to be tested for const type qualification.
*/
template< class TYPE > struct is_const;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is not const qualified, and false if it 
*   is.
*   \tparam TYPE   A type which is to be tested for non-const type qualification.
*/
template< class TYPE > struct not_const;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is volatile qualified, and false if it 
*   is not.
*   \tparam TYPE   A type which is to be tested for volatile type qualification.
*/
template< class TYPE > struct is_volatile;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is not volatile qualified, and false if 
*   it is.
*   \tparam TYPE   A type which is to be tested for non-volatile type qualification.
*/
template< class TYPE > struct not_volatile;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Sign typetrait structures
//////////////////////////////


/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of unsigned type, and false if it 
*   is not.
*   \tparam TYPE   A type which is to be tested for unsigned type.
*/
template< typename TYPE > struct is_unsigned;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is of signed type, and false if it 
*   is not.
*   \tparam TYPE   A type which is to be tested for signed type.
*/
template< typename TYPE > struct is_signed;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Value category typetrait structures
////////////////////////////////////////


/** A function to ascertain if the template parameter is of rvalue value category.
*   \tparam TYPE   The type of the instance INST will be deduced by compiler.
*   \param INST    An instance which is to be tested for rvalue value category.
*   \return        True if TYPE is rvalue, false if not.
*/
template< class TYPE > constexpr bool is_rvalue( TYPE && INST );

/** A function to ascertain if the template parameter is of lvalue value category.
*   \tparam TYPE   The type of the instance INST will be deduced by compiler.
*   \param INST    An instance which is to be tested for lvalue value category.
*   \return        True if TYPE is lvalue, false if not.
*/
template< class TYPE > constexpr bool is_lvalue( TYPE && INST );



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Categorical typetrait structures
/////////////////////////////////////


/** A struct whose compile-time constant boolean member, value, is true if the template parameters have the exact same typename, and false 
*   if it they do not.
*   \tparam T1   A first template parameter.
*   \tparam T2   A second template parameter.
*/
template< class T1, class T2 > struct are_type_similar;


/** A struct whose compile-time constant boolean member, value, is true if the one class is derived from the other, and false if it is not.
*   \tparam DERIVED   A class which could be derived from BASE.
*   \tparam BASE      A class which could be the base class of DERIVED.
*/
template< class DERIVED, class BASE, typename >            struct is_derived_from;

/** A struct whose compile-time constant boolean member, value, is true if a class is derived from at least one member of a specified 
*   typelist of type SN_CT_TYPELIST, and false if it is not.
*   \tparam CLS   A class which could be derived from at least one member of TL.
*   \tparam TL    A typelist which could contain a base class of CLS.
*/
template< class CLS, class TL >                            struct is_derived_from_list_member; 

/** A struct whose compile-time constant boolean member, value, is true if the one class is not derived from the other, and false if it is.
*   \tparam NOT_DERIVED   A class which may not be derived from BASE.
*   \tparam NOT_BASE      A class which may not be the base class of DERIVED.
*/
template< class NOT_DERIVED, class NOT_BASE, typename >    struct not_derived_from;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter is callable, and false if it is not. 
*   Callable objects are functions, function pointers, pointers to member functions and functors (or function objects).
*   \tparam TYPE   A type which could be callable.
*/
template< class TYPE, typename >                           struct is_callable;

/** A struct whose compile-time constant boolean member, value, is true if the template parameter can be called with the parameters 
*   specified in the typelist TL, and false if it is not.
*   \tparam CAL   A callable object.
*   \tparam TL    A SN_CT_TYPELIST which contains the parameters for CAL.
*/
template< class CAL, class TL, typename >                  struct can_call;

/** A struct whose compile-time constant boolean member, value, is true if a class is trivially constructible i.e., constructible without 
*   parameters of initialization, and false if it is not.
*   \tparam TYPE   A class which could be trivially constructible.
*/
template< class TYPE, typename >                           struct is_trivially_constructible;

/** A struct whose compile-time constant boolean member, value, is true if the a class can be copy constructed, and false if it can not.
*   \tparam TYPE   A class which could be copy constructible.
*/
template< class TYPE, typename >                           struct is_copy_constructible;

/** A struct whose compile-time constant boolean member, value, is true if a class is move constructible, and false if it is not.
*   \tparam TYPE   A class which could be move constructible.
*/
template< class TYPE, typename >                           struct is_move_constructible;

/** A struct whose compile-time constant boolean member, value, is true if a class can be constructed, and false if it can not.
*   \tparam TYPE   A class which could be constructible.
*/
template< class TYPE, class TL, typename >                 struct is_constructible;

/** A struct whose compile-time constant boolean member, value, is true if two types are equality comparable, and false if they are not.
*   \tparam TYPE1   A type which has an equality comparison operator compatible with TYPE2.
*   \tparam TYPE2   A type which could be equality compared with TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct are_strictly_comparable;

/** A struct whose compile-time constant boolean member, value, is true if two types are equal-to (==), less-than-or-equal-to (<=), less-
*   than (<), greater-than-or-equal-to (>=) and greater-than (>) comparable, and false if they are not.
*   \tparam TYPE1   A type which has ==, <=, <, >= and > comparison operators compatible with TYPE2.
*   \tparam TYPE2   A type which could be fully compared with TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename, typename, typename, typename, typename >
                                                           struct are_comparable;

/** A struct whose compile-time constant boolean member, value, is true if a type can be copy assigned to another, and false if it cannot.
*   \tparam TYPE1   A type which could be assigned by an instance of TYPE2.
*   \tparam TYPE2   A type which could be use to assign TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct is_copy_assignable;

/** A struct whose compile-time constant boolean member, value, is true if a type can be move assigned to another, and false if it cannot.
*   \tparam TYPE1   A type which could be assigned by an instance of TYPE2.
*   \tparam TYPE2   A type which could be use to assign TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct is_move_assignable;

/** A struct whose compile-time constant boolean member, value, is true if a type can be either copy or move assigned to another, and false 
*   if it cannot.
*   \tparam TYPE1   A type which could be assigned by an instance of TYPE2.
*   \tparam TYPE2   A type which could be use to assign TYPE1.
*/
template< class TYPE1, class TYPE2 >                       struct is_assignable;

/** A struct whose compile-time constant boolean member, value, is true if a type can be added to another, and false if it cannot.
*   \tparam TYPE1   A type which has an addition operator compatible with TYPE2.
*   \tparam TYPE2   A type whose instances could be added to instances of TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct can_add;

/** A struct whose compile-time constant boolean member, value, is true if a type can be subtracted from another, and false if it cannot.
*   \tparam TYPE1   A type which has a subtraction operator compatible with TYPE2.
*   \tparam TYPE2   A type whose instances could be subtracted from instances of TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct can_subtract;

/** A struct whose compile-time constant boolean member, value, is true if a type can be multiplied with another, and false if it cannot.
*   \tparam TYPE1   A type which has a multiplication operator compatible with TYPE2.
*   \tparam TYPE2   A type whose instances could be multiplied with instances of TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct can_multiply;

/** A struct whose compile-time constant boolean member, value, is true if a type can be divided by another, and false if it cannot.
*   \tparam TYPE1   A type which has a division operator compatible with TYPE2.
*   \tparam TYPE2   A type whose instances could divide the instances of TYPE1.
*/
template< class TYPE1, class TYPE2, typename, typename >   struct can_divide;

/** A struct whose compile-time constant boolean member, value, is true if a type is arithmetic i.e., instances of the type can be added 
*   to, subtracted from, multiplied with and divided by instances of the same type, and false if it cannot.
*   \tparam TYPE   A type which is arithmetic.
*/
template< class TYPE >                                     struct is_arithmetic;

}   // namespace typetraits
}   // namespace simpleNewton

#include "BasicTypeTraits.impl.hpp"
#endif





