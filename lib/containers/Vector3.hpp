#ifndef SN_VECTOR3_HPP
#define SN_VECTOR3_HPP

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
///   Contains the class templates Vector3 and Vector3_t, which are mathematical containers representing a 3-dimensional vector and its
///   transpose respectively.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Forward declarations: Matrix and Vector2 transposed
template< class T > class Matrix3;
template< class T > class Vector3;
template< class T > class Vector3_t;

// Forward declarations: special product
template< typename T > Matrix3<T> operator*( const Vector3<T> &, const Vector3_t<T> & );   // outer product
#endif

//=== CLASS ================================================================================================================================

/** Vector3 serves as a mathematical container which represents the 3-dimensional vector.
*
*   \tparam TYPE_T   The underlying data type of the Vector3.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class Vector3 : public FArray< TYPE_T, 3 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 3>::data_;
   
public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** List initialization constructor which creates a Vector3 object by assigning a value to each element.
   *
   *   \param v1   The value of the first element.
   *   \param v2   The value of the second element.
   *   \param v3   The value of the third element.
   */
   Vector3( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3 ) : FArray<TYPE_T, 3>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 TC)" );
   }
   
   /** Near-default copy constructor.
   *
   *   \param _ref   The reference Vector3 object whose values are to be used for initialization.
   */
   Vector3( const Vector3<TYPE_T> & _ref ) : FArray<TYPE_T, 3>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 CC1)" );
   }
   
   /** Near-default move constructor.
   *
   *   \param _ref   The reference Vector3 object whose values are to be used for initialization.
   */
   Vector3( Vector3<TYPE_T> && _ref ) : FArray<TYPE_T, 3>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 MC1)" );
   }
   
   /** Near-default destructor. */
   ~Vector3() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 Destr.)" );
   }
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** Operator (non-const): direct element-wise access.
   *
   *   \param index   The container index corresponding to the element which is to be accessed.
   *   \return        A non-const reference to the element.
   */
   inline TYPE_T & operator()( small_t index )             { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   
   /** Operator (const): direct element-wise access.
   *
   *   \param index   The container index corresponding to the element which is to be accessed.
   *   \return        A const qualified reference to the element.
   */
   inline const TYPE_T & operator()( small_t index ) const { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   
   /** A function which returns a transposed form of the 3-dimensional vector.
   *
   *   \return   A Vector3_t object which is the transpose of the vector.
   */
   inline Vector3_t<TYPE_T> t() const                      { return Vector3_t<TYPE_T>( data_[0], data_[1], data_[2] );     }
   
   /** @} */
   
   /** \name Arithmetic
   *   @{
   */
   /** Addition operator: operand is a 3D vector.
   *
   *   \param operand   A 3D vector with which the vector has to be added.
   *   \return          A Vector3 object which is the result of the addition.
   */
   inline Vector3<TYPE_T> operator+( const Vector3<TYPE_T> & operand ) const {
      return Vector3<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], data_[2] + operand.data_[2] );
   }
   
   /** Addition operator: operand is a scalar.
   *
   *   \param operand   A scalar with which the vector has to be added.
   *   \return          A Vector3 object which is the result of the addition.
   */
   inline Vector3<TYPE_T> operator+( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] + operand, data_[1] + operand, data_[2] + operand );
   }
   
   /** Subtraction operator: operand is a 3D vector.
   *
   *   \param operand   A 3D vector which shall be subtracted from the vector.
   *   \return          A Vector3 object which is the result of the subtraction.
   */
   inline Vector3<TYPE_T> operator-( const Vector3<TYPE_T> & operand ) const {
      return Vector3<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1], data_[2] + operand.data_[2] );
   }

   /** Subtraction operator: operand is a scalar.
   *
   *   \param operand   A scalar which shall be subtracted from the vector.
   *   \return          A Vector3 object which is the result of the subtraction.
   */
   inline Vector3<TYPE_T> operator-( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] - operand, data_[1] - operand, data_[2] + operand );
   }
   
   /** Multiplication operator: operand is a scalar.
   *
   *   \param operand   A scalar with which the vector is to be multiplied.
   *   \return          A Vector3 object which is the result of the multiplication.
   */
   inline Vector3<TYPE_T> operator*( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] * operand, data_[1] * operand, data_[2] + operand );
   }
   
   /** Multiplication operator: performs the outer product of 2-dimensional vectors. */
   template< typename T > friend Matrix3<T> operator*( const Vector3<T> &, const Vector3_t<T> & );
   
   /** Multiplication operator: performs the inner product (dot-product) of 2-dimensional vectors. */
   template< typename T > friend T Vector3_t<T>::operator*( const Vector3<T> & ) const;
   
   /** Division operator: operand is a scalar.
   *
   *   \param operand   The scalar value by which every element of the vector shall be divided.
   *   \return          A Vector3 object which is the result of the division.
   */
   inline Vector3<TYPE_T> operator/( const TYPE_T & operand ) const {
      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Vector3<TYPE_T>( data_[0] * inv, data_[1] * inv, data_[2] * inv );
   }
   
   /** @} */
   
   /** \name Output
   *   @{
   */
   /** Output function which is compatible with the Logger. */
   template< typename T >
   friend Logger & operator<<( Logger & lg, const Vector3<T> & );
   /** @} */
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Implementation of output
//////////////////////////////

