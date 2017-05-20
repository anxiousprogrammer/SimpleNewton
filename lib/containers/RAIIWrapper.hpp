#ifndef SN_RAIIWRAPPER_HPP
#define SN_RAIIWRAPPER_HPP

#include <algorithm>
#include <utility>

#include <Types.hpp>
#include <BasicBases.hpp>
#include <asserts/Asserts.hpp>

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
///   Contains the class template RAIIWrapper, which is a dynamic, movable-only resource unit.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//=== CLASS ================================================================================================================================

/** This class is a dynamic, movable-only unit intended to be used as a basic resource manager. An instance of the class can only be 
*   created using the function, createRAIIWrapper.
*
*   \tparam TYPE_T   The underlying data type of the RAIIWrapper.
*/
//==========================================================================================================================================

template< class TYPE >
class RAIIWrapper : private NonCopyable {

public:

   /** \name Constructors and Destructor
   *  @{
   */
   /** Trivial constructor is deleted. */
   RAIIWrapper() = delete;
   
private:

   /** Direct initialization constructor which accepts freshly allocated resource.
   *
   *   \param ptr   A pointer to a newly allocated resource.
   */
   explicit RAIIWrapper( TYPE * ptr ) {
      data_ = ptr;
   }

public:

   /** Explicitly defined move constructor.
   *
   *   \param donour   The rvalue resource managing unit.
   */
   RAIIWrapper( RAIIWrapper<TYPE> && donour ) {
      
      data_ = donour;
      donour.data_ = nullptr;
   }

   /** Explicitly defined destructor. */
   ~RAIIWrapper() {
      free();
   }
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** User-defined conversion (non-const): allows breach of encapsulation to make the wrapper behave like a raw pointer.
   *
   *   \return   A raw pointer to the resource.
   */
   inline operator TYPE*()               { return data_; }
   
   /** User-defined conversion (const): allows breach of encapsulation to make the wrapper behave like a raw pointer.
   *
   *   \return   A const qualified raw pointer to the resource.
   */
   inline operator const TYPE*() const   { return data_; }

   /** A (non-const) function which allows breach of encapsulation to make the wrapper behave like a raw pointer.
   *
   *   \return   A raw pointer to the resource.
   */
   inline TYPE * raw_ptr()               { return data_; }
   
   /** A const qualified function which allows breach of encapsulation to make the wrapper behave like a raw pointer.
   *
   *   \return   A const qualified raw pointer to the resource.
   */
   inline const TYPE * raw_ptr() const   { return data_; }
   
   /** @} */
   
   /** A function to cautiously deallocate the resource. */
   void free() {
      if( data_ != nullptr )
         delete[] data_;
   }
   
   /** \name Assignment control
   *   @{
   */
   /**   Move assignment operator explicitly details a resource moving procedure.
   *
   *   \param donour   The resource managing unit, the management of whose resource is to be taken over.
   */
   void operator=( RAIIWrapper<TYPE> && donour ) {
      
      free();
      data_ = donour;
      donour.data_ = nullptr;
   }
   
   /** @} */
   
   /** A function which creates an instance of RAIIWrapper. */
   template< class CTYPE >
   friend RAIIWrapper<CTYPE> createRAIIWrapper( small_t, const CTYPE & );
   
private:
   
   /* Resource */
   TYPE * data_;   ///< The resource pointer.
};



/** This function performs resource allocation and directs the resource to a newly created RAIIWrapper.
*
*   \param size   The size of the resource.
*   \param val    The value with which the resource is to be initialised.
*   \return       An RAIIWrapper object which will be used to move initialise another.
*/
template< class TYPE >
RAIIWrapper<TYPE> createRAIIWrapper( small_t size, const TYPE & val = {} ) {

   SN_ASSERT_POSITIVE( size );
   RAIIWrapper<TYPE> new_packet( new TYPE[size] );
   
   // Initialization
   std::fill( new_packet.raw_ptr(), new_packet.raw_ptr() + size, val );
   
   return new_packet;
}

}   // namespace simpleNewton

#endif
