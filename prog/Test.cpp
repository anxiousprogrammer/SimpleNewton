#include <iostream>
#include "simpleNewtonConfig.h"
#include <Asserts.hh>
#include <TypeTraits.hh>

int main() {
  
   // Asserts
   const int value = 10;
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
   
   // TypeTraits
   SN_ASSERT_INT_BASED( value );
   //SN_ASSERT_INT_BASED( ding );
   
   return 0;
}
