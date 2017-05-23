#ifndef SN_VECTOR2_HPP
#define SN_VECTOR2_HPP

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
///   Contains the class templates Vector2 and Vector2_t, which are mathematical containers representing a 2-dimensional vector and its
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
template< class T > class Matrix2;
template< class T > class Vector2;
template< class T > class Vector2_t;

// Forward declarations: Interactions with objects of other mathematical types
template< typename T > Matrix2<T> operator*( const Vector2<T> &, const Vector2_t<T> & );     // Outer product
#endif

//=== CLASS ================================================================================================================================

/** This class serves as a mathematical container which represents the 2-dimensional vector.
*
*   \tparam TYPE_T   The underlying data type of the Vector2.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class Vector2 : public FArray< TYPE_T, 2 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 2>::data_;
   
public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** List initialization constructor which creates a Vector2 object by assigning a value to each element.
   *
   *   \param v1   The value of the first element.
   *   \param v2   The value of the second element.
   */
   Vector2( const TYPE_T & v1, const TYPE_T & v2 ) : FArray<TYPE_T, 2>() {

      data_[0] = v1;
      data_[1] = v2;
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2 DIC)" );
   }
   
   /** Near-default copy constructor.
   *
   *   \param _ref   The reference Vector2 object whose values are to be used for initialization.
   */
   Vector2( const Vector2<TYPE_T> & _ref ) : FArray<TYPE_T, 2>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2 CC)" );
   }
   
   /** Near-default move constructor.
   *
   *   \param _ref   The Vector2 object whose values are to be used for initialization.
   */
   Vector2( Vector2<TYPE_T> && _ref ) : FArray<TYPE_T, 2>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2 MC)" );
   }
   
   /** Near-default destructor. */
   ~Vector2() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2 Destr.)" );
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
   
   /** A function which returns a transposed form of the 2-dimensional vector.
   *
   *   \return   A Vector2_t object which is the transpose of the vector.
   */
   inline Vector2_t<TYPE_T> t() const                      { return Vector2_t<TYPE_T>( data_[0], data_[1] ); }
   
   /** @} */
   
   /** \name Arithmetic
   *   @{
   */
   /** Addition operator: operand is a 2D vector.
   *
   *   \param operand   A 2D vector with which the vector has to be added.
   *   \return          A Vector2 object which is the result of the addition.
   */
   inline Vector2<TYPE_T> operator+( const Vector2<TYPE_T> & operand ) const {
      return Vector2<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1] );
   }
   
   /** Addition operator: operand is a scalar.
   *
   *   \param operand   A scalar with which the vector has to be added.
   *   \return          A Vector2 object which is the result of the addition.
   */
   inline Vector2<TYPE_T> operator+( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] + operand, data_[1] + operand );
   }
   
   /** Subtraction operator: operand is a 2D vector.
   *
   *   \param operand   A 2D vector which shall be subtracted from the vector.
   *   \return          A Vector2 object which is the result of the subtraction.
   */
   inline Vector2<TYPE_T> operator-( const Vector2<TYPE_T> & operand ) const {
      return Vector2<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1] );
   }
   
   /** Subtraction operator: operand is a scalar.
   *
   *   \param operand   A scalar which shall be subtracted from the vector.
   *   \return          A Vector2 object which is the result of the subtraction.
   */
   inline Vector2<TYPE_T> operator-( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] - operand, data_[1] - operand );
   }
   
   /** Multiplication operator: operand is a scalar.
   *
   *   \param operand   A scalar with which the vector is to be multiplied.
   *   \return          A Vector2 object which is the result of the multiplication.
   */
   inline Vector2<TYPE_T> operator*( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] * operand, data_[1] * operand );
   }
   
   /** Multiplication operator: performs the outer product of 2-dimensional vectors. */
   template< typename T > friend Matrix2<T> operator*( const Vector2<T> &, const Vector2_t<T> & );
   
   /** Multiplication operator: performs the inner product (dot-product) of 2-dimensional vectors. */
   template< typename T > friend T Vector2_t<T>::operator*( const Vector2<T> & ) const;
   
   /** Division operator: operand is a scalar.
   *
   *   \param operand   The scalar value by which every element of the vector shall be divided.
   *   \return          A Vector2 object which is the result of the division.
   */
   inline Vector2<TYPE_T> operator/( const TYPE_T & operand ) const {

      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Vector2<TYPE_T>( data_[0] * inv, data_[1] * inv );
   }
   
   /** @} */
   
   /** \name Output
   *   @{
   */
   /** Output function which is compatible with the Logger. */
   template< typename T >
   friend Logger & operator<<( Logger & , const Vector2<T> & );
   /** @} */
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Implementation of output
//////////////////////////////

/** Every container in the simpleNewton framework is naturally compatible with the Logger class.
*
*   \param lg    An instance of Logger.
*   \param vec   The Vector2 object to be output.
*/
template< typename TYPE_T >
Logger & operator<<( Logger & lg, const Vector2<TYPE_T> & vec ) {

   lg.fixFP();
   lg << '\n' << "Vector2 (t)   [" << vec[0] << "   " << vec[1] << "]   " << '\n';
   lg.unfixFP();
   return lg;
}



//=== CLASS ================================================================================================================================

/** This class serves as a mathematical container which represents the transposed 2-dimensional vector.
*
*   \tparam TYPE_T   The underlying data type of the Vector2_t.
*/
//==========================================================================================================================================

template< class TYPE_T >
class Vector2_t : public FArray< TYPE_T, 2 > {

private:

   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 2>::data_;
   
private:
   /* LIC */ explicit Vector2_t( const TYPE_T & v1, const TYPE_T & v2 ) : FArray<TYPE_T, 2>() {

      data_[0] = v1;
      data_[1] = v2;
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2_t TC)" );
   }
public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Near-default copy constructor.
   *
   *   \param _ref   The reference Vector2_t object whose values are to be used for initialization.
   */
   Vector2_t( const Vector2_t<TYPE_T> & _ref ) : FArray<TYPE_T, 2>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2_t CC)" );
   }
   
   /** Near-default move constructor.
   *
   *   \param _ref   The reference Vector2_t object whose values are to be used for initialization.
   */
   Vector2_t( Vector2_t<TYPE_T> && _ref ) : FArray<TYPE_T, 2>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2" << " (from Vector2_t MC)" );
   }
   
   /** Near-default destructor */
   ~Vector2_t() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 2"
                                                        << " (from Vector2_t Destr.)" );
   }
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** User-defined conversion: a transposed vector can be turned into a non-transposed one.
   *
   *   \return   A Vector2 object which is in non-transposed form.
   */
   inline operator Vector2<TYPE_T>() const   { return Vector2<TYPE_T>( data_[0], data_[1] ); }
   
   /** @} */
   
   /** \name Arithmetic
   *   @{
   */
   /** Multiplication operator: dot-product of 2-dimensional vectors.
   *
   *   \param op   The operand, which is a 2-dimensional vector.
   *   \return     The dot-product in underlying field type.
   */
   inline TYPE_T operator*( const Vector2<TYPE_T> & op ) const {
      return ( data_[0] * op.data_[0] + data_[1] * op.data_[1] );
   }
   
   /** Multiplication operator: performs the multiplication of a transposed 2-dimensional vector and a 2x2 matrix. */
   template< typename T > friend Vector2_t<T> operator*( const Vector2_t<T> &, const Matrix2<T> & );
   
   /** @} */
   
   /** A function which returns a transposed form of a 2-dimensional vector. */
   friend Vector2_t<TYPE_T> Vector2<TYPE_T>::t() const;
};

}   // namespace simpleNewton

#endif
