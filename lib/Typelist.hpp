#ifndef TYPELIST_HPP
#define TYPELIST_HPP

#include <Types.hpp>

namespace simpleNewton {

/**|||**************************************************************************************************************************************
*
*   Description: Simple Newton's typelist module
*
|***************************************************************************************************************************************///+

namespace typelist {
namespace impl {

// The underlying type for the typelist implementation
template< class... TYPES >
struct typeNodes;

/* Operations on typelists */
// Calculate length
template< class TYPENODES >
struct typeNodes_length;

// Is a type in the list?
template< class TYPE, class... TYPES >
struct is_in_list;

// Append typelist
template< class... ALL_TYPES >
struct typeNodes_append;

// Concatenate typelist
template< class TYPELIST, class... TYPES >
struct typeNodes_concatenate;

// Remove type from typelist
template< class REM_T, class... TYPES >
struct typeNodes_remove;

// Remove type from typelist
template< class... TYPES >
struct typeNodes_removeDuplicates;
/* End: operations on typelists */

}   // namespace impl
}   // namespace typelist


// The do-all, no-instance wrapper
// Definition of the typelist
template< class... TYPES >
struct SN_CT_TYPELIST {
   using list = typelist::impl::typeNodes<TYPES...>;
   
   // 'Function style' operations associated with typelist
   /* Calculate length */
   enum { getSize = typelist::impl::typeNodes_length< list >::result };
   /* Is type in typelist */
   template< class TYPE >
   static inline constexpr bool isInList() { return typelist::impl::is_in_list< TYPE, TYPES... >::result; }
   /* Append typelist */
   template< class... MORE_TYPES >
   using appendList = typename typelist::impl::typeNodes_append< TYPES..., MORE_TYPES... >::list;
   /* Concatenate typelist */
   template< class TYPELIST >
   using concatenateList = typename typelist::impl::typeNodes_concatenate< TYPELIST, TYPES... >::list;
   /* Remove type from typelist */
   template< class REM_T >
   using removeFromList = typename typelist::impl::typeNodes_remove< REM_T, TYPES... >::list;
   /* Remove duplicates from typelist */
   using removeDuplicates = typename typelist::impl::typeNodes_removeDuplicates< TYPES... >::list;
   
   virtual void NoInstance() = 0;   // To prevent client to create instances of a typelist
};

}   // namespace simpleNewton

#include "Typelist.impl.hpp"
#endif
