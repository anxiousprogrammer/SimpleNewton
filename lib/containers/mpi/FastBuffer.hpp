#ifndef SN_FASTBUFFER_HPP
#define SN_FASTBUFFER_HPP

#include <logger/Logger.hpp>
#include <containers/DArray.hpp>

#include <BasicBases.hpp>

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
///   Contains the class template FastBuffer, which is a container meant to be used for quick transfers.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Forward declarations.
template< typename TYPE_T > class BaseComm;
#endif

//===CLASS==================================================================================================================================

/** This container serves as a move-only buffer for quick transfers between loopers, MPI functions and others. It is highly recommended 
*   that the data be moved out of the buffer immediately after use. 
*
*   \tparam TYPE_T   The data type of the resource
*/
//==========================================================================================================================================

template< typename TYPE_T >
class FastBuffer : private NonCopyable, public DArray<TYPE_T> {

private:
   
   /* Ancestral visibility */
   using DArray<TYPE_T>::data_;
   using DArray<TYPE_T>::size_;
   
   /* Length of a literal */
   small_t cptr_length( const TYPE_T * ptr ) {
   
      small_t size = 0;
      while( ptr[size] != TYPE_T() )
         size++;
      return size;
   }
   
public:
   
   /** \name Constructors and Destructors
   * @{
   */
   /** Direct initialization constructor: copies directly from a literal.
   *
   *   \param arr   The literal from which the direct initialization (by copy) takes place.
   */
   FastBuffer( const TYPE_T * arr ) : DArray<TYPE_T>( cptr_length( arr ) ) {
      std::copy( arr, arr + size_, data_.raw_ptr() );
   }

   /** Direct initialization constructor: size and reference value fill.
   *
   *   \param size   The desired size of the FastBuffer object upon construction.
   *   \param val    The value with which the contents of the FastBuffer need to be initialized. 
   */
   FastBuffer( small_t size, const TYPE_T & val = {} ) : DArray<TYPE_T>( size, val ) {}
   
   /** Default move constructor. */
   FastBuffer( FastBuffer<TYPE_T> && ) = default;

   /** Default destructor. */
   ~FastBuffer() = default;
   
   /** @} */
   
   /** \name Assignment control
   *   @{
   */
   /** Assignment is possible as one-time move only. */
   void operator=( FastBuffer<TYPE_T> && src ) {
      DArray<TYPE_T>::operator=(src);
   }
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** Operator (const): primary access function. Notes on exception safety: strong safety guaranteed. The function throws an OORError
   *   exception if the provided index is invalid.
   *
   *   \param index   The index used to access the corresponding element.
   *   \return        A const reference to the element required to be accessed.
   */
   inline const TYPE_T & operator[]( large_t index ) const {
      
      #ifdef NDEBUG
      if( index >= size_ )
         SN_THROW_OOR_ERROR();
      #endif
      
      return DArray<TYPE_T>::operator[]( index );
   }
   
   /** @} */
   
   /** \name Utility
   *   @{
   */
   
   /** Function to concatenate buffers of the same type.
   *
   *   \param operand   The FastBuffer object which has to be appended.
   *   \return          The concatenated FastBuffer object. 
   */
   FastBuffer<TYPE_T> operator+( const FastBuffer<TYPE_T> & operand ) {
   
      FastBuffer<TYPE_T> newOMPIB( size_ + operand.size_ );

      std::copy( data_.raw_ptr(), data_.raw_ptr() + size_, newOMPIB.data_.raw_ptr() );
      std::copy( operand.data_.raw_ptr(), operand.data_.raw_ptr() + operand.size_, newOMPIB.data_.raw_ptr() + size_ );
   
      return newOMPIB;
   }
   
   /** @} */
   
   /** \name Output
   *   @{
   */
   /** Output function which is compatible with the Logger. */
   template< typename T >
   friend Logger & operator<<( Logger & , const FastBuffer<T> & );
   
   /** @} */
   
   /* BaseComm can get in here */
   template< typename TYPE > friend class BaseComm; 
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   FRIENDS AND EXTERNAL UTILITIES
///////////////////////////////////

/** A friend operator of FastBuffer which transfers data from the buffer to a Logger instance element-wise. Warning: this is not very 
*   performance optimized.
*
*   \tparam T     The basic data type of the FastBuffer.
*   \param lg     A Logger instance.
*   \param buff   The buffer from which the data has to be transferred to the Logger instance lg.
*   \return       The Logger instance.
*/
template< typename T >
Logger & operator<<( Logger & lg, const FastBuffer<T> & buff ) {
   
   for( uint_t i=0; i<buff.size_; ++i )
      lg <<  buff.data_[i];
   return lg;
}



/** A function which creates a std::string object with the data contained in an FastBuffer<char> object.
*
*   \param buff   The buffer from which the data has to be copied into the std::string
*   \return       A std::string object with the contents of buff.
*/
std::string make_std_string( const FastBuffer< char > & buff ) { 

   std::string str;
   
   try {
      str.append( &buff[0], buff.getSize() );
   }
   catch( const std::bad_alloc & ex ) {
      SN_THROW_ALLOC_ERROR();
   }
   
   return str;
}

}   // namespace simpleNewton

#endif
