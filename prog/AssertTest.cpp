#include <iostream>
#include "simpleNewtonConfig.h"
#include <Asserts.hpp>
#include <TypeTraits.hpp>

class B {};
class D : public B {};
class C {};
class E : public D, public C {};

int main() {

   using namespace simpleNewton;
  
   // Asserts
   const int value = 10;
   //int test = 0;
   const float ding = 10.0;
   
   SN_CT_ASSERT( value == 10 );
   SN_CT_ASSERT_EQUAL( value, 10 );
   SN_CT_ASSERT_INEQUAL( value, 11 );
   SN_CT_ASSERT_LESS_THAN( value, 11 );
   SN_CT_ASSERT_LEQ( value, 10 );
   SN_CT_ASSERT_GREATER_THAN( value, 9 );
   SN_CT_ASSERT_GREQ( value, 10 );
   SN_CT_ASSERT_ZERO( 1E-16 );
   
   SN_ASSERT( value == 10 );
   SN_ASSERT_EQUAL( value, 10 );
   SN_ASSERT_INEQUAL( value, 100 );
   SN_ASSERT_LESS_THAN( value, 11 );
   SN_ASSERT_LEQ( value, 10 );
   SN_ASSERT_GREATER_THAN( value, 9 );
   SN_ASSERT_GREQ( value, 10 );
   SN_ASSERT_ZERO( 1E-16 );
   
   SN_ASSERT_MSG( value == 10, "here" );
   
   SN_ASSERT_SIZE_STRICTLY_LESS_THAN( 1, 2 );
   SN_ASSERT_SIZE_LESS_THAN( 1, 2 );
   SN_ASSERT_INDEX_WITHIN_SIZE( 1, 2 );
   
   // TypeTraits
   SN_CT_ASSERT_TYPE( ding, ConstSingle_t );
   SN_CT_ASSERT_STRICTLY_DERIVED_FROM( D, B );
   
   std::shared_ptr<C> sp( new C );
   SN_CT_ASSERT_SHARED_PTR( sp );

   return 0;
}
