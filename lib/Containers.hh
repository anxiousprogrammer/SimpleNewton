#ifndef CONTAINERS_HH
#define CONTAINERS_HH

//#include "Testing.hh"

namespace Testing {

//***************************************************************************************************
// Feeling pompous? Let's make some declarations.
template< typename TYPE_T > class Matrix3x3;
template< typename TYPE_T > class Matrix2x2;
//***************************************************************************************************




//***************************************************************************************************
/// Three dimensional vector class
//@{
template< class TYPE_T >
class Vector3{
public:
   Vector3( const TYPE_T & _v1=TYPE_T(), const TYPE_T & _v2=TYPE_T(), 
            const TYPE_T & _v3=TYPE_T() ) : data_{_v1, _v2, _v3}                                  {}
   Vector3( const Vector3<TYPE_T> & _ref ) : data_{_ref.data_[0], _ref.data_[1], _ref.data_[2]}   {}
   ~Vector3()                                                                                     {}
   
   // Access
   inline TYPE_T & operator()( std::size_t _index )               { return data_[ _index ]; }
   inline const TYPE_T & operator()( std::size_t _index ) const   { return data_[ _index ]; }
   
   // Arithmetic
   /*(FL)OP count: 2A, 3M*/
   inline TYPE_T dot( const Vector3<TYPE_T> & _op ) const
   { return (data_[0]*_op.data_[0] + data_[1]*_op.data_[1] + data_[2]*_op.data_[2]); }

   /*(FL)OP count: 3A*/
   inline Vector3<TYPE_T> operator+( const Vector3<TYPE_T> & _op ) const { 
      return Vector3<TYPE_T>(data_[0] + _op.data_[0], data_[1] 
                           + _op.data_[1], data_[2] + _op.data_[2]); 
   }
   
   /*(FL)OP count: 3A*/
   inline Vector3<TYPE_T> operator-( const Vector3<TYPE_T> & _op ) const { 
      return Vector3<TYPE_T>(data_[0] - _op.data_[0], data_[1] 
                           - _op.data_[1], data_[2] - _op.data_[2]); 
   }
   
   /*(FL)OP count: 6A, 9M*/
   inline Vector3<TYPE_T> operator*( const Matrix3x3<TYPE_T> & _op ) const {
      return Vector3<TYPE_T>( data_[0]*_op(0,0) + data_[1]*_op(1,0) + data_[2]*_op(2,0),
                              data_[0]*_op(0,1) + data_[1]*_op(1,1) + data_[2]*_op(2,1),
                              data_[0]*_op(0,2) + data_[1]*_op(1,2) + data_[2]*_op(2,2) );
   }
   
   /*(FL)OP count: 2A, 3M*/
   inline TYPE_T operator*( const Vector3<TYPE_T> & _op ) const { 
      return (data_[0]*_op.data_[0] + data_[1]*_op.data_[1] + data_[2]*_op.data_[2]);
   }
   
   /*(FL)OP count: 3M*/
   inline Vector3<TYPE_T> operator*( const TYPE_T & _scalar ) const { 
      return Vector3<TYPE_T>(data_[0]*_scalar, data_[1]*_scalar, data_[2]*_scalar);
   }
   
   // Measure. (FL)OP count: 2A, 3M, 1SQRT
   inline TYPE_T L2Norm() const   { return std::sqrt( data_[0]*data_[0] + data_[1]*data_[1] +
                                                      data_[2]*data_[2] ); }
   
   // Output
   template< typename TYPE >
   friend std::ostream & operator<<( std::ostream & os, const Vector3<TYPE> & _v ) {
      os << "The output of a Vector3 was required." << std::endl;
      os << "[ " << _v(0) << "   " << _v(1) << "   " << _v(2) << " ]" << std::endl;
      return os;
   }

private:
   TYPE_T data_[3];
};
//}@
//***************************************************************************************************
typedef Vector3<real> Vec3;




//***************************************************************************************************
/// Three dimensional vector class
//@{
template< class TYPE_T >
class Vector2{
public:
   Vector2( const TYPE_T & _v1=TYPE_T(), const TYPE_T & _v2=TYPE_T() ) : data_{_v1, _v2}   {}
   Vector2( const Vector2<TYPE_T> & _ref ) : data_{_ref.data_[0], _ref.data_[1]}           {}
   ~Vector2()                                                                              {}
   
   // Access
   inline TYPE_T & operator()( std::size_t _index )               { return data_[ _index ]; }
   inline const TYPE_T & operator()( std::size_t _index ) const   { return data_[ _index ]; }
   
