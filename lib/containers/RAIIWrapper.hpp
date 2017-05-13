#ifndef RAIIWRAPPER_HPP
#define RAIIWRAPPER_HPP

#include <algorithm>
#include <utility>

#include <Types.hpp>
#include <BasicBases.hpp>
#include <asserts/Asserts.hpp>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: The base class of all RAII wrappers
*
|***************************************************************************************************************************************///+

template< class TYPE >
class RAIIWrapper : private NonCopyable {

public:

   /* The only way to create it */
   template< class CTYPE >
   friend RAIIWrapper<CTYPE> createRAIIWrapper( small_t, const CTYPE & );
   
   /* Pointer functionality */
   void free() {
      if( data_ != nullptr )
         delete[] data_;
   }

   /* Visible LCM */
   RAIIWrapper() = delete;
   RAIIWrapper( RAIIWrapper<TYPE> && donour ) {
      
      data_ = donour;
      donour.data_ = nullptr;
   }
   ~RAIIWrapper() {
      free();
   }
   
   /* Breach of encapsulation to make the wrapper function like a raw pointer */
   inline operator TYPE*()               { return data_; }
   inline operator const TYPE*() const   { return data_; }

   /* For template type deduction and situations where it's necessary */
   inline TYPE * raw_ptr()               { return data_; }
   inline const TYPE * raw_ptr() const   { return data_; }
   
   /* Move control */
   void operator=( RAIIWrapper<TYPE> && donour ) {
      
      free();
      data_ = donour;
      donour.data_ = nullptr;
   }
   
private:

   /* Direct initialization */
   explicit RAIIWrapper( TYPE * ptr ) {
      data_ = ptr;
   }
   
   /* Resource */
   TYPE * data_;
};



// The only way to create an instance of RAIIWrapper
template< class TYPE >
RAIIWrapper<TYPE> createRAIIWrapper( small_t size, const TYPE & val = TYPE() ) {

   SN_ASSERT_POSITIVE( size );
   RAIIWrapper<TYPE> new_packet( new TYPE[size] );
   
   // Initialization
   std::fill( new_packet.raw_ptr(), new_packet.raw_ptr() + size, val );
   
   return new_packet;
}

}   // namespace simpleNewton

#endif
