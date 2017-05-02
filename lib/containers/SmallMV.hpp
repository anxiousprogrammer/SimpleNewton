#ifndef SMALLMV_HPP
#define SMALLMV_HPP

#include "Vector2.hpp"
#include "Matrix2.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"


namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Special products help finally bring together the smaller arithmetic containers.
*
|***************************************************************************************************************************************///+

/* 2x2*2 MV product */
template< typename T >
Vector2<T> operator*( const Matrix2<T> & op1, const Vector2<T> & op2 ) {
   return Vector2<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[1],
                      op1.data_[2] * op2.data_[0] + op1.data_[3] * op2.data_[1] );
}


  
/* 2x2 MM product */
template< typename T >
Matrix2<T> operator*( const Matrix2<T> & op1, const Matrix2<T> & op2 ) {
   return Matrix2<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[2], op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[3],
                      op1.data_[2] * op2.data_[0] + op1.data_[3] * op2.data_[2], op1.data_[2] * op2.data_[1] + op1.data_[3] * op2.data_[3] );
}



/* 2x2 Outer product */
template< typename T >
Matrix2<T> operator*( const Vector2<T> & op1, const Vector2_t<T> & op2 ) {
   return Matrix2<T>( op1.data_[0] * op2.data_[0], op1.data_[0] * op2.data_[1],
                      op1.data_[1] * op2.data_[0], op1.data_[1] * op2.data_[1] );
}



/* 2*2x2 V'M product */
template< typename T >
inline Vector2_t<T> operator*( const Vector2_t<T> & op1, const Matrix2<T> & op2 ) {
   return Vector2_t<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[2],
                        op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[3] );
}



/* 3x3*3 MV product */
template< typename T >
Vector3<T> operator*( const Matrix3<T> & op1, const Vector3<T> & op2 ) {
   return Vector3<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[1] + op1.data_[2] * op2.data_[2],
                      op1.data_[3] * op2.data_[0] + op1.data_[4] * op2.data_[1] + op1.data_[5] * op2.data_[2],
                      op1.data_[6] * op2.data_[0] + op1.data_[7] * op2.data_[1] + op1.data_[8] * op2.data_[2] );
}


   
/* 3x3 MM product */
template< typename T >
Matrix3<T> operator*( const Matrix3<T> & op1, const Matrix3<T> & op2 ) {
   return Matrix3<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[3] + op1.data_[2] * op2.data_[6],
                      op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[4] + op1.data_[2] * op2.data_[7],
                      op1.data_[0] * op2.data_[2] + op1.data_[1] * op2.data_[5] + op1.data_[2] * op2.data_[8],
                      op1.data_[3] * op2.data_[0] + op1.data_[4] * op2.data_[3] + op1.data_[5] * op2.data_[6],
                      op1.data_[3] * op2.data_[1] + op1.data_[4] * op2.data_[4] + op1.data_[5] * op2.data_[7],
                      op1.data_[3] * op2.data_[2] + op1.data_[4] * op2.data_[5] + op1.data_[5] * op2.data_[8],
                      op1.data_[6] * op2.data_[0] + op1.data_[7] * op2.data_[3] + op1.data_[8] * op2.data_[6],
                      op1.data_[6] * op2.data_[1] + op1.data_[7] * op2.data_[4] + op1.data_[8] * op2.data_[7],
                      op1.data_[6] * op2.data_[2] + op1.data_[7] * op2.data_[5] + op1.data_[8] * op2.data_[8] );
}



/* 3x3 V'M product */
template< class T >
Vector3_t<T> operator*( const Vector3_t<T> & op1, const Matrix3<T> & op2 ) {
   return Vector3_t<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[3] + op1.data_[2] * op2.data_[6],
                        op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[4] + op1.data_[2] * op2.data_[7],
                        op1.data_[0] * op2.data_[2] + op1.data_[1] * op2.data_[5] + op1.data_[2] * op2.data_[8] );
}



/* 3x3 Outer product */
template< typename T >
Matrix3<T> operator*( const Vector3<T> & op1, const Vector3_t<T> & op2 ) {
   return Matrix3<T>( op1.data_[0]*op2.data_[0], op1.data_[0]*op2.data_[1], op1.data_[0]*op2.data_[2],
                      op1.data_[1]*op2.data_[0], op1.data_[1]*op2.data_[1], op1.data_[1]*op2.data_[2],
                      op1.data_[2]*op2.data_[0], op1.data_[2]*op2.data_[1], op1.data_[2]*op2.data_[2] );
}

}   // namespace simpleNewton

#endif
