/**||**************************************************************************************************************************************|
*
*   Description: Simple Newton's typelist implementation
*
|***************************************************************************************************************************************///+

namespace simpleNewton {

// Specialization -> tail-end of the typelist.
template< class TAIL >
struct typeNodes< TAIL > {
   using head = TAIL;
   using tail = NullType;
};

// Specialization -> Typelist peeler (note: recursive inheritance)
template< class H, class... TYPES >
struct typeNodes<H, TYPES...> : typeNodes<TYPES...> {
   using head = H;
   using tail = typeNodes<TYPES...>;
};


/*****************************************************************************************************************************************|
*
*   Operations on the above typelist: calc. length, find at index, add item, erase item.
*
|*****************************************************************************************************************************************/

//+****************************************************************************************************************************************
/* Calculate length operation */
// Terminator full specialization
template< class TAIL >
struct typeNodes_length< typeNodes< TAIL > > {
   enum { result = 1 };
};

// Recursive specialization
template< class H, class... TYPES >
struct typeNodes_length< typeNodes< H, TYPES... > > {
   enum { result = 1 + typeNodes_length< typeNodes<TYPES...> >::result };
};
/* End: Calculate length operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Append typelist operation */
// Full definition
template< class... ALL_TYPES >
struct typeNodes_append {
   using list = SN_CT_TYPELIST< ALL_TYPES... >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Concatenate typelist operation */
// Full definition
template< class... NEW_TYPES, class... TYPES >
struct typeNodes_concatenate< SN_CT_TYPELIST<NEW_TYPES...>, TYPES... > {
   using list = SN_CT_TYPELIST< TYPES..., NEW_TYPES... >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************


//+****************************************************************************************************************************************
/* Remove a type from typelist operation */
// Full definition
template< class REM_T, class... TAIL >
struct typeNodes_remove< REM_T, REM_T, TAIL... > {
   using list = SN_CT_TYPELIST< TAIL... >;
};

template< class REM_T, class END >
struct typeNodes_remove< REM_T, END > {
   using list = SN_CT_TYPELIST< END >;
};

template< class REM_T, class HEAD, class... TAIL >
struct typeNodes_remove< REM_T, HEAD, TAIL... > {
   using list = typename SN_CT_TYPELIST< HEAD >::template concatenateList< typename typeNodes_remove< REM_T, TAIL... >::list >;
};
/* End: Append typelist operation */
//+****************************************************************************************************************************************

}   // namespace simpleNewton
