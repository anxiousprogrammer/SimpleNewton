#ifndef SN_MATRIX2_HPP
#define SN_MATRIX2_HPP

#include <cmath>

#include <logger/Logger.hpp>
#include <types/DTInfo.hpp>

#include <Global.hpp>

#include "FArray.hpp"

//==========================================================================================================================================
//
//  This file is part of simpleNewton. simpleNewton is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  simpleNewton is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with simpleNewton (see LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
//
///   Contains the class template Matrix2, which is a mathematical container representing a 2x2 matrix.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/* Let the compiler know that vector2 is a thing */
template< typename T > class Vector2;
template< typename T > class Matrix2;

// Forward declarations of special products
template< typename T > Vector2<T> operator*( const Matrix2<T> &, const Vector2<T> & );
#endif

//=== CLASS ================================================================================================================================

/** This class serves as a mathematical container which represents the 2x2 matrix.
*
*   \tparam FP_TYPE_T   The underlying floating-point data type of the Matrix2.
*/
//==========================================================================================================================================

template< typename FP_TYPE_T >
class Matrix2 : public FArray< FP_TYPE_T, 4 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<FP_TYPE_T, 4>::data_;
   
public:
   
   /** \name Constructors and Destructor
   *   @{
   */
   /** Default initialization constructor. */
   Matrix2() = default;
   
   /** Direct initialization constructor which fills the matrix with a provided value.
   *
   *   \param _val   The value which is to be used to populate the matrix.
   */
   explicit Matrix2( const FP_TYPE_T & _val ) : FArray<FP_TYPE_T, 4>( _val ) { SN_CT_REQUIRE_FP_TYPE< FP_TYPE_T >(); }
   
   /** List initialization constructor which takes every value of the matrix as argument.
   *
   *   \param v1   The value at position (0,0) of the matrix.
   *   \param v2   The value at position (0,1) of the matrix.
   *   \param v3   The value at position (1,0) of the matrix.
   *   \param v4   The value at position (1,1) of the matrix.
   */
   Matrix2( const FP_TYPE_T & v1, const FP_TYPE_T & v2, const FP_TYPE_T & v3, const FP_TYPE_T & v4 ) : FArray<FP_TYPE_T, 4>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      data_[3] = v4;
      
      SN_CT_REQUIRE_FP_TYPE< FP_TYPE_T >();
   }
   
   /** Default destructor.*/
   ~Matrix2() = default;
   
   /** @} */
   
   
   
   /** \name Access
   *   @{
   */
   /** Operator (non-const): direct element-wise, linear access.
   *
   *   \param index   The container index corresponding to the element which is to be accessed.
   *   \return        A const qualified reference to the element.
   */
   inline FP_TYPE_T & operator[]( small_t index )     { SN_ASSERT_INDEX_WITHIN_SIZE( index, 4 ); return data_[index]; }
   
   /** A function (non-const) to access the elements of the matrix.
   *
   *   \param r   The row identifier.
   *   \param c   The column identifier.
   *   \return    A non-const reference to the element.
   */
   inline FP_TYPE_T & at( small_t r, small_t c ) {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   
   /** Operator (const): direct element-wise, linear access.
   *
   *   \param index   The container index corresponding to the element which is to be accessed.
   *   \return        A const qualified reference to the element.
   */
   inline const FP_TYPE_T & operator[]( small_t index ) const   { SN_ASSERT_INDEX_WITHIN_SIZE( index, 4 ); return data_[index]; }
   
   /** A function (const) to access the elements of the matrix.
   *
   *   \param r   The row identifier.
   *   \param c   The column identifier.
   *   \return    A const qualified reference to the element.
   */
   inline const FP_TYPE_T & at( small_t r, small_t c ) const {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   
   /** A function which returns the transposed matrix.
   *
   *   \return   A Matrix2 object which is the transposed form of the matrix.
   */
   inline Matrix2<FP_TYPE_T> t() const {
   
      return Matrix2<FP_TYPE_T>( data_[0], data_[2],
                                 data_[1], data_[3] );
   }
   
   /** @} */
   
   
   
   /** \name Characteristic
   *   @{
   */
   /** A function which returns the determinant of the matrix.
   *
   *   \return   The determinant of the matrix
   */
   inline FP_TYPE_T getDeterminant() const {
      return data_[0] * data_[3] - data_[1] * data_[2];
   }
   
   /** A function which investigates the invertibility of the matrix.
   *
   *   \return   True if the matrix is invertible, false if not.
   */
   inline bool isInvertible() const {
      return ( getDeterminant() == 0 ? false : true );
   }
   
   /** A function which returns the infinity norm of the matrix.
   *
   *   \return   The infinity norm of the matrix
   */
   inline FP_TYPE_T infinityNorm() const {

      FP_TYPE_T r_great1 = ( data_[0] >= data_[1] ? data_[0] : data_[1] );
      FP_TYPE_T r_great2 = ( data_[2] >= data_[3] ? data_[2] : data_[3] );
      
      return ( r_great1 >= r_great2 ? r_great1 : r_great2 );
   }
   
   /** @} */
   
   
   
   /** \name Arithmetic
   *   @{
   */
   /** Addition operator: operand is a 2x2 matrix.
   *
   *   \param operand   A 2x2 matrix with which the matrix has to be added.
   *   \return          A Matrix2 object which is the result of the addition.
   */
   inline Matrix2<FP_TYPE_T> operator+( const Matrix2<FP_TYPE_T> & operand ) const {
   
      return Matrix2<FP_TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], 
                                 data_[2] + operand.data_[2], data_[2] + operand.data_[2] );
   }
   
   /** Addition operator: operand is a scalar.
   *
   *   \param operand   The scalar with which the matrix has to be added.
   *   \return          A Matrix2 object which is the result of the addition.
   */
   inline Matrix2<FP_TYPE_T> operator+( const FP_TYPE_T & operand ) const {
   
      return Matrix2<FP_TYPE_T>( data_[0] + operand, data_[1] + operand,
                                 data_[2] + operand, data_[3] + operand );
   }
   
   /** Subtraction operator: operand is a 2x2 matrix.
   *
   *   \param operand   A 2x2 matrix which shall be subtracted from the matrix.
   *   \return          A Matrix2 object which is the result of the subtraction.
   */
   inline Matrix2<FP_TYPE_T> operator-( const Matrix2<FP_TYPE_T> & operand ) const {
   
      return Matrix2<FP_TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1],
                                 data_[2] - operand.data_[2], data_[3] - operand.data_[3] );
   }
   
   /** Subtraction operator: operand is a scalar.
   *
   *   \param operand   The scalar which shall be subtracted from the matrix.
   *   \return          A Matrix2 object which is the result of the subtraction.
   */
   inline Matrix2<FP_TYPE_T> operator-( const FP_TYPE_T & operand ) const {
   
      return Matrix2<FP_TYPE_T>( data_[0] - operand, data_[1] - operand,
                                 data_[2] - operand, data_[3] - operand );
   }
   
   /** Multiplication operator: operand is a 2x2 matrix.
   *
   *   \param op        A 2x2 matrix with whom the matrix is to be multiplied.
   *   \return          A Matrix2 object which is the result of the multiplication.
   */
   template< typename T > inline Matrix2<T> operator*( const Matrix2<T> & op ) {
   
      return Matrix2<FP_TYPE_T>( data_[0] * op.data_[0] + data_[1] * op.data_[2], 
                                 data_[0] * op.data_[1] + data_[1] * op.data_[3],
                                 data_[2] * op.data_[0] + data_[3] * op.data_[2], 
                                 data_[2] * op.data_[1] + data_[3] * op.data_[3] );
   }
   
   /** Multiplication operator: operand is a scalar.
   *
   *   \param operand   The scalar which shall be multiplied with every element of the matrix.
   *   \return          A Matrix2 object which is the result of the multiplication.
   */
   inline Matrix2<FP_TYPE_T> operator*( const FP_TYPE_T & operand ) const {
   
      return Matrix2<FP_TYPE_T>( data_[0] * operand, data_[1] * operand,
                                 data_[2] * operand, data_[3] * operand );
   }
   
   /** A function which implements the multiplication of a 2x2 matrix with a 2-dimensional vector. */
   template< typename T > friend Vector2<T> operator*( const Matrix2<T> &, const Vector2<T> & );
   
   /** Division operator: operand is a scalar. Notes on exception safety: strong safety guaranteed. The function throws a MathError 
   *   exception if division by zero is attempted.
   *
   *   \param operand   The scalar value by which every element of the matrix shall be divided.
   *   \return          A Matrix2 object which is the result of the division.
   */
   Matrix2<FP_TYPE_T> operator/( const FP_TYPE_T & operand ) const {
      
      SN_ASSERT_NOT_ZERO( operand );
      
      FP_TYPE_T inv = FP_TYPE_T();
      try {
         inv = static_cast<FP_TYPE_T>(1.0)/operand;
      }
      catch( const std::exception & ) {
         SN_THROW_MATH_ERROR( "MATH_Matrix2_Div_Zero" );
      }
      
      return Matrix2<FP_TYPE_T>( data_[0] * inv, data_[1] * inv,
                                 data_[2] * inv, data_[3] * inv );
   }
      
   /** @} */
   
   
   
   /** \name Comparison
   *   @{
   */
   /** Equal-to operator: operand is a scalar.
   *
   *   \param _ref   The scalar with which the matrix is to be compared.
   *   \return       True if the quantities are equal.
   */
   inline bool operator==( const FP_TYPE_T & _ref ) const {
      
      return ( std::fabs( data_[0] - _ref ) <= globalConstants::ZERO && std::fabs( data_[1] - _ref ) <= globalConstants::ZERO && 
               std::fabs( data_[2] - _ref ) <= globalConstants::ZERO && std::fabs( data_[3] - _ref ) <= globalConstants::ZERO );
   }
   
   /** Less-than operator: operand is a scalar.
   *
   *   \param _ref   The scalar with which the matrix is to be compared.
   *   \return       True if the matrix is less than the provided scalar value.
   */
   inline bool operator<( const FP_TYPE_T & _ref ) const {
      return ( data_[0] < _ref && data_[1] < _ref && data_[2] < _ref && data_[3] < _ref );
   }
   
   /** Less-than-equal-to operator: operand is a scalar.
   *
   *   \param _ref   The scalar with which the matrix is to be compared.
   *   \return       True if the matrix is less than or equal to the provided scalar value.
   */
   inline bool operator<=( const FP_TYPE_T & _ref ) const {
      return ( data_[0] <= _ref && data_[1] <= _ref && data_[2] <= _ref && data_[3] < _ref );
   }
   
   /** Greater-than operator: operand is a scalar.
   *
   *   \param _ref   The scalar with which the matrix is to be compared.
   *   \return       True if the matrix is greater than the provided scalar value.
   */
   inline bool operator>( const FP_TYPE_T & _ref ) const {
      return ( data_[0] > _ref && data_[1] > _ref && data_[2] > _ref && data_[3] > _ref );
   }
   
   /** Greater-than-equal-to operator: operand is a scalar.
   *
   *   \param _ref   The scalar with which the matrix is to be compared.
   *   \return       True if the matrix is greater than or equal to the provided scalar value.
   */
   inline bool operator>=( const FP_TYPE_T & _ref ) const {
      return ( data_[0] >= _ref && data_[1] >= _ref && data_[2] >= _ref && data_[3] >= _ref );
   }
   
   /** @} */
   
   
   
   /** \name Output
   *   @{
   */
   /** Output function which is compatible with the Logger. */
   template< typename T >
   friend Logger & operator<<( Logger & , const Matrix2<T> & );
   
   /** @} */
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Implementation of a friend function
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Every container in the simpleNewton framework is naturally compatible with the Logger class.
*
*   \param lg    An instance of Logger.
*   \param mat   The Matrix2 object to be output.
*/
template< typename FP_TYPE_T >
Logger & operator<<( Logger & lg, const Matrix2<FP_TYPE_T> & mat ) {
   
   lg.fixFP();
   lg << '\n' << "Matrix (2x2) " << mat[0] << " " << mat[1] << '\n' 
              << "             " << mat[2] << " " << mat[3] << '\n';
   lg.unfixFP();
   return lg;
}

}   // namespace simpleNewton

#endif
