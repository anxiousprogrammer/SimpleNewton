#include <iostream>
#include <fstream>
#include "simpleNewtonConfig.h"
#include <Asserts.hpp>
#include <TypeConstraints.hpp>


// Operator checking compile-time asserts test cases
template< class T > class CompType;

template< class T >
class ArithType {
public:
   bool operator==( const ArithType<T> & ) const;
   ArithType<T> operator+( const T & ) const;
   ArithType<T> operator+( const ArithType<T> & ) const;
   ArithType<T> operator-( const T & ) const;
   ArithType<T> operator-( const ArithType<T> & ) const;
   ArithType<T> operator*( const T & ) const;
   ArithType<T> operator*( const ArithType<T> & ) const;
   ArithType<T> operator/( const T & ) const;
   ArithType<T> operator/( const ArithType<T> & ) const;
   ArithType<T>&& operator=( const T & );
   ArithType<T>&& operator=( const ArithType<T> & );
};

template< typename T >
class CompType {
public:
   bool operator==( const CompType<T> & ) const { return true; }
   bool operator==( const T & ) const { return true; }
   bool operator==( const ArithType<T> & ) const { return true; }
   bool operator<( const CompType<T> & ) const { return true; }
   bool operator>( const CompType<T> & ) const { return true; }
   bool operator<=( const CompType<T> & ) const { return true; }
   bool operator>=( const CompType<T> & ) const { return true; }
   CompType<T> operator=( const CompType<T> & );
};

// Inheritance compile-time asserts test cases
/* Base class template */
template< class TYPE >
class B {};
/* Base class explicit instantiation */
template class B<int>;

/* Derived class and grandchild */
template< class TYPE >
class D : public B<TYPE> {};
class ED : public D<int> {};
/* Non-derived class */
class ND {};

/* class template for callable type */
template< typename T1, typename T2 >
class C { 
public:
   float operator()( T1, T2 ) const volatile { std::cout << "Dings" << std::endl; return 0.0; }
   void MemberFunction( const T1 & ) {}
};

/* function template for callable type */
template< class T >
bool f1( T ) {
   return true;
}
template bool f1<int>( int ); 

// (Trivially) constructible
class tc {
   tc( const tc & ) = default;
   tc( tc&& ) = default;
public:
   tc() = default;
};
class ntc {
   ntc() = default;
   ntc( const ntc & ) = default;
   ntc( ntc && ) = default;
};

// (copy) constructible
class cc {
public:
   cc( const cc & ) = default;
};

// (move) constructible
class mc {
   mc() = default;
   mc( const mc & ) = default;
public:
   mc( mc && ) = default;
};

// constructible
class constr {
public:
   explicit constr( int, float ) {}
};
class n_constr {
public:
   n_constr( int, float ) {}
   virtual void absy() = 0;
};

