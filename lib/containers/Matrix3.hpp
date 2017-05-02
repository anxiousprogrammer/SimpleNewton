#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include <logger/BasicTypenameStr.hpp>
#include "Container.hpp"


namespace simpleNewton {

/* Let the compiler know that vector2 is a thing */
template< typename T > class Vector3;
template< typename T > class Matrix3;
template< typename T >
Vector3<T> operator*( const Matrix3<T> &, const Vector3<T> & );
template< typename T >
Matrix3<T> operator*( const Matrix3<T> &, const Matrix3<T> & );

/**||***************************************************************************************************************************************
*
*   Description: The 2x2 (square) matrix class
*
|***************************************************************************************************************************************///+

template< typename TYPE_T >
class Matrix3 : public Container< TYPE_T, 9 > {

public:
   
   /* Unveil the underlaying body of container */
   using Container<TYPE_T, 9>::data_;
   
   /* Specifying creation and destruction */
   /* NTC */ explicit Matrix3( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3, 
                               const TYPE_T & v4, const TYPE_T & v5, const TYPE_T & v6,
                               const TYPE_T & v7, const TYPE_T & v8, const TYPE_T & v9 ) : Container<TYPE_T, 9>() {
      data_[0] = v1; data_[1] = v2; data_[2] = v3;
      data_[3] = v4; data_[4] = v5; data_[5] = v6;
      data_[6] = v7; data_[7] = v8; data_[8] = v9;
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 9" + " (from Matrix3 TC)" );
   }
   /* CC */ Matrix3( const Matrix3<TYPE_T> & _ref ) : Container<TYPE_T, 9>(_ref) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 9" + " (from Matrix3 CC)" );
   }
   /* MC */ Matrix3( Matrix3<TYPE_T> && _ref ) : Container<TYPE_T, 9>( std::move(_ref) ) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 9" + " (from Matrix3 MC)" );
   }
   ~Matrix3() {
      SN_LOG_REPORT_EVENT( LogEventType::ResDealloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 9" + " (from Matrix3 Destr.)" );
   }
   
   /* Access */
   inline TYPE_T & operator()( small_t r, small_t c ) {
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 3 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 3 );
      return data_[ 2*r + c ];
   }
   inline const TYPE_T & operator()( small_t r, small_t c ) const {
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 3 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 3 );
      return data_[ 2*r + c ];
   }
   inline Matrix3<TYPE_T> t() const {
      return Matrix3<TYPE_T>( data_[0], data_[3], data_[6],
                              data_[1], data_[4], data_[7],
                              data_[2], data_[5], data_[8] );
   }
   
   /* Arithmetic completion */
   inline Matrix3<TYPE_T> operator+( const Matrix3<TYPE_T> & operand ) const {
      return Matrix3<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], data_[2] + operand.data_[2],
                              data_[3] + operand.data_[3], data_[4] + operand.data_[4], data_[5] + operand.data_[5],
                              data_[6] + operand.data_[6], data_[7] + operand.data_[7], data_[8] + operand.data_[8] );
   }
   inline Matrix3<TYPE_T> operator-( const Matrix3<TYPE_T> & operand ) const {
      return Matrix3<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1], data_[2] - operand.data_[2],
                              data_[3] - operand.data_[3], data_[4] - operand.data_[4], data_[5] - operand.data_[5],
                              data_[6] - operand.data_[6], data_[7] - operand.data_[7], data_[8] - operand.data_[8] );
   }
   /* Operations with scalars */
   inline Matrix3<TYPE_T> operator+( const TYPE_T & operand ) const {
      return Matrix3<TYPE_T>( data_[0] + operand, data_[1] + operand, data_[2] + operand,
                              data_[3] + operand, data_[4] + operand, data_[5] + operand,
                              data_[6] + operand, data_[7] + operand, data_[8] + operand );
   }
   inline Matrix3<TYPE_T> operator-( const TYPE_T & operand ) const {
      return Matrix3<TYPE_T>( data_[0] - operand, data_[1] - operand, data_[2] - operand,
                              data_[3] - operand, data_[4] - operand, data_[5] - operand,
                              data_[6] - operand, data_[7] - operand, data_[8] - operand );
   }
   inline Matrix3<TYPE_T> operator*( const TYPE_T & operand ) const {
      return Matrix3<TYPE_T>( data_[0] * operand, data_[1] * operand, data_[2] * operand,
                              data_[3] * operand, data_[4] * operand, data_[5] * operand,
                              data_[6] * operand, data_[7] * operand, data_[8] * operand );
   }
   inline Matrix3<TYPE_T> operator/( const TYPE_T & operand ) const {
      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Matrix3<TYPE_T>( data_[0] * inv, data_[1] * inv, data_[2] * inv,
                              data_[3] * inv, data_[4] * inv, data_[5] * inv,
                              data_[6] * inv, data_[7] * inv, data_[8] * inv );
   }
   
   /* Special products */
   /* MV */
   template< typename T >
   friend Vector3<T> operator*( const Matrix3<T> &, const Vector3<T> & );
   /* MM */
   template< typename T >
   friend Matrix3<T> operator*( const Matrix3<T> &, const Matrix3<T> & );
   
   /* Determinant */
   inline TYPE_T getDeterminant() {
      return ( data_[0] * (data_[4]*data_[8] - data_[5]*data_[7]) -
               data_[1] * (data_[3]*data_[8] - data_[5]*data_[6]) +
               data_[2] * (data_[3]*data_[7] - data_[4]*data_[6]) );
   }
   
   /* Output */
   friend Logger & operator<<( Logger & lg, const Matrix3<TYPE_T> & mat ) {
      lg.fixFP();
      lg << Logger::nl <<  "Matrix (3x3) " << mat[0] << " " << mat[1] << " " << mat[2] << Logger::nl
                       <<  "             " << mat[3] << " " << mat[4] << " " << mat[5] << Logger::nl
                       <<  "             " << mat[6] << " " << mat[7] << " " << mat[8] << Logger::nl;
      lg.unfixFP();
      return lg;
   }
};

}   // namespace simpleNewton

#endif