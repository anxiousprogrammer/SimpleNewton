#include <iostream>
#include "simpleNewtonConfig.h"
#include <Asserts.hpp>
#include <Typelist.hpp>
#include <TypeConstraints.hpp>

// operator checking
class B {
public:
   bool operator==( const B & ) const { return true; }
   bool operator==( const int & ) const { return true; }
   bool operator<( const B & ) const { return true; }
   bool operator>( const B & ) const { return true; }
   bool operator<=( const B & ) const { return true; }
   bool operator>=( const B & ) const { return true; }
};

// Inheritance
class D : public B {};
class C { 
public:
   float operator()( int, int ) const volatile { std::cout << "Dings" << std::endl; return 0.0; }
};
class E : public D, public C {};

template< class T >
constexpr bool f1( T ) {
   //std::cout << "Here, got into the function, y'all" << std::endl;
   return true;
}

int main() {

   using namespace simpleNewton;
  
   // Asserts
   const int value = 10;
   
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
   /*SN_CT_ASSERT_INT( *pint );
   SN_CT_ASSERT_TYPE( ding, ConstSingle_t );
   SN_CT_ASSERT_STRICTLY_DERIVED_FROM( D, B );*/
   int j = 0;
   volatile const int k = 0;
   SN_CT_ASSERT_INT( j );
   SN_CT_ASSERT_CALLABLE( E() );
   SN_CT_ASSERT_COMPARABLE( B(), B() );
   SN_CT_ASSERT_SAME_TYPE( j, k );
   SN_CT_ASSERT_RVALUE( 2 );
   SN_CT_ASSERT_DERIVED_FROM<D, B>();
   
   return 0;
}
