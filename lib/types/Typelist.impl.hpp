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
///   Contains the implementation of the internal structures of the typelist.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {
namespace typelist {

namespace internal {

/*****************************************************************************************************************************************|
*
*   Operations on the above typelist: calc. length, is type available, append list, concatenate list, remove from list and remove
*
*   duplicates.
*
|*****************************************************************************************************************************************/

//+****************************************************************************************************************************************
/* Calculate length operation */
// Terminator full specialization
template< class TAIL >
struct length< TAIL > {
   enum { result = 1 };
};

// Recursive specialization
template< class H, class... TYPES >
struct length< H, TYPES... > {
   enum { result = 1 + length< TYPES... >::result };
};
/* End: Calculate length operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Is type available */
// Terminator full specialization
template< class TYPE, class END > 
struct is_in_list< TYPE, END > {
   enum : bool { result = false };
};

// 'Acting' full specialization
template< class TYPE, class... TAIL >
struct is_in_list< TYPE, TYPE, TAIL... > {
   enum : bool { result = true };
};

// Recursive full specialization
template< class TYPE, class HEAD, class... TAIL >
struct is_in_list< TYPE, HEAD, TAIL...> {
   enum : bool { result = is_in_list< TYPE, TAIL... >::result || false };
};
/* End: is type in typelist check */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Append typelist operation */
// Full definition
template< class... ALL_TYPES >
struct append {
   using list = SN_CT_TYPELIST< ALL_TYPES... >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Concatenate typelist operation */
// Work-around full specialization: we pass typelist as argument but extract the template arguments by compiler-deducing them.
template< class... NEW_TYPES, class... TYPES >
struct concatenate< SN_CT_TYPELIST<NEW_TYPES...>, TYPES... > {
   using list = SN_CT_TYPELIST< TYPES..., NEW_TYPES... >;
};
// Partial specilization for empty typelist: sometimes we WANT empty typelists, especially when operating on other typelists.
template< class... TYPES >
struct concatenate< SN_CT_TYPELIST<NullType>, TYPES... > {
   using list = SN_CT_TYPELIST< TYPES... >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Remove a type from typelist operation */
// 'Acting' specialization
template< class REM_T, class... TAIL >
struct remove< REM_T, REM_T, TAIL... > {
   using list = typename remove< REM_T, TAIL... >::list;
};

// Terminator specialization(s)
template< class REM_T, class END >
struct remove< REM_T, END > {
   using list = SN_CT_TYPELIST< END >;
};
template< class REM_T >
struct remove< REM_T, REM_T > {
   using list = SN_CT_TYPELIST< NullType >;
};

// Recursive specialization
template< class REM_T, class HEAD, class... TAIL >
struct remove< REM_T, HEAD, TAIL... > {
   using list = typename SN_CT_TYPELIST< HEAD >::template concatenateList< typename remove< REM_T, TAIL... >::list >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Remove duplicates from typelist operation */
// Empty specialization
template<> struct removeDuplicates< NullType > {
   using list = SN_CT_TYPELIST< NullType >;
};

// Terminator specialization
template< class END > 
struct removeDuplicates< END > {
   using list = SN_CT_TYPELIST< END >;
};

// Recursive specialization
template< class HEAD, class... TAIL >
struct removeDuplicates< HEAD, TAIL... > {

private:

   using R1 = typename removeDuplicates< TAIL... >::list;
   using R2 = typename R1::template removeFromList< HEAD >;

public:

   using list = typename SN_CT_TYPELIST< HEAD >::template concatenateList< R2 >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************

}   // namespace impl
}   // namespace typelist
}   // namespace simpleNewton

#endif   // DOXYSKIP
