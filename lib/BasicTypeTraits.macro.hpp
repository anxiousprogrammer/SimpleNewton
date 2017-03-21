#ifndef BASICTYPETRAITS_MACRO_HPP
#define BASICTYPETRAITS_MACRO_HPP

/**||***************************************************************************************************************************************
*
*   Description: Macros for the BasicTypeTraits.hpp
*
|***************************************************************************************************************************************///+

#ifdef NDEBUG

#define SN_CT_ASSERT_INT( VAR )
#define SN_CT_ASSERT_INT_REF( VAR )
#define SN_CT_ASSERT_INT_PTR( VAR )
#define SN_CT_ASSERT_CONST_INT( VAR )
#define SN_CT_ASSERT_CONST_INT_REF( VAR )
#define SN_CT_ASSERT_CONST_INT_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_INT( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_INT( VAR )

#define SN_CT_ASSERT_SIZE_T( VAR )
#define SN_CT_ASSERT_SIZE_T_REF( VAR )
#define SN_CT_ASSERT_SIZE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_SIZE_T( VAR )
#define SN_CT_ASSERT_CONST_SIZE_T_REF( VAR )
#define SN_CT_ASSERT_CONST_SIZE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_SIZE_T( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_SIZE_T( VAR )

#define SN_CT_ASSERT_LONG_T( VAR )
#define SN_CT_ASSERT_LONG_T_REF( VAR )
#define SN_CT_ASSERT_LONG_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_LONG_T( VAR )
#define SN_CT_ASSERT_CONST_LONG_T_REF( VAR )
#define SN_CT_ASSERT_CONST_LONG_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_LONG_T( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_LONG_T( VAR )

#define SN_CT_ASSERT_LARGE_T( VAR )
#define SN_CT_ASSERT_LARGE_T_REF( VAR )
#define SN_CT_ASSERT_LARGE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_LARGE_T( VAR )
#define SN_CT_ASSERT_CONST_LARGE_T_REF( VAR )
#define SN_CT_ASSERT_CONST_LARGE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_LARGE_T( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_LARGE_T( VAR )

#define SN_CT_ASSERT_SINGLE_T( VAR )
#define SN_CT_ASSERT_SINGLE_T_REF( VAR )
#define SN_CT_ASSERT_SINGLE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_SINGLE_T( VAR )
#define SN_CT_ASSERT_CONST_SINGLE_T_REF( VAR )
#define SN_CT_ASSERT_CONST_SINGLE_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_SINGLE_T( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_SINGLE_T( VAR )

#define SN_CT_ASSERT_REAL_T( VAR )
#define SN_CT_ASSERT_REAL_T_REF( VAR )
#define SN_CT_ASSERT_REAL_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_REAL_T( VAR )
#define SN_CT_ASSERT_CONST_REAL_T_REF( VAR )
#define SN_CT_ASSERT_CONST_REAL_T_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_REAL_T( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_REAL_T( VAR )

#define SN_CT_ASSERT_BOOL( VAR )
#define SN_CT_ASSERT_STRING( VAR )
#define SN_CT_ASSERT_STRING_REF( VAR )
#define SN_CT_ASSERT_STRING_PTR( VAR )
#define SN_CT_ASSERT_CONST_STRING( VAR )
#define SN_CT_ASSERT_CONST_STRING_REF( VAR )
#define SN_CT_ASSERT_CONST_STRING_PTR( VAR )
#define SN_CT_ASSERT_CONST_PTR_STRING( VAR )
#define SN_CT_ASSERT_CONST_PTR_CONST_STRING( VAR )

#define SN_CT_ASSERT_SAME_TYPENAME( TYPE1, TYPE2 )
#define SN_CT_ASSERT_SAME_TYPE( VAR1, VAR2 )
#define SN_CT_ASSERT_TYPE( VAR, ... )

#define SN_CT_ASSERT_UNIQUE_PTR( VAR )
#define SN_CT_ASSERT_SHARED_PTR( VAR )
#define SN_CT_ASSERT_WEAK_PTR( VAR )

#else

