#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <Types.hpp>
#include <asserts/TypeConstraints.hpp>
#include <logger/Logger.hpp>

namespace simpleNewton {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   HACK: TEMPLATE/INLINE OR NO, WE WANT CPP!
///////////////////////////////////////////////
template< class T > struct Container_CPPHackClass {};

/**||***************************************************************************************************************************************
*
*   Description: The base class of all mathematical datatypes
*
|***************************************************************************************************************************************///+

template< typename TYPE_T, small_t SIZE >
class Container {
public:

   /* Constructors */
   Container( const TYPE_T & );
   Container( const Container<TYPE_T, SIZE> & );
   Container( Container<TYPE_T, SIZE> && );

   /* Copy and move control */
   Container<TYPE_T, SIZE> & operator=( const Container<TYPE_T, SIZE> & );
   Container<TYPE_T, SIZE> & operator=( Container<TYPE_T, SIZE> && );
   Container<TYPE_T, SIZE> & operator=( const TYPE_T & );
   
   /* Linear access */
   inline const TYPE_T & operator[]( small_t index );
   
   /* Mathematical operators which every datatype must possess */
   Container<TYPE_T, SIZE> && operator+( const Container<TYPE_T, SIZE> & ) const;
   Container<TYPE_T, SIZE> && operator-( const Container<TYPE_T, SIZE> & ) const;

   virtual Container<TYPE_T, SIZE> && operator*( const Container<TYPE_T, SIZE> & ) = 0;
   
   Container<TYPE_T, SIZE> && operator+( const TYPE_T & ) const;
   Container<TYPE_T, SIZE> && operator-( const TYPE_T & ) const;
   Container<TYPE_T, SIZE> && operator*( const TYPE_T & ) const;
   Container<TYPE_T, SIZE> && operator/( const TYPE_T & ) const;
   
private:
   
   /* Members */
   std::unique_ptr<TYPE_T> data_ = std::unique_ptr<TYPE_T>( new TYPE_T[SIZE] ) ;
};

}   // namespace simpleNewton

#include "Container.impl.hpp"
#endif
