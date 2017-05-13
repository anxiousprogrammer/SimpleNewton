#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <logger/Logger.hpp>
#include <types/DTInfo.hpp>
#include "FArray.hpp"

namespace simpleNewton {

// Forward declarations: Matrix and Vector2 transposed
template< class T > class Matrix3;
template< class T > class Vector3;
template< class T > class Vector3_t;

// Forward declarations: special product
template< typename T > Matrix3<T> operator*( const Vector3<T> &, const Vector3_t<T> & );   // outer product

/**||***************************************************************************************************************************************
*
*   Description: The 3D vector class
*
|***************************************************************************************************************************************///+


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Natural class for Vector2
///////////////////////////////

template< typename TYPE_T >
class Vector3 : public FArray< TYPE_T, 3 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 3>::data_;
   
public:
   
   /* Specifying creation and destruction */
   /* NTC */ explicit Vector3( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3 ) : FArray<TYPE_T, 3>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 TC)" );
   }
   /* CC1 */ Vector3( const Vector3<TYPE_T> & _ref ) : FArray<TYPE_T, 3>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 CC1)" );
   }
   /* CC2 */ Vector3( const Vector3_t<TYPE_T> & _ref ) : FArray<TYPE_T, 3>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 CC2)" );
   }
   /* MC1 */ Vector3( Vector3<TYPE_T> && _ref ) : FArray<TYPE_T, 3>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 MC1)" );
   }
   /* MC2 */ Vector3( Vector3_t<TYPE_T> && _ref ) : FArray<TYPE_T, 3>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 MC2)" );
   }
   ~Vector3() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3 Destr.)" );
   }
   
   /* Access */
   inline TYPE_T & operator()( small_t index )             { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   inline const TYPE_T & operator()( small_t index ) const { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   inline Vector3_t<TYPE_T> t() const                      { return Vector3_t<TYPE_T>( data_[0], data_[1], data_[2] );     }
   
   /* Arithmetic completion */
   inline Vector3<TYPE_T> operator+( const Vector3<TYPE_T> & operand ) const {
      return Vector3<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1], data_[2] + operand.data_[2] );
   }
   inline Vector3<TYPE_T> operator-( const Vector3<TYPE_T> & operand ) const {
      return Vector3<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1], data_[2] + operand.data_[2] );
   }
   /* Operations with scalars */
   inline Vector3<TYPE_T> operator+( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] + operand, data_[1] + operand, data_[2] + operand );
   }
   inline Vector3<TYPE_T> operator-( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] - operand, data_[1] - operand, data_[2] + operand );
   }
   inline Vector3<TYPE_T> operator*( const TYPE_T & operand ) const {
      return Vector3<TYPE_T>( data_[0] * operand, data_[1] * operand, data_[2] + operand );
   }
   inline Vector3<TYPE_T> operator/( const TYPE_T & operand ) const {
      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Vector3<TYPE_T>( data_[0] * inv, data_[1] * inv, data_[2] * inv );
   }
   
   /* Outer product */
   template< typename T > friend Matrix3<T> operator*( const Vector3<T> &, const Vector3_t<T> & );
   /* Dot product needs permission */
   template< typename T > friend T Vector3_t<T>::operator*( const Vector3<T> & ) const;
   
   /* Output */
   friend Logger & operator<<( Logger & lg, const Vector3<TYPE_T> & vec ) {
   
      lg.fixFP();
      lg << '\n' << "Vector3 (t)   [" << vec[0] << "   " << vec[1] << "   " << vec[2] << "]   " << '\n';
      lg.unfixFP();
      return lg;
   }
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Transpose class for Vector2
/////////////////////////////////

template< class TYPE_T >
class Vector3_t : public FArray< TYPE_T, 3 > {

private:
   
   /* Unveil the underlaying body of FArray */
   using FArray<TYPE_T, 3>::data_;
   
public:
   
   /* Creation of transpose Vector3 is only possible by t() function */
   friend Vector3_t<TYPE_T> Vector3<TYPE_T>::t() const;
   
private:
   
   /* Specifying creation and destruction */
   /* NTC */ explicit Vector3_t( const TYPE_T & v1, const TYPE_T & v2, const TYPE_T & v3 ) : FArray<TYPE_T, 3>() {
   
      data_[0] = v1;
      data_[1] = v2;
      data_[2] = v3;
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t TC)" );
   }
public:
   /* CC */ Vector3_t( const Vector3_t<TYPE_T> & _ref ) : FArray<TYPE_T, 3>(_ref) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t CC)" );
   }
   /* MC */ Vector3_t( Vector3_t<TYPE_T> && _ref ) : FArray<TYPE_T, 3>( std::move(_ref) ) {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResAlloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3" << " (from Vector3_t MC)" );
   }
   /* Mortality */ ~Vector3_t() {
      SN_LOG_REPORT_L1_EVENT( LogEventType::ResDealloc, "data_, " << types::DTInfo< TYPE_T >::name << ", 3"
                                                        << " (from Vector3_t Destr.)" );
   }

   /* V'M product */
   template< class T >
   friend Vector3_t<T> operator*( const Vector3_t<T> &, const Matrix3<T> & );
   
   
   /* Dot product */
   inline TYPE_T operator*( const Vector3<TYPE_T> & op ) const {
      return ( data_[0] * op.data_[0] + data_[1] * op.data_[1] + data_[2] * op.data_[2] );
   }
};


}   // namespace simpleNewton

#endif
