#include <iostream>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

// Test classes
template< typename T >
struct TestC1 {};
struct TestC2 {};

int main() {
   
   using namespace simpleNewton;
   
   // Test calc. length and concatenate 'functions' of typelist implementation.
   // Calc. length test
   using TL_size_test = SN_CT_TYPELIST< TestC1<int>, unsigned int, TestC2, unsigned long, long long, unsigned long long >;
   SN_ASSERT_SIZE_SAME( TL_size_test::getSize, 6 );
   // Append test
   using TL_append_test  = SN_CT_TYPELIST< float, char, TestC1<int*> >;
   using TL_appended     = TL_append_test::appendList< TestC1<float*> >;
   using TL_append_proof = SN_CT_TYPELIST< float, char, TestC1<int*>, TestC1<float*> >;
   SN_CT_ASSERT_SAME_TYPENAME( TL_appended, TL_append_proof );
   // Concatenate test
   using TL_concat_test  = SN_CT_TYPELIST< TestC1<int>, float >;
   using TL_concatenated = TL_concat_test::concatenateList< TL_concat_test >;
   using TL_concat_proof = SN_CT_TYPELIST< TestC1<int>, float, TestC1<int>, float >;
   SN_CT_ASSERT_SAME_TYPENAME( TL_concatenated, TL_concat_proof );
   
   // Test remove from list and remove duplicate operations of typelist implementation.
   // Remove from list
   using TL_rem_test  = SN_CT_TYPELIST< int, char, double, float, int >;
   using TL_removed   = TL_rem_test::removeFromList< int >;
   using TL_rem_proof = SN_CT_TYPELIST< char, double, float >;
   SN_CT_ASSERT_SAME_TYPENAME( TL_removed, TL_rem_proof );
   // Removing from empty typelist
   using TL_rem_null     = SN_CT_TYPELIST< NullType >;
   using TL_removed_null = TL_rem_null::removeFromList< float >::removeFromList< TestC2 >;
   SN_CT_ASSERT_SAME_TYPENAME( TL_rem_null, TL_removed_null );
   // Remove duplicates from list
   using TL_dup_test  = SN_CT_TYPELIST< float, long, int, int, int, float >;
   using TL_no_dup    = TL_dup_test::removeDuplicates;
   using TL_dup_proof = SN_CT_TYPELIST< float, long, int >;
   SN_CT_ASSERT_SAME_TYPENAME( TL_no_dup, TL_dup_proof );
   
   return 0;
}
