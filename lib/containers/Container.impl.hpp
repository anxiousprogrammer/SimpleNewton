/**||***************************************************************************************************************************************
*
*   Description: Implementation of the base class of all fields and mathematical datatypes
*
|***************************************************************************************************************************************///+

namespace simpleNewton {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Constructors and destructor
/////////////////////////////////

// Non-trivial constructor(s)
template< class TYPE_T, small_t SIZE >
Container< TYPE_T, SIZE > :: Container( const TYPE_T & val ) {
   std::fill( data_, data_ + SIZE, val );
}



// Copy constructor
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> :: Container( const Container<TYPE_T, SIZE> & ref ) {
   std::copy( ref.data_, ref.data_ + SIZE, data_ );
   SN_LOG_MESSAGE( "Got to the very end of the CC" );
}



// Move constructor
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> :: Container( Container<TYPE_T, SIZE> && ref ) : data_( nullptr ) {
   SN_LOG_MESSAGE( "Got to the very beginning of the MC" );
   data_ = ref.data_;
   ref.data_ = nullptr;
   SN_LOG_MESSAGE( "Got to the very end of the MC" );
}



// Destructor
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> :: ~Container() {
   if( data_ != nullptr ) {
      delete[] data_;
   }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Copy and move control
///////////////////////////

// (Scalar) Copy control
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> & Container<TYPE_T, SIZE> :: operator=( const TYPE_T & ref ) {
   std::fill( data_, data_ + SIZE, ref );
   SN_LOG_MESSAGE( "Got to the very end of the CAO" );
   return *this;
}



// Copy control
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> & Container<TYPE_T, SIZE> :: operator=( const Container<TYPE_T, SIZE> & ref ) {
   std::copy( ref.data_, ref.data_ + SIZE, data_ );
   SN_LOG_MESSAGE( "Got to the very end of the CAO" );
   return *this;
}



// Move control
template< class TYPE_T, small_t SIZE >
Container<TYPE_T, SIZE> & Container<TYPE_T, SIZE> :: operator=( Container<TYPE_T, SIZE> && ref ) {
   if( this != &ref ) {
      delete[] data_;
      data_ = ref.data_;
      ref.data_ = nullptr;
      SN_LOG_MESSAGE( "Got to the very end of the MAO" );
   }
   return *this;
}

}   // namespace simpleNewton