/** Every container in the simpleNewton framework is naturally compatible with the Logger class.
*
*   \param lg    An instance of Logger.
*   \param vec   The Vector3 object to be output.
*/
template< typename TYPE_T >
Logger & operator<<( Logger & lg, const Vector3<TYPE_T> & vec ) {
   
   lg.fixFP();
   lg << '\n' << "Vector3 (t)   [" << vec[0] << "   " << vec[1] << "   " << vec[2] << "]   " << '\n';
   lg.unfixFP();
   return lg;
}



//=== CLASS ================================================================================================================================

/** Vector3_t serves as a mathematical container which represents the transposed 3-dimensional vector.
*
*   \tparam TYPE_T   The underlying data type of the Vector3_t.
*/
//==========================================================================================================================================

template< class TYPE_T >
class Vector3_t : public FArray< TYPE_T, 3 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 3>::data_;
   
private:
   
   /* NTC */ explicit Vector3_t( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3 ) : FArray<TYPE_T, 3>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t TC)" );
   }
   
public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Near-default copy constructor.
   *
   *   \param _ref   The reference Vector3_t object whose values are to be used for initialization.
   */
   Vector3_t( const Vector3_t<TYPE_T> & _ref ) : FArray<TYPE_T, 3>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t CC)" );
   }
   
   /** Near-default move constructor.
   *
   *   \param _ref   The reference Vector3_t object whose values are to be used for initialization.
   */
   Vector3_t( Vector3_t<TYPE_T> && _ref ) : FArray<TYPE_T, 3>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t MC)" );
   }
   
   /** Near-default destructor. */
   ~Vector3_t() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3"
                                                        << " (from Vector3_t Destr.)" );
   }
   
   /** @} */

   /** \name Arithmetic
   *   @{
   */
   /** Multiplication operator: dot-product of 3-dimensional vectors.
   *
   *   \param op   The operand, which is a 3-dimensional vector.
   *   \return     The dot-product in underlying field type.
   */
   inline TYPE_T operator*( const Vector3<TYPE_T> & op ) const {
      return ( data_[0] * op.data_[0] + data_[1] * op.data_[1] + data_[2] * op.data_[2] );
   }
   
   /** Multiplication operator: performs the multiplication of a transposed 3-dimensional vector and a 3x3 matrix. */
   template< class T > friend Vector3_t<T> operator*( const Vector3_t<T> &, const Matrix3<T> & );
   
   /** @} */
   
   /** A function which returns a transposed form of a 3-dimensional vector. */
   friend Vector3_t<TYPE_T> Vector3<TYPE_T>::t() const;
};


}   // namespace simpleNewton

#endif
