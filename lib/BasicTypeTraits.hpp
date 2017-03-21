#ifndef BASICTYPETRAITS_HPP
#define BASICTYPETRAITS_HPP

#include <Types.hpp>

namespace simpleNewton {
namespace types {

/**||***************************************************************************************************************************************
*
*   Description: TypeTraits implementation for the simpleNewton framework. Gentle reminder - this are all compile time checks.
*
|***************************************************************************************************************************************///+

// Declarations -> int and all related
template< class TYPE > struct AssertIntTypeFailed;
template< class TYPE > struct AssertIntRefFailed;
template< class TYPE > struct AssertIntPtrFailed;
template< class TYPE > struct AssertConstIntFailed;
template< class TYPE > struct AssertConstIntRefFailed;
template< class TYPE > struct AssertConstIntPtrFailed;
template< class TYPE > struct AssertConstPtrIntFailed;
template< class TYPE > struct AssertConstPtrConstIntFailed;

// Declarations -> size_t and all related
template< class TYPE > struct AssertSizeTypeFailed;
template< class TYPE > struct AssertSizeRefFailed;
template< class TYPE > struct AssertSizePtrFailed;
template< class TYPE > struct AssertConstSizeFailed;
template< class TYPE > struct AssertConstSizeRefFailed;
template< class TYPE > struct AssertConstSizePtrFailed;
template< class TYPE > struct AssertConstPtrSizeFailed;
template< class TYPE > struct AssertConstPtrConstSizeFailed;

// Declarations -> long_t and all related
template< class TYPE > struct AssertLongTypeFailed;
template< class TYPE > struct AssertLongRefFailed;
template< class TYPE > struct AssertLongPtrFailed;
template< class TYPE > struct AssertConstLongFailed;
template< class TYPE > struct AssertConstLongRefFailed;
template< class TYPE > struct AssertConstLongPtrFailed;
template< class TYPE > struct AssertConstPtrLongFailed;
template< class TYPE > struct AssertConstPtrConstLongFailed;

// Declarations -> large_t and all related
template< class TYPE > struct AssertLargeTypeFailed;
template< class TYPE > struct AssertLargeRefFailed;
template< class TYPE > struct AssertLargePtrFailed;
template< class TYPE > struct AssertConstLargeFailed;
template< class TYPE > struct AssertConstLargeRefFailed;
template< class TYPE > struct AssertConstLargePtrFailed;
template< class TYPE > struct AssertConstPtrLargeFailed;
template< class TYPE > struct AssertConstPtrConstLargeFailed;

// Declarations -> single_t and all related
template< class TYPE > struct AssertSingleTypeFailed;
template< class TYPE > struct AssertSingleRefFailed;
template< class TYPE > struct AssertSinglePtrFailed;
template< class TYPE > struct AssertConstSingleFailed;
template< class TYPE > struct AssertConstSingleRefFailed;
template< class TYPE > struct AssertConstSinglePtrFailed;
template< class TYPE > struct AssertConstPtrSingleFailed;
template< class TYPE > struct AssertConstPtrConstSingleFailed;

// Declarations -> real_t and all related
template< class TYPE > struct AssertRealTypeFailed;
template< class TYPE > struct AssertRealRefFailed;
template< class TYPE > struct AssertRealPtrFailed;
template< class TYPE > struct AssertConstRealFailed;
template< class TYPE > struct AssertConstRealRefFailed;
template< class TYPE > struct AssertConstRealPtrFailed;
template< class TYPE > struct AssertConstPtrRealFailed;
template< class TYPE > struct AssertConstPtrConstRealFailed;

// Declarations -> bool and std::string related
template< class TYPE > struct AssertBoolTypeFailed;
template< class TYPE > struct AssertStringTypeFailed;
template< class TYPE > struct AssertStringRefFailed;
template< class TYPE > struct AssertStringPtrFailed;
template< class TYPE > struct AssertConstStringFailed;
template< class TYPE > struct AssertConstStringRefFailed;
template< class TYPE > struct AssertConstStringPtrFailed;
template< class TYPE > struct AssertConstPtrStringFailed;
template< class TYPE > struct AssertConstStringConstPtrFailed;

// Smart pointers
template< class TYPE > struct AssertUniquePtrFailed;
template< class TYPE > struct AssertSharedPtrFailed;
template< class TYPE > struct AssertWeakPtrFailed;

// Declaration -> exact type similarity
template< class T1, class T2 > struct AssertExactTypeSimilarityFailed;


// Specializations -> int and all related
template<> struct AssertIntTypeFailed<int>                          { enum : bool { result = true }; };
template<> struct AssertIntRefFailed<int &>                         { enum : bool { result = true }; };
template<> struct AssertIntPtrFailed<int *>                         { enum : bool { result = true }; };
template<> struct AssertConstIntFailed< const int >                 { enum : bool { result = true }; };
template<> struct AssertConstIntRefFailed< const int & >            { enum : bool { result = true }; };
template<> struct AssertConstIntPtrFailed< const int * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrIntFailed< int * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstIntFailed< const int * const > { enum : bool { result = true }; };

// Specializations -> size_t and all related
template<> struct AssertSizeTypeFailed<size_t>                          { enum : bool { result = true }; };
template<> struct AssertSizeRefFailed<size_t &>                         { enum : bool { result = true }; };
template<> struct AssertSizePtrFailed<size_t *>                         { enum : bool { result = true }; };
template<> struct AssertConstSizeFailed< const size_t >                 { enum : bool { result = true }; };
template<> struct AssertConstSizeRefFailed< const size_t & >            { enum : bool { result = true }; };
template<> struct AssertConstSizePtrFailed< const size_t * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrSizeFailed< size_t * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstSizeFailed< const size_t * const > { enum : bool { result = true }; };

// Specializations -> long_t and all related
template<> struct AssertLongTypeFailed<long_t>                          { enum : bool { result = true }; };
template<> struct AssertLongRefFailed<long_t &>                         { enum : bool { result = true }; };
template<> struct AssertLongPtrFailed<long_t *>                         { enum : bool { result = true }; };
template<> struct AssertConstLongFailed< const long_t >                 { enum : bool { result = true }; };
template<> struct AssertConstLongRefFailed< const long_t & >            { enum : bool { result = true }; };
template<> struct AssertConstLongPtrFailed< const long_t * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrLongFailed< long_t * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstLongFailed< const long_t * const > { enum : bool { result = true }; };

// Specializations -> large_t and all related
template<> struct AssertLargeTypeFailed<large_t>                          { enum : bool { result = true }; };
template<> struct AssertLargeRefFailed<large_t &>                         { enum : bool { result = true }; };
template<> struct AssertLargePtrFailed<large_t *>                         { enum : bool { result = true }; };
template<> struct AssertConstLargeFailed< const large_t >                 { enum : bool { result = true }; };
template<> struct AssertConstLargeRefFailed< const large_t & >            { enum : bool { result = true }; };
template<> struct AssertConstLargePtrFailed< const large_t * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrLargeFailed< large_t * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstLargeFailed< const large_t * const > { enum : bool { result = true }; };

// Specializations -> single_t and all related
template<> struct AssertSingleTypeFailed<single_t>                          { enum : bool { result = true }; };
template<> struct AssertSingleRefFailed<single_t &>                         { enum : bool { result = true }; };
template<> struct AssertSinglePtrFailed<single_t *>                         { enum : bool { result = true }; };
template<> struct AssertConstSingleFailed< const single_t >                 { enum : bool { result = true }; };
template<> struct AssertConstSingleRefFailed< const single_t & >            { enum : bool { result = true }; };
template<> struct AssertConstSinglePtrFailed< const single_t * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrSingleFailed< single_t * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstSingleFailed< const single_t * const > { enum : bool { result = true }; };

// Specializations -> real_t and all related
template<> struct AssertRealTypeFailed<real_t>                          { enum : bool { result = true }; };
template<> struct AssertRealRefFailed<real_t &>                         { enum : bool { result = true }; };
template<> struct AssertRealPtrFailed<real_t *>                         { enum : bool { result = true }; };
template<> struct AssertConstRealFailed< const real_t >                 { enum : bool { result = true }; };
template<> struct AssertConstRealRefFailed< const real_t & >            { enum : bool { result = true }; };
template<> struct AssertConstRealPtrFailed< const real_t * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrRealFailed< real_t * const >            { enum : bool { result = true }; };
template<> struct AssertConstPtrConstRealFailed< const real_t * const > { enum : bool { result = true }; };

// Specializations -> bool and std::string
template<> struct AssertBoolTypeFailed<bool>                                   { enum : bool { result = true }; };
template<> struct AssertStringTypeFailed<std::string>                          { enum : bool { result = true }; };
template<> struct AssertStringRefFailed<std::string &>                         { enum : bool { result = true }; };
template<> struct AssertStringPtrFailed<std::string *>                         { enum : bool { result = true }; };
template<> struct AssertConstStringFailed< const std::string >                 { enum : bool { result = true }; };
template<> struct AssertConstStringRefFailed< const std::string & >            { enum : bool { result = true }; };
template<> struct AssertConstStringPtrFailed< const std::string * >            { enum : bool { result = true }; };
template<> struct AssertConstPtrStringFailed< std::string * const >            { enum : bool { result = true }; };
template<> struct AssertConstStringConstPtrFailed< const std::string * const > { enum : bool { result = true }; };

// Specializations -> smart pointers
template< class T > struct AssertUniquePtrFailed< std::unique_ptr<T> > { enum : bool { result = true }; };
template< class T > struct AssertSharedPtrFailed< std::shared_ptr<T> > { enum : bool { result = true }; };
template< class T > struct AssertWeakPtrFailed< std::weak_ptr<T> >     { enum : bool { result = true }; };

// Specialization -> exact type similarity
template< class T > struct AssertExactTypeSimilarityFailed< T, T > { enum : bool { result = true }; };

}   // namespace simpleNewton
}   // namespace types

#include <BasicTypeTraits.macro.hpp>
#endif





