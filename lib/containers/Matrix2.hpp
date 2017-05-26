#ifndef SN_MATRIX2_HPP
#define SN_MATRIX2_HPP

#include <logger/Logger.hpp>
#include <types/DTInfo.hpp>
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
*   \tparam TYPE_T   The underlying data type of the Matrix2.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class Matrix2 : public FArray< TYPE_T, 4 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 4>::data_;
   
public:
   
   /** \name Constructors and Destructor
   *   @{
   */
   /** List initialization constructor which takes every value of the matrix as argument.
   *
   *   \param v1   The value at position (0,0) of the matrix.
   *   \param v2   The value at position (0,1) of the matrix.
   *   \param v3   The value at position (1,0) of the matrix.
   *   \param v4   The value at position (1,1) of the matrix.
   */
   Matrix2( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3, const TYPE_T & v4 ) : FArray<TYPE_T, 4>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      data_[3] = v4;
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 TC)" );
   }
   
   /** Near-default copy constructor.
   *
   *   \param _ref   The reference Matrix2 object.
   */
   Matrix2( const Matrix2<TYPE_T> & _ref ) : FArray<TYPE_T, 4>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 CC)" );
   }
   
   /** Near-default move constructor.
   *
   *   \param _ref   The rvalue Matrix2 object which serves as the source of data.
   */
   Matrix2( Matrix2<TYPE_T> && _ref ) : FArray<TYPE_T, 4>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 MC)" );
   }
   
   /** Near-default destructor.*/
   ~Matrix2() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 4" << " (from Matrix2 Destr.)" );
   }
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** Operator (const): direct element-wise access.
   *
   *   \param r   The row identifier.
   *   \param c   The column identifier.
   *   \return    A const qualified reference to the element.
   */
   inline const TYPE_T & operator()( small_t r, small_t c ) const {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   
   /** Operator (non-const): direct element-wise access.
   *
   *   \param r   The row identifier.
   *   \param c   The column identifier.
   *   \return    A non-const reference to the element.
   */
   inline TYPE_T & operator()( small_t r, small_t c ) {
   
      SN_ASSERT_INDEX_WITHIN_SIZE( r, 2 );
      SN_ASSERT_INDEX_WITHIN_SIZE( c, 2 );
      return data_[ 2*r + c ];
   }
   
   /** A function which returns the transposed matrix.
   *
   *   \return   A Matrix2 object which is the transposed form of the matrix.
   */
   inline Matrix2<TYPE_T> t() const {
   
      return Matrix2<TYPE_T>( data_[0], data_[2],
                              data_[1], data_[3] );
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
   inline Matrix2<TYPE_T> operator+( const Matrix2<TYPE_T> & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], 
                              data_[2] + operand.data_[2], data_[2] + operand.data_[2] );
   }
   
   /** Addition operator: operand is a scalar.
   *
   *   \param operand   The scalar with which the matrix has to be added.
   *   \return          A Matrix2 object which is the result of the addition.
   */
   inline Matrix2<TYPE_T> operator+( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] + operand, data_[1] + operand,
                              data_[2] + operand, data_[3] + operand );
   }
   
   /** Subtraction operator: operand is a 2x2 matrix.
   *
   *   \param operand   A 2x2 matrix which shall be subtracted from the matrix.
   *   \return          A Matrix2 object which is the result of the subtraction.
   */
   inline Matrix2<TYPE_T> operator-( const Matrix2<TYPE_T> & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1],
                              data_[2] - operand.data_[2], data_[3] - operand.data_[3] );
   }
   
   /** Subtraction operator: operand is a scalar.
   *
   *   \param operand   The scalar which shall be subtracted from the matrix.
   *   \return          A Matrix2 object which is the result of the subtraction.
   */
   inline Matrix2<TYPE_T> operator-( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] - operand, data_[1] - operand,
                              data_[2] - operand, data_[3] - operand );
   }
   
   /** Multiplication operator: operand is a 2x2 matrix.
   *
   *   \param operand   A 2x2 matrix with whom the matrix is to be multiplied.
   *   \return          A Matrix2 object which is the result of the multiplication.
   */
   template< typename T > Matrix2<T> operator*( const Matrix2<T> & op2 ) {
   
      return Matrix2<T>( data_[0] * op2.data_[0] + data_[1] * op2.data_[2], 
                         data_[0] * op2.data_[1] + data_[1] * op2.data_[3],
                         data_[2] * op2.data_[0] + data_[3] * op2.data_[2], 
                         data_[2] * op2.data_[1] + data_[3] * op2.data_[3] );
   }
   
   /** Multiplication operator: operand is a scalar.
   *
   *   \param operand   The scalar which shall be multiplied with every element of the matrix.
   *   \return          A Matrix2 object which is the result of the multiplication.
   */
   inline Matrix2<TYPE_T> operator*( const TYPE_T & operand ) const {
   
      return Matrix2<TYPE_T>( data_[0] * operand, data_[1] * operand,
                              data_[2] * operand, data_[3] * operand );
   }
   
   /** A function which implements the multiplication of a 2x2 matrix with a 2-dimensional vector. */
   template< typename T > friend Vector2<T> operator*( const Matrix2<T> &, const Vector2<T> & );
   
   /** Division operator: operand is a scalar.
   *
   *   \param operand   The scalar value by which every element of the matrix shall be divided.
   *   \return          A Matrix2 object which is the result of the division.
   */
   inline Matrix2<TYPE_T> operator/( const TYPE_T & operand ) const {
      
      SN_ASSERT_NOT_ZERO( operand );
      
      #ifdef NDEBUG
      if( std::fabs(operand) <= globalConstants::ZERO )
         SN_THROW_INVALID_ARGUMENT( "IA_Matrix2_Div_Zero" );
      #endif

      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Matrix2<TYPE_T>( data_[0] * inv, data_[1] * inv,
                              data_[2] * inv, data_[3] * inv );
   }
   
   /** A function to calculate the determinant of the matrix.
   *
   *   \return   The value of the determinant of the matrix.
   */
   inline TYPE_T getDeterminant() {
      return ( data_[0]*data_[3] - data_[1]*data_[2] );
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
template< typename TYPE_T >
Logger & operator<<( Logger & lg, const Matrix2<TYPE_T> & mat ) {
   
   lg.fixFP();
   lg << '\n' << "Matrix (2x2) " << mat[0] << " " << mat[1] << '\n' 
              << "             " << mat[2] << " " << mat[3] << '\n';
   lg.unfixFP();
   return lg;
}

}   // namespace simpleNewton

#endif
