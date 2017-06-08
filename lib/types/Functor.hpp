#ifndef SN_FUNCTOR_HPP
#define SN_FUNCTOR_HPP

#include <types/Typelist.hpp>
#include <BasicBases.hpp>
#include <core/Exceptions.hpp>

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
///   Contains the class template Functor, which is the go-to function object class for the framework.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


/** This serves as the base class to all Functor classes and behaves accordingly. With the help of this class, arrays of functors with 
*   different target function signatures can be conceptualized.
*/
class BasicFunctor {

public:

   /** The main function, which renders callability to the class. */
   void operator()() {}
};



//===CLASS==================================================================================================================================

/** This class serves as the standard function object for the framework.
*
*   \tparam RET_TYPE   The return type of the target function.
*   \tparam PARAM      The parameter pack containing all the parameter types for the target function.
*/
//==========================================================================================================================================

template< class RET_TYPE, class... PARAM >
class Functor : public BasicFunctor {

public:

   /** This typedef describes the signature of the target function. */
   using function_type = RET_TYPE (*)( PARAM... );
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Direct initialization constructor.
   *
   *   \param _F   The pointer to target function or lambda expression.
   */
   Functor( function_type _F ) : func_ptr( _F ) {}
   
   /** Default copy constructor. */
   Functor( const Functor< RET_TYPE, PARAM... > & _ref ) = default;
   
   /** The destructor calls the member function reset. */
   ~Functor() { reset(); }
   
   /** @} */
   
   /** \name Primary functionality
   *   @{
   */
   /** Call operator: this calls the target function with certain arguments. Notes on exception safety: strong safety guaranteed. The 
   *   function throws an exception of type FunctorError if the target function is invalid/cannot be called.
   *
   *   \param args   Argument pack for the target function.
   *   \return       The return value of the target function.
   */
   inline RET_TYPE operator()( PARAM... args ) const {
      
      try {
         return func_ptr( args... ); 
      }
      catch( const std::bad_function_call & ex ) {
         SN_THROW_FUNCTOR_ERROR();
      }
   }
   
   /** @} */
   
   /** \name Utility
   *   @{
   */
   /** A function which resets the internal function pointer to nullptr. */
   inline void reset() { func_ptr = nullptr; }
   
   /** @} */

private:

   function_type func_ptr;
};

}   // namespace simpleNewton

#endif