   // Arithmetic
   /*(FL)OP count: 1A, 2M*/
   inline TYPE_T dot( const Vector2<TYPE_T> & _op ) const
   { return (data_[0]*_op.data_[0] + data_[1]*_op.data_[1]); }
   
   /*(FL)OP count: 2A*/
   inline Vector2<TYPE_T> operator+( const Vector2<TYPE_T> & _op ) const { 
      return Vector2<TYPE_T>(data_[0] + _op.data_[0], data_[1] + _op.data_[1]); 
   }
   
   /*(FL)OP count: 2A*/
   inline Vector2<TYPE_T> operator-( const Vector2<TYPE_T> & _op ) const { 
      return Vector2<TYPE_T>(data_[0] - _op.data_[0], data_[1] - _op.data_[1]); 
   }
   
   /*(FL)OP count: 2A, 4M*/
   inline Vector2<TYPE_T> operator*( const Matrix2x2<TYPE_T> & _op ) const {
      return Vector2<TYPE_T>( data_[0]*_op(0,0) + data_[1]*_op(1,0),
                              data_[0]*_op(0,1) + data_[1]*_op(1,1) );
   }
   
   /*(FL)OP count: 1A, 2M*/
   inline TYPE_T operator*( const Vector2<TYPE_T> & _op ) const { 
      return (data_[0]*_op.data_[0] + data_[1]*_op.data_[1]);
   }
   
   /*(FL)OP count: 2M*/
   inline Vector2<TYPE_T> operator*( const TYPE_T & _scalar ) const { 
      return Vector2<TYPE_T>(data_[0]*_scalar, data_[1]*_scalar);
   }

   /*(FL)OP count: 4M*/
   inline Matrix2x2<TYPE_T> outerProduct( const Vector2<TYPE_T> & _op ) const {
      return Matrix2x2<TYPE_T>( data_[0]*_op.data_[0], data_[0]*_op.data_[1],
                                data_[1]*_op.data_[0], data_[1]*_op.data_[1] );
   }
   
   // Measure. (FL)OP count: 1A, 2M, 1SQRT
   inline TYPE_T L2Norm() const   { return std::sqrt( data_[0]*data_[0] + data_[1]*data_[1] ); }
   
   // Output
   template< typename TYPE >
   friend std::ostream & operator<<( std::ostream & os, const Vector2<TYPE> & _v ) {
      os << "The output of a Vector2 was required." << std::endl;
      os << "[ " << _v(0) << "   " << _v(1) << " ]" << std::endl;
      return os;
   }

private:
   TYPE_T data_[2];
};
//}@
//***************************************************************************************************
typedef Vector2<real> Vec2;




//***************************************************************************************************
/// 3x3 square matrix class
//@{
template< class TYPE_T >
class Matrix3x3{
public:
   Matrix3x3( const TYPE_T & _v1=TYPE_T(1.0), const TYPE_T & _v2=TYPE_T(0.0), 
              const TYPE_T & _v3=TYPE_T(0.0), const TYPE_T & _v4=TYPE_T(0.0), 
              const TYPE_T & _v5=TYPE_T(1.0), const TYPE_T & _v6=TYPE_T(0.0), 
              const TYPE_T & _v7=TYPE_T(0.0), const TYPE_T & _v8=TYPE_T(0.0), 
              const TYPE_T & _v9=TYPE_T(1.0) ) 
              : data_{_v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9}                                 {}
   Matrix3x3( const Matrix3x3<TYPE_T> & _ref ) : data_{_ref.data_[0], _ref.data_[1], _ref.data_[2],
                                                       _ref.data_[3], _ref.data_[4], _ref.data_[5],
                                                       _ref.data_[6], _ref.data_[7], _ref.data_[8]}{}
   ~Matrix3x3()                                                                                    {}
   
   // Getty
   TYPE_T infinityNorm() {
      TYPE_T Largest = data_[0];
      for( unsigned int i=1; i<9; ++i ) {
         if( std::fabs( data_[i] ) >= Largest ) Largest = std::fabs( data_[i] );
      }
      return Largest;
   }
   inline TYPE_T & operator()( std::size_t i, std::size_t j )
   { return data_[ 3*i + j ]; }
   inline const TYPE_T & operator()( std::size_t i, std::size_t j ) const
   { return data_[ 3*i + j ]; }
   Matrix3x3<TYPE_T> transpose() const {
      return Matrix3x3<TYPE_T>( data_[0], data_[3], data_[6], data_[1], data_[4], data_[7],
                                data_[2], data_[5], data_[8] );
   }
   
