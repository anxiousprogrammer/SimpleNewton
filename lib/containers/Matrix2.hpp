#ifndef MATRIX2_HPP
#define MATRIX2_HPP

#include <logger/Logger.hpp>
#include <types/DTInfo.hpp>
#include "FArray.hpp"


namespace simpleNewton {

/* Let the compiler know that vector2 is a thing */
template< typename T > class Vector2;
template< typename T > class Matrix2;

// Forward declarations of special products
template< typename T > Vector2<T> operator*( const Matrix2<T> &, const Vector2<T> & );

/**||***************************************************************************************************************************************
*
*   Description: The 2x2 (square) matrix class
*
|***************************************************************************************************************************************///+

template< typename TYPE_T >
class Matrix2 : public FArray< TYPE_T, 4 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 4>::data_;
   
public:
   
   /* Specifying creation and destruction */
   /* NTC */ explicit Matrix2( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3, const TYPE_T & v4 ) : FArray<TYPE_T, 4>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      data_[3] = v4;
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 TC)" );
   }
   /* CC */ Matrix2( const Matrix2<TYPE_T> & _ref ) : FArray<TYPE_T, 4>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 CC)" );
   }
   /* MC */ Matrix2( Matrix2<TYPE_T> && _ref ) : FArray<TYPE_T, 4>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 MC)" );
   }
   ~Matrix2() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 Destr.)" );
   }
   
   /* Access */
   inline TYPE_T & operator()( small_t r, small_t c ) {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   inline const TYPE_T & operator()( small_t r, small_t c ) const {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   inline Matrix2<TYPE_T> t() const {
   
      return Matrix2<TYPE_T>( data_[0], data_[2],
                              data_[1], data_[3] );
   }
   
   /* Arithmetic completion */
   inline Matrix2<TYPE_T> operator+( const Matrix2<TYPE_T> & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], 
                              data_[2] + operand.data_[2], data_[2] + operand.data_[2] );
   }
   inline Matrix2<TYPE_T> operator-( const Matrix2<TYPE_T> & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1],
                              data_[2] - operand.data_[2], data_[3] - operand.data_[3] );
   }
   /* Operations with scalars */
   inline Matrix2<TYPE_T> operator+( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] + operand, data_[1] + operand,
                              data_[2] + operand, data_[3] + operand );
   }
   inline Matrix2<TYPE_T> operator-( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] - operand, data_[1] - operand,
                              data_[2] - operand, data_[3] - operand );
   }
   inline Matrix2<TYPE_T> operator*( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] * operand, data_[1] * operand,
                              data_[2] * operand, data_[3] * operand );
   }
   inline Matrix2<TYPE_T> operator/( const TYPE_T & operand ) const {

      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Matrix2<TYPE_T>( data_[0] * inv, data_[1] * inv,
                              data_[2] * inv, data_[3] * inv );
   }
   
   /* Special products are friends */
   /* MV */
   template< typename T > friend Vector2<T> operator*( const Matrix2<T> &, const Vector2<T> & );
   /* MM */
   template< typename T > Matrix2<T> operator*( const Matrix2<T> & op2 ) {
   
      return Matrix2<T>( data_[0] * op2.data_[0] + data_[1] * op2.data_[2], 
                         data_[0] * op2.data_[1] + data_[1] * op2.data_[3],
                         data_[2] * op2.data_[0] + data_[3] * op2.data_[2], 
                         data_[2] * op2.data_[1] + data_[3] * op2.data_[3] );
   }
   
   /* Determinant */
   inline TYPE_T getDeterminant() {
      return ( data_[0]*data_[3] - data_[1]*data_[2] );
   }
   
   /* Output */
   friend Logger & operator<<( Logger & lg, const Matrix2<TYPE_T> & mat ) {
   
      lg.fixFP();
      lg << '\n' << "Matrix (2x2) " << mat[0] << " " << mat[1] << '\n' 
                 << "             " << mat[2] << " " << mat[3] << '\n';
      lg.unfixFP();
      return lg;
   }
   
};

}   // namespace simpleNewton

#endif