int main() {

   using namespace simpleNewton;
  
   /* Asserts */
   const int value = 10;
   
   SN_ASSERT( value == 10 );
   SN_ASSERT_EQUAL( value, 10 );
   SN_ASSERT_INEQUAL( value, 100 );
   SN_ASSERT_LESS_THAN( value, 11 );
   SN_ASSERT_LEQ( value, 10 );
   SN_ASSERT_GREATER_THAN( value, 9 );
   SN_ASSERT_GREQ( value, 10 );
   SN_ASSERT_ZERO( 1E-16 );
   
   SN_ASSERT_MSG( value == 10, "Here" );
   
   SN_ASSERT_SIZE_STRICTLY_LESS_THAN( 1, 2 );
   SN_ASSERT_SIZE_LESS_THAN( 1, 2 );
   SN_ASSERT_INDEX_WITHIN_SIZE( 1, 2 );
   
   /* TypeTraits */
   SN_CT_ASSERT_NUM_TEMPLATE_ARG< 4, float, int, long, double >();
   SN_CT_ASSERT< true >();
   
   SN_CT_ASSERT_VOID_TYPE<void>();
   
   SN_CT_ASSERT_INT_TYPE<int>();
   SN_CT_ASSERT_INT_TYPE<int &>();
   SN_CT_ASSERT_INT_TYPE<volatile int>();
   SN_CT_ASSERT_INT_TYPE<const volatile int &>();
   SN_CT_ASSERT_INT_TYPE<unsigned int>();
   SN_CT_ASSERT_INT_TYPE<long>();
   //SN_CT_ASSERT_NOT_INT_TYPE<const volatile unsigned long long>();
   SN_CT_ASSERT_INT( value );
   
   SN_CT_ASSERT_NOT_INT_TYPE<const volatile float &>();
   //SN_CT_ASSERT_NOT_INT_TYPE<const volatile int>();
   SN_CT_ASSERT_NOT_INT( float() );
   
   SN_CT_ASSERT_FP_TYPE<float>();
   SN_CT_ASSERT_FP_TYPE<double>();
   SN_CT_ASSERT_FP_TYPE<const volatile double &>();
   SN_CT_ASSERT_NOT_FP( C<int, int>() );
   //SN_CT_ASSERT_NOT_FP_TYPE< double >();
   
   SN_CT_ASSERT_SMALL_TYPE< const volatile small_t >();
   SN_CT_ASSERT_SMALL_TYPE< const small_t & >();
   SN_CT_ASSERT_SMALL( small_t() );
   //SN_CT_ASSERT_SMALL( large_t() );
   
   SN_CT_ASSERT_LARGE_TYPE< const volatile large_t >();
   SN_CT_ASSERT_LARGE_TYPE< const large_t & >();
   SN_CT_ASSERT_LARGE( large_t() );
   //SN_CT_ASSERT_LARGE( ID_t() );
   
   SN_CT_ASSERT_ID_TYPE< const volatile ID_t >();
   SN_CT_ASSERT_ID_TYPE< const ID_t & >();
   SN_CT_ASSERT_ID( ID_t() );
   //SN_CT_ASSERT_ID( small_t() );
   
   SN_CT_ASSERT_STRING_TYPE< const_string_t >();
   SN_CT_ASSERT_STRING_TYPE< volatile const_string_t >();
   SN_CT_ASSERT_STRING( std::string("Hello") );
   //SN_CT_ASSERT_STRING( double() );
   
   SN_CT_ASSERT_BOOL_TYPE< flag_t & >();
   SN_CT_ASSERT_BOOL( true );
   //SN_CT_ASSERT_BOOL_TYPE< string_t & >();
   
   int arr[] = { 0, 0, 0 };
   SN_CT_ASSERT_ARRAY_TYPE< int[3] >();
   SN_CT_ASSERT_ARRAY( arr );
   //SN_CT_ASSERT_ARRAY( int() );
   
   SN_CT_ASSERT_FUNCTION( f1<int> );
   //SN_CT_ASSERT_FUNCTION( int() );
   
   SN_CT_ASSERT_CLASS_TYPE< C< C<int, int>, float > >();
   SN_CT_ASSERT_OBJECT( C<float, double>() );
   //SN_CT_ASSERT_OBJECT( 3.0 );
   
   SN_CT_ASSERT_PTR_TYPE< std::unique_ptr<int> >();
   SN_CT_ASSERT_PTR_TYPE< std::shared_ptr< C<float, int> > >();
   SN_CT_ASSERT_PTR_TYPE< std::weak_ptr<float> >();
   SN_CT_ASSERT_PTR_TYPE< int* >();
   //SN_CT_ASSERT_PTR( float* );
   SN_CT_ASSERT_PTR_TO_CONST_TYPE<const_real_t*>();
   //SN_CT_ASSERT_PTR_TO_CONST_TYPE<real_t*>();
   
   bool (*fp)(int) = &f1<int>;
   SN_CT_ASSERT_FUNCTION_PTR_TYPE< int(*)(int, int) >();
   SN_CT_ASSERT_FUNCTION_PTR( fp );
   
   const int & rf = value;
   SN_CT_ASSERT_REFERENCE_TYPE< const int & >();
   //SN_CT_ASSERT_REFERENCE_TYPE< const int >();
   SN_CT_ASSERT_CONST_REFERENCE_TYPE< const int & >();
   SN_CT_ASSERT_CONST_REFERENCE( rf );
   //SN_CT_ASSERT_CONST_REFERENCE_TYPE< const int >();
   
   SN_CT_ASSERT_RVALUE_REFERENCE_TYPE< volatile int && >();
   //SN_CT_ASSERT_RVALUE_REFERENCE( ArithType() );
   SN_CT_ASSERT_NOT_RVALUE_REFERENCE_TYPE< const int & >();
   SN_CT_ASSERT_NOT_RVALUE_REFERENCE( int() );
   
   const int ci=0;
   SN_CT_ASSERT_CONST_TYPE< const int >();
   SN_CT_ASSERT_CONST( ci );
   //SN_CT_ASSERT_CONST_TYPE< int >();
   SN_CT_ASSERT_NOT_CONST_TYPE< int >();
   SN_CT_ASSERT_NOT_CONST( int() );
   
   SN_CT_ASSERT_VOLATILE_TYPE< volatile ArithType<int> >();
   //SN_CT_ASSERT_VOLATILE_TYPE< ArithType >();
   //SN_CT_ASSERT_NOT_VOLATILE_TYPE< volatile ArithType >();
   SN_CT_ASSERT_NOT_VOLATILE_TYPE< ArithType<float> >();
   
   SN_CT_ASSERT_UNSIGNED_TYPE< volatile const small_t & >();
   //SN_CT_ASSERT_UNSIGNED_TYPE< const string_t >();
   SN_CT_ASSERT_SIGNED( float() );
   
   SN_CT_ASSERT_RVALUE( 3.0 );
   //SN_CT_ASSERT_RVALUE( ci );
   SN_CT_ASSERT_LVALUE( ci );
   //SN_CT_ASSERT_LVALUE( ArithType() );
   
   int v;
   const int j = 0;
   SN_CT_ASSERT_SAME_TYPENAME< const C< C< C<int, int>, int >, int >, C< C< C<int, int>, int >, int > >();
   //SN_CT_ASSERT_SAME_TYPENAME< C< C< C<int, int>, int >, int >, int >();
   //SN_CT_ASSERT_STRICTLY_SAME_TYPENAME< const C< C< C<int, int>, int >, int >, C< C< C<int, int>, int >, int > >();
   SN_CT_ASSERT_STRICTLY_SAME_TYPENAME< C< C< C<int, int>, int >, int >, C< C< C<int, int>, int >, int > >();

   SN_CT_ASSERT_SAME_TYPE( v, j );
   SN_CT_ASSERT_SAME_TYPE( 3.0, 5.0 );
   //SN_CT_ASSERT_SAME_TYPE( v, 3.0 );
   SN_CT_ASSERT_STRICTLY_SAME_TYPE( v, v );
   
   SN_CT_ASSERT_TYPE<int>(1);
   SN_CT_ASSERT_TYPE<int>(v);
   SN_CT_ASSERT_TYPE<int>(j);
   //SN_CT_ASSERT_TYPE<int>(2.0);
   SN_CT_ASSERT_STRICTLY_TYPE( v, int );
   //SN_CT_ASSERT_STRICTLY_TYPE( j, int );
   
   SN_CT_ASSERT_TYPE_IN_TYPELIST< int, SN_CT_TYPELIST<int, float, double, long> >();
   //SN_CT_ASSERT_TYPE_IN_TYPELIST< unsigned long, SN_CT_TYPELIST<int, float, double, long> >();
   
   SN_CT_ASSERT_TYPELIST< SN_CT_TYPELIST< int, float, long, double > >();
   //SN_CT_ASSERT_TYPELIST< double >();
   SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER< ED, SN_CT_TYPELIST< int, float, B<int>, double > >();
   SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER< ED, SN_CT_TYPELIST< int, float, ED, double > >();
   //SN_CT_ASSERT_DERIVED_FROM_LIST_MEMBER< ND, SN_CT_TYPELIST< int, float, B<int>, double > >();
   
   SN_CT_ASSERT_DERIVED_FROM< D<int>, B<int> >();
   SN_CT_ASSERT_DERIVED_FROM< D<int>, D<int> >();
   //SN_CT_ASSERT_DERIVED_FROM< D<int>, int >();
   SN_CT_ASSERT_DERIVED_FROM< B<int>, B<int> >();
   //SN_CT_ASSERT_DERIVED_FROM< ND, B<int> >();
   SN_CT_ASSERT_INSTANCE_DERIVED_FROM( ED(), B<int>() );
   //SN_CT_ASSERT_INSTANCE_DERIVED_FROM( ND(), B<int>() );
   
   SN_CT_ASSERT_NOT_DERIVED_FROM< ND, B<int> >();
   //SN_CT_ASSERT_NOT_DERIVED_FROM< D<int>, B<int> >();
   SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( ND(), B<int>() );
   //SN_CT_ASSERT_INSTANCE_NOT_DERIVED_FROM( ED(), B<int>() );
   
   C<int, int> callable;
   SN_CT_ASSERT_CALLABLE_TYPE< C<int, int> >();
   //SN_CT_ASSERT_CALLABLE_TYPE< float >();
   SN_CT_ASSERT_CALLABLE( callable );
   SN_CT_ASSERT_CALLABLE( &f1<int> );
   //SN_CT_ASSERT_CALLABLE( int() );
   
   SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE< tc >();
   //SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE< SN_CT_TYPELIST<int> >();
   //SN_CT_ASSERT_TRIVIALLY_CONSTRUCTIBLE_TYPE< ntc >();
   
   SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE< cc >();
   //SN_CT_ASSERT_COPY_CONSTRUCTIBLE_TYPE< tc >();
   
   SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE< mc >();
   //SN_CT_ASSERT_MOVE_CONSTRUCTIBLE_TYPE< ntc >();
   
   SN_CT_ASSERT_CONSTRUCTIBLE_TYPE< constr, SN_CT_TYPELIST< int, float > >();
   SN_CT_ASSERT_CONSTRUCTIBLE_TYPE< constr, SN_CT_TYPELIST< float, float > >();   // Cast!
   //SN_CT_ASSERT_CONSTRUCTIBLE_TYPE< constr, SN_CT_TYPELIST< int, float, float > >();
   
   SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE< CompType<int>, CompType<int> >();
   SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE< CompType<int>, int >();
   SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE< CompType<int>, ArithType<int> >();
   //SN_CT_ASSERT_STRICTLY_COMPARABLE_TYPE< CompType<int>, CompType<float> >();
   
   SN_CT_ASSERT_COMPARABLE( CompType<int>(), CompType<int>() );
   //SN_CT_ASSERT_COMPARABLE_TYPE< CompType<int>, int >();
   //SN_CT_ASSERT_COMPARABLE_TYPE< CompType<int>, ArithType<int> >();
   //SN_CT_ASSERT_COMPARABLE_TYPE< CompType<int>, CompType<float> >();
   
   ArithType<int> inst;
   SN_CT_ASSERT_MOVE_ASSIGNABLE( inst, ArithType<int>() );
   SN_CT_ASSERT_MOVE_ASSIGNABLE_TYPE< ArithType<int>, ArithType<int> >();
   SN_CT_ASSERT_MOVE_ASSIGNABLE_TYPE< ArithType<int>, ArithType<int> >();
   
   CompType<int> a_inst1, a_inst2;
   SN_CT_ASSERT_COPY_ASSIGNABLE_TYPE< CompType<int>, CompType<int> >();
   SN_CT_ASSERT_COPY_ASSIGNABLE( a_inst1, a_inst2 );
   
   SN_CT_ASSERT_CAN_ADD_TYPE< ArithType<float>, float >();
   SN_CT_ASSERT_CAN_ADD( inst, ArithType<int>() );
   //SN_CT_ASSERT_CAN_ADD_TYPE< ArithType<float>, int >();
   
   SN_CT_ASSERT_CAN_SUBTRACT_TYPE< ArithType<float>, float >();
   SN_CT_ASSERT_CAN_SUBTRACT( inst, ArithType<int>() );
   //SN_CT_ASSERT_CAN_SUBTRACT_TYPE< ArithType<float>, int >();
   
   SN_CT_ASSERT_CAN_MULTIPLY_TYPE< ArithType<float>, float >();
   SN_CT_ASSERT_CAN_MULTIPLY( inst, ArithType<int>() );
   //SN_CT_ASSERT_CAN_MULTIPLY_TYPE< ArithType<float>, int >();
   
   SN_CT_ASSERT_CAN_DIVIDE_TYPE< ArithType<float>, float >();
   SN_CT_ASSERT_CAN_DIVIDE( inst, ArithType<int>() );
   //SN_CT_ASSERT_CAN_DIVIDE_TYPE< ArithType<float>, int >();
   
   SN_CT_ASSERT_ARITHMETIC_TYPE< ArithType<float> >();
   SN_CT_ASSERT_ARITHMETIC( inst );
   //SN_CT_ASSERT_ARITHMETIC_TYPE< CompType<float> >();
   
   return 0;
}
