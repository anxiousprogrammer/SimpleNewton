#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <algorithm>
#include <utility>

#include <asserts/Asserts.hpp>
#include <logger/Logger.hpp>
#include <asserts/TypeConstraints.hpp>

#include <core/ULoops.hpp>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: The base classes of all fields and mathematical datatypes
*
|***************************************************************************************************************************************///+

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Basic container: can be large, small - whatever.
//////////////////////////////////////////////////////

template< typename TYPE_T, small_t SIZE >
class Container {

public:

   /* Copy and move control */
   Container<TYPE_T, SIZE> & operator=( const TYPE_T & );
   Container<TYPE_T, SIZE> & operator=( const Container<TYPE_T, SIZE> & );
   Container<TYPE_T, SIZE> & operator=( Container<TYPE_T, SIZE> && );
   
   /* Linear access */
   inline const TYPE_T & operator[]( small_t index ) const   { SN_ASSERT_INDEX_WITHIN_SIZE( index, SIZE ); return data_[index]; }
   
protected:

   /* Birth and death */
   Container() = default;
   explicit Container( const TYPE_T & );

   Container( const Container<TYPE_T, SIZE> & );
   Container( Container<TYPE_T, SIZE> && );
   ~Container();
   
   /* Members */
   TYPE_T* data_ = new TYPE_T[SIZE];
};

}   // namespace simpleNewton

#include "Container.impl.hpp"
#endif