   // O-loaded ops
   /*(FL)OP count: 9A*/
   Matrix3x3<TYPE_T> operator+( const Matrix3x3<TYPE_T> & _op ) const { 
      return Matrix3x3<TYPE_T>( data_[0] + _op.data_[0], data_[1] + _op.data_[1], 
                                data_[2] + _op.data_[2], data_[3] + _op.data_[3],
                                data_[4] + _op.data_[4], data_[5] + _op.data_[5], 
                                data_[6] + _op.data_[6], data_[7] + _op.data_[7],
                                data_[8] + _op.data_[8] ); 
   }
   
   /*(FL)OP count: 9A*/
   Matrix3x3<TYPE_T> operator-( const Matrix3x3<TYPE_T> & _op ) const { 
      return Matrix3x3<TYPE_T>( data_[0] - _op.data_[0], data_[1] - _op.data_[1], 
                                data_[2] - _op.data_[2], data_[3] - _op.data_[3],
                                data_[4] - _op.data_[4], data_[5] - _op.data_[5], 
                                data_[6] - _op.data_[6], data_[7] - _op.data_[7],
                                data_[8] - _op.data_[8] ); 
   }
   
   /*(FL)OP count: 18A, 27M*/
   Matrix3x3<TYPE_T> operator*( const Matrix3x3<TYPE_T> & _op ) const { 
      return Matrix3x3<TYPE_T>
             ( data_[0]*_op.data_[0] + data_[1]*_op.data_[3] + data_[2]*_op.data_[6],
               data_[0]*_op.data_[1] + data_[1]*_op.data_[4] + data_[2]*_op.data_[7],
               data_[0]*_op.data_[2] + data_[1]*_op.data_[5] + data_[2]*_op.data_[8],
               data_[3]*_op.data_[0] + data_[4]*_op.data_[3] + data_[5]*_op.data_[6],
               data_[3]*_op.data_[1] + data_[4]*_op.data_[4] + data_[5]*_op.data_[7],
               data_[3]*_op.data_[2] + data_[4]*_op.data_[5] + data_[5]*_op.data_[8],
               data_[6]*_op.data_[0] + data_[7]*_op.data_[3] + data_[8]*_op.data_[6],
               data_[6]*_op.data_[1] + data_[7]*_op.data_[4] + data_[8]*_op.data_[7],
               data_[6]*_op.data_[2] + data_[7]*_op.data_[5] + data_[8]*_op.data_[8] );
   }
   
   /*(FL)OP count: 6A, 9M*/
   Vector3<TYPE_T> operator*( const Vector3<TYPE_T> & _op ) const {
      return Vector3<TYPE_T>
             ( data_[0]*_op(0) + data_[1]*_op(1) + data_[2]*_op(2),
               data_[3]*_op(0) + data_[4]*_op(1) + data_[5]*_op(2),
               data_[6]*_op(0) + data_[7]*_op(1) + data_[8]*_op(2) );
   }
   
   /*(FL)OP count: 9M*/
   Matrix3x3<TYPE_T> operator*( const TYPE_T & _scalar ) const {
      return Matrix3x3<TYPE_T>( data_[0]*_scalar, data_[1]*_scalar, data_[2]*_scalar, 
                                data_[3]*_scalar, data_[4]*_scalar, data_[5]*_scalar, 
                                data_[6]*_scalar, data_[7]*_scalar, data_[8]*_scalar );
   }
   
   // Utility
   void print() const {
      for( std::size_t i=0; i<3; ++i ) {
         for( std::size_t j=0; j<3; ++j ) {
            std::cout << data_[3*i+j] << " " << std::ends;
         }
         std::cout << std::endl;
      }
   }
   template< typename TYPE >
   friend std::ostream & operator<<( std::ostream & os, const Matrix3x3<TYPE> & _M ) {
      os << "The output of a Matrix3x3 was required." << std::endl;
      os << _M(0,0) << "   " << _M(0,1) << "   " << _M(0,2) << std::endl;
      os << _M(1,0) << "   " << _M(1,1) << "   " << _M(1,2) << std::endl;
      os << _M(2,0) << "   " << _M(2,1) << "   " << _M(2,2) << std::endl;
      return os;
   }

private:
   TYPE_T data_[9];
};
//}@
//***************************************************************************************************
typedef Matrix3x3<real> M33;




//***************************************************************************************************
/// 2x2 square matrix class
//@{
template< class TYPE_T >
class Matrix2x2{
public:
   Matrix2x2( const TYPE_T & _v1=TYPE_T(1.0), const TYPE_T & _v2=TYPE_T(0.0), 
              const TYPE_T & _v3=TYPE_T(0.0), const TYPE_T & _v4=TYPE_T(1.0) ) 
              : data_{_v1, _v2, _v3, _v4}                                 {}
   Matrix2x2( const Matrix2x2<TYPE_T> & _ref ) : data_{_ref.data_[0], _ref.data_[1], 
                                                       _ref.data_[2], _ref.data_[3]}               {}
   ~Matrix2x2()                                                                                    {}
   
