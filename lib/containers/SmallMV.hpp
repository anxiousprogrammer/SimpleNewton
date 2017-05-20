#ifndef SN_SMALLMV_HPP
#define SN_SMALLMV_HPP

#include "Vector2.hpp"
#include "Matrix2.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"


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
///   Contains the special product operators of all possible combinations of Matrix2, Matrix3, Vector2 and Vector3.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


/** Special product operator: performs the multiplication of a 2x2 matrix (Matrix2 object) and a 2-dimensional vector (Vector2 object). The 
*   result is a 2-dimensional vector.
*
*   \param op1   The first operand must be a Matrix2 object.
*   \param op2   The second operand must be a Vector2 object.
*   \return      A Vector2 object which is the product.
*/
template< typename T > Vector2<T> operator*( const Matrix2<T> & op1, const Vector2<T> & op2 ) {

   return Vector2<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[1],
                      op1.data_[2] * op2.data_[0] + op1.data_[3] * op2.data_[1] );
}



/** Special product operator: performs the multiplication of a 2-dimensional vector (Vector2_t object) and a 2x2 matrix (Matrix2 object). 
*   The result is a 2-dimensional vector transposed.
*
*   \param op1   The first operand must be a Vector2_t object.
*   \param op2   The second operand must be a Matrix2 object.
*   \return      A Vector2_t object which is the product.
*/
template< typename T > Vector2_t<T> operator*( const Vector2_t<T> & op1, const Matrix2<T> & op2 ) {
 
   return Vector2_t<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[2],
                        op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[3] );
}



/** Special product operator: performs the multiplication of a 2-dimensional vector (Vector2 object) and its transpose (Vector2_t object). 
*   This product is known as the outer product. The result is a 2x2 matrix.
*
*   \param op1   The first operand must be a Vector2 object.
*   \param op2   The second operand must be a Vector2_t object.
*   \return      A Matrix2 object which is the product.
*/
template< typename T > Matrix2<T> operator*( const Vector2<T> & op1, const Vector2_t<T> & op2 ) {

   return Matrix2<T>( op1.data_[0] * op2.data_[0], op1.data_[0] * op2.data_[1],
                      op1.data_[1] * op2.data_[0], op1.data_[1] * op2.data_[1] );
}



/** Special product operator: performs the multiplication of a 3x3 matrix (Matrix3 object) and a 3-dimensional vector (Vector3 object). The 
*   result is a 3-dimensional vector.
*
*   \param op1   The first operand must be a Matrix3 object.
*   \param op2   The second operand must be a Vector3 object.
*   \return      A Vector3 object which is the product.
*/
template< typename T > Vector3<T> operator*( const Matrix3<T> & op1, const Vector3<T> & op2 ) {

   return Vector3<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[1] + op1.data_[2] * op2.data_[2],
                      op1.data_[3] * op2.data_[0] + op1.data_[4] * op2.data_[1] + op1.data_[5] * op2.data_[2],
                      op1.data_[6] * op2.data_[0] + op1.data_[7] * op2.data_[1] + op1.data_[8] * op2.data_[2] );
}



/** Special product operator: performs the multiplication of a 3-dimensional vector (Vector3_t object) and a 3x3 matrix (Matrix3 object). 
*   The result is a 3-dimensional vector transposed.
*
*   \param op1   The first operand must be a Vector3_t object.
*   \param op2   The second operand must be a Matrix3 object.
*   \return      A Vector3_t object which is the product.
*/
template< class T > Vector3_t<T> operator*( const Vector3_t<T> & op1, const Matrix3<T> & op2 ) {

   return Vector3_t<T>( op1.data_[0] * op2.data_[0] + op1.data_[1] * op2.data_[3] + op1.data_[2] * op2.data_[6],
                        op1.data_[0] * op2.data_[1] + op1.data_[1] * op2.data_[4] + op1.data_[2] * op2.data_[7],
                        op1.data_[0] * op2.data_[2] + op1.data_[1] * op2.data_[5] + op1.data_[2] * op2.data_[8] );
}



/** Special product operator: performs the multiplication of a 3-dimensional vector (Vector3 object) and its transpose (Vector3_t object). 
*   This product is known as the outer product. The result is a 3x3 matrix.
*
*   \param op1   The first operand must be a Vector3 object.
*   \param op2   The second operand must be a Vector3_t object.
*   \return      A Matrix3 object which is the product.
*/
template< typename T > Matrix3<T> operator*( const Vector3<T> & op1, const Vector3_t<T> & op2 ) {

   return Matrix3<T>( op1.data_[0]*op2.data_[0], op1.data_[0]*op2.data_[1], op1.data_[0]*op2.data_[2],
                      op1.data_[1]*op2.data_[0], op1.data_[1]*op2.data_[1], op1.data_[1]*op2.data_[2],
                      op1.data_[2]*op2.data_[0], op1.data_[2]*op2.data_[1], op1.data_[2]*op2.data_[2] );
}

}   // namespace simpleNewton

#endif