#define SN_CT_ASSERT_INT( VAR ) \
   do { if( simpleNewton::types::AssertIntTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_INT_REF( VAR ) \
   do { if( simpleNewton::types::AssertIntRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_INT_PTR( VAR ) \
   do { if( simpleNewton::types::AssertIntPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_INT( VAR ) \
   do { if( simpleNewton::types::AssertConstIntFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_INT_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstIntRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_INT_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstIntPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_INT( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrIntFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_INT( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstIntFailed<decltype(VAR)>::result ) break; } while(false)


#define SN_CT_ASSERT_SIZE_T( VAR ) \
   do { if( simpleNewton::types::AssertSizeTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SIZE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertSizeRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SIZE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertSizePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SIZE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstSizeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SIZE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstSizeRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SIZE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstSizePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_SIZE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrSizeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_SIZE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstSizeFailed<decltype(VAR)>::result ) break; } while(false)


#define SN_CT_ASSERT_LONG_T( VAR ) \
   do { if( simpleNewton::types::AssertLongTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_LONG_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertLongRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_LONG_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertLongPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LONG_T( VAR ) \
   do { if( simpleNewton::types::AssertConstLongFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LONG_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstLongRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LONG_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstLongPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_LONG_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrLongFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_LONG_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstLongFailed<decltype(VAR)>::result ) break; } while(false)


#define SN_CT_ASSERT_LARGE_T( VAR ) \
   do { if( simpleNewton::types::AssertLargeTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_LARGE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertLargeRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_LARGE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertLargePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LARGE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstLargeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LARGE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstLargeRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_LARGE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstLargePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_LARGE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrLargeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_LARGE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstLargeFailed<decltype(VAR)>::result ) break; } while(false)


#define SN_CT_ASSERT_SINGLE_T( VAR ) \
   do { if( simpleNewton::types::AssertSingleTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SINGLE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertSingleRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SINGLE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertSinglePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SINGLE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstSingleFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SINGLE_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstSingleRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_SINGLE_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstSinglePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_SINGLE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrSingleFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_SINGLE_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstSingleFailed<decltype(VAR)>::result ) break; } while(false)

   
#define SN_CT_ASSERT_REAL_T( VAR ) \
   do { if( simpleNewton::types::AssertRealTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_REAL_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertRealRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_REAL_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertRealPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_REAL_T( VAR ) \
   do { if( simpleNewton::types::AssertConstRealFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_REAL_T_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstRealRef<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_REAL_T_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstRealPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_REAL_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrRealFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_REAL_T( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstRealFailed<decltype(VAR)>::result ) break; } while(false)
   

#define SN_CT_ASSERT_BOOL( VAR ) \
   do { if( simpleNewton::types::AssertBoolTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_STRING( VAR ) \
   do { if( simpleNewton::types::AssertStringTypeFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_STRING_REF( VAR ) \
   do { if( simpleNewton::types::AssertStringRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_STRING_PTR( VAR ) \
   do { if( simpleNewton::types::AssertStringPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_STRING( VAR ) \
   do { if( simpleNewton::types::AssertConstStringFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_STRING_REF( VAR ) \
   do { if( simpleNewton::types::AssertConstStringRefFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_STRING_PTR( VAR ) \
   do { if( simpleNewton::types::AssertConstStringPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_STRING( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrStringFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_CONST_PTR_CONST_STRING( VAR ) \
   do { if( simpleNewton::types::AssertConstPtrConstStringFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SAME_TYPENAME( TYPE1, TYPE2 ) \
   do { if( simpleNewton::types::AssertExactTypeSimilarityFailed<TYPE1, TYPE2>::result ) break; } while(false)
   
#define SN_CT_ASSERT_SAME_TYPE( VAR1, VAR2 ) \
   do { if( simpleNewton::types::AssertExactTypeSimilarityFailed<decltype(VAR1), decltype(VAR2)>::result ) break; } while(false)

#define SN_CT_ASSERT_TYPE( VAR, ... ) \
   do { if( simpleNewton::types::AssertExactTypeSimilarityFailed<decltype(VAR), __VA_ARGS__>::result ) break; } while(false)


#define SN_CT_ASSERT_UNIQUE_PTR( VAR ) \
   do { if( simpleNewton::types::AssertUniquePtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_SHARED_PTR( VAR ) \
   do { if( simpleNewton::types::AssertSharedPtrFailed<decltype(VAR)>::result ) break; } while(false)

#define SN_CT_ASSERT_WEAK_PTR( VAR ) \
   do { if( simpleNewton::types::AssertWeakPtrFailed<decltype(VAR)>::result ) break; } while(false)

#endif   // NDEBUG

#endif