   // Getty
   inline TYPE_T & operator()( std::size_t i, std::size_t j )
   { return data_[ 2*i + j ]; }
   inline const TYPE_T & operator()( std::size_t i, std::size_t j ) const
   { return data_[ 2*i + j ]; }
   Matrix2x2<TYPE_T> transpose() const {
      return Matrix2x2<TYPE_T>( data_[0], data_[2], data_[1], data_[3] );
   }
   /*(FL)OP count: 1A, 2M*/
   TYPE_T infinityNorm() {
      TYPE_T Largest = data_[0];
      for( unsigned int i=1; i<4; ++i ) {
         if( std::fabs( data_[i] ) >= Largest ) Largest = std::fabs( data_[i] );
      }
      return Largest;
   }
   inline TYPE_T determinant() const   { return data_[0]*data_[3] - data_[1]*data_[2]; }
   /*(FL)OP count: 1A, 6M, 1DIV*/
   inline Matrix2x2<TYPE_T> getInverse() const {
      TYPE_T inv_det = TYPE_T(1.0)/(data_[0]*data_[3] - data_[1]*data_[2]);
      return Matrix2x2<TYPE_T>( data_[3]*inv_det, -data_[1]*inv_det, 
                               -data_[2]*inv_det,  data_[0]*inv_det );
   }
   
   // O-loaded ops
   /*(FL)OP count: 4A*/
   Matrix2x2<TYPE_T> operator+( const Matrix2x2<TYPE_T> & _op ) const { 
      return Matrix2x2<TYPE_T>( data_[0] + _op.data_[0], data_[1] + _op.data_[1], 
                                data_[2] + _op.data_[2], data_[3] + _op.data_[3] ); 
   }
   /*(FL)OP count: 4A*/
   Matrix2x2<TYPE_T> operator-( const Matrix2x2<TYPE_T> & _op ) const { 
      return Matrix2x2<TYPE_T>( data_[0] - _op.data_[0], data_[1] - _op.data_[1], 
                                data_[2] - _op.data_[2], data_[3] - _op.data_[3] ); 
   }
   /*(FL)OP count: 4A, 8M*/
   Matrix2x2<TYPE_T> operator*( const Matrix2x2<TYPE_T> & _op ) const { 
      return Matrix2x2<TYPE_T>( data_[0]*_op.data_[0] + data_[1]*_op.data_[2],
                                data_[0]*_op.data_[1] + data_[1]*_op.data_[3],
                                data_[2]*_op.data_[0] + data_[3]*_op.data_[2],
                                data_[2]*_op.data_[1] + data_[3]*_op.data_[3] );
   }
   /*(FL)OP count: 2A, 4M*/
   Vector2<TYPE_T> operator*( const Vector2<TYPE_T> & _op ) const {
      return Vector2<TYPE_T>( data_[0]*_op(0) + data_[1]*_op(1),
                              data_[2]*_op(0) + data_[3]*_op(1) );
   }
   /*(FL)OP count: 4M*/
   Matrix2x2<TYPE_T> operator*( const TYPE_T & _scalar ) const {
      return Matrix2x2<TYPE_T>( data_[0]*_scalar, data_[1]*_scalar,
                                data_[2]*_scalar, data_[3]*_scalar );
   }
   
   // Utility
   void print() const {
      std::cout << std::endl;
      std::cout << data_[0] << " " << data_[1] << std::endl;
      std::cout << data_[2] << " " << data_[3] << std::endl;
   }
   template< typename TYPE >
   friend std::ostream & operator<<( std::ostream & os, const Matrix2x2<TYPE> & _M ) {
      os << "The output of a Matrix2x2 was required." << std::endl;
      os << _M(0,0) << "   " << _M(0,1) << std::endl;
      os << _M(1,0) << "   " << _M(1,1) << std::endl;
      return os;
   }

private:
   TYPE_T data_[4];
};
//}@
//***************************************************************************************************
typedef Matrix2x2<real> M22;

}
#endif
