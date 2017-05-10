#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <logger/Logger.hpp>
#include <logger/BasicTypenameStr.hpp>
#include "Container.hpp"

namespace simpleNewton {

// Forward declarations: Matrix and Vector2 transposed
template< class T > class Matrix2;
template< class T > class Vector2;
template< class T > class Vector2_t;

// Forward declarations: Interactions with objects of other mathematical types
template< typename T > Matrix2<T> operator*( const Vector2<T> &, const Vector2_t<T> & );     // Outer product

/**||***************************************************************************************************************************************
*
*   Description: The 2D vector class
*
|***************************************************************************************************************************************///+


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Natural class for Vector2
///////////////////////////////

template< typename TYPE_T >
class Vector2 : public Container< TYPE_T, 2 > {

private:
   
   /* Unveil the underlaying body of container */
   using Container<TYPE_T, 2>::data_;
   
public:
   
   /* Specifying creation and destruction */
   /* NTC */ explicit Vector2( const TYPE_T & v1, const TYPE_T & v2 ) : Container<TYPE_T, 2>() {

      data_[0] = v1;
      data_[1] = v2;
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 TC)" );
   }
   /* CC */ Vector2( const Vector2<TYPE_T> & _ref ) : Container<TYPE_T, 2>(_ref) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 CC1)" );
   }
   /* CC */ Vector2( const Vector2_t<TYPE_T> & _ref ) : Container<TYPE_T, 2>(_ref) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 CC2)" );
   }
   /* MC1 */ Vector2( Vector2<TYPE_T> && _ref ) : Container<TYPE_T, 2>( std::move(_ref) ) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 MC1)" );
   }
   /* MC2 */ Vector2( Vector2_t<TYPE_T> && _ref ) : Container<TYPE_T, 2>( std::move(_ref) ) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 MC2)" );
   }
   ~Vector2() {
      SN_LOG_REPORT_EVENT( LogEventType::ResDealloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2 Destr.)" );
   }
   
   /* Access */
   inline TYPE_T & operator()( small_t index )             { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   inline const TYPE_T & operator()( small_t index ) const { SN_ASSERT_INDEX_WITHIN_SIZE( index, 2 ); return data_[index]; }
   inline Vector2_t<TYPE_T> t() const                      { return Vector2_t<TYPE_T>( data_[0], data_[1] ); }
   
   /* Arithmetic completion */
   inline Vector2<TYPE_T> operator+( const Vector2<TYPE_T> & operand ) const {
      return Vector2<TYPE_T>( data_[0] + operand.data_[0], data_[1] + operand.data_[1] );
   }
   inline Vector2<TYPE_T> operator-( const Vector2<TYPE_T> & operand ) const {
      return Vector2<TYPE_T>( data_[0] - operand.data_[0], data_[1] - operand.data_[1] );
   }
   /* Operations with scalars */
   inline Vector2<TYPE_T> operator+( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] + operand, data_[1] + operand );
   }
   inline Vector2<TYPE_T> operator-( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] - operand, data_[1] - operand );
   }
   inline Vector2<TYPE_T> operator*( const TYPE_T & operand ) const {
      return Vector2<TYPE_T>( data_[0] * operand, data_[1] * operand );
   }
   inline Vector2<TYPE_T> operator/( const TYPE_T & operand ) const {

      TYPE_T inv = static_cast<TYPE_T>(1.0)/operand;
      return Vector2<TYPE_T>( data_[0] * inv, data_[1] * inv );
   }
   
   /* Outer product */
   template< typename T > friend Matrix2<T> operator*( const Vector2<T> &, const Vector2_t<T> & );
   /* Dot product needs permission */
   template< typename T > friend T Vector2_t<T>::operator*( const Vector2<T> & ) const;
   
   /* Output */
   friend Logger & operator<<( Logger & lg, const Vector2<TYPE_T> & vec ) {

      lg.fixFP();
      lg << '\n' << "Vector2 (t)   [" << vec[0] << "   " << vec[1] << "]   " << '\n';
      lg.unfixFP();
      return lg;
   }
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Transpose class for Vector2
/////////////////////////////////

template< class TYPE_T >
class Vector2_t : public Container< TYPE_T, 2 > {

private:

   /* Unveil the underlaying body of container */
   using Container<TYPE_T, 2>::data_;
   
public:
   
   /* The only way to ever create a transpose */
   friend Vector2_t<TYPE_T> Vector2<TYPE_T>::t() const;
   
   /* Specifying creation and destruction */
private:
   /* NTC */ explicit Vector2_t( const TYPE_T & v1, const TYPE_T & v2 ) : Container<TYPE_T, 2>() {

      data_[0] = v1;
      data_[1] = v2;
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2_t TC)" );
   }
public:
   /* CC */ Vector2_t( const Vector2_t<TYPE_T> & _ref ) : Container<TYPE_T, 2>(_ref) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2_t CC)" );
   }
   /* MC */ Vector2_t( Vector2_t<TYPE_T> && _ref ) : Container<TYPE_T, 2>( std::move(_ref) ) {
      SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2_t MC)" );
   }
   /* Mortality */ ~Vector2_t() {
      SN_LOG_REPORT_EVENT( LogEventType::ResDealloc, "data_, " + SN_BASIC_TYPENAME_STR<TYPE_T>() + ", 2" + " (from Vector2_t Destr.)" );
   }
   
   /* 2*2x2 V'M product */
   template< typename T >
   friend Vector2_t<T> operator*( const Vector2_t<T> &, const Matrix2<T> & );
   
   /* Dot product */
   inline TYPE_T operator*( const Vector2<TYPE_T> & op ) const {
      return ( data_[0] * op.data_[0] + data_[1] * op.data_[1] );
   }
};

}   // namespace simpleNewton

#endif
