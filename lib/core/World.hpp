#ifndef SN_WORLD_HPP
#define SN_WORLD_HPP

#include <algorithm>
#include <vector>

#include <Types.hpp>
#include <types/Functor.hpp>
#include <BasicBases.hpp>
#include <GlobalConstants.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <logger/Logger.hpp>
#include <core/Exceptions.hpp>

#include <containers/Field.hpp>
#include "math/KinematicIntegrator.hpp"

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
///   Contains the class World
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

class Object;
class KinematicIntegrator;

namespace world {
namespace internal {

template< class OBJ_T >
class ObjectFactory {

public:
   
   template< class... PARAM > void createObject( PARAM... Args ) {
      
      SN_CT_REQUIRE_DERIVED_FROM< OBJ_T, Object >();
      SN_CT_REQUIRE_CONSTRUCTIBLE_TYPE< OBJ_T, PARAM... >();
      
      try {
         container_.push_back( OBJ_T(Args...) );
      }
      catch( const std::bad_alloc & ) {
         SN_THROW_ALLOC_ERROR();
      }
   }

private:

   Field< OBJ_T > container_;
};

template< class... OBJ_TYPES > class World {};
template< class HD, class... TAIL > class World< HD, TAIL... > : public ObjectFactory< HD >, World< TAIL... > {};

}   // namespace internal
}   // namespace world

template< typename TYPE_T, class... OBJ_TYPES >
class World : private NonCopyable, public world::internal::World< OBJ_TYPES... > {

   World() = default;

public:

   using objectTypelist = SN_CT_TYPELIST< OBJ_TYPES... >;
   
   World( World && ) = default;
   
   void registerKinematicFunction( const Functor< void, World* > & new_kf ) {
      kif_ = new_kf;
   }
   
   void addTStepFunction( const Functor<void, World*> & new_func ) {
      
      try {
         stepFunctions_.push_back( new_func );
      }
      catch( const std::bad_alloc & ) {
         SN_THROW_ALLOC_ERROR();
      }
   }
   
   void doStep( TYPE_T time_step ) {

      SN_ASSERT_POSITIVE( time_step );
      
      #ifdef NDEBUG
      if( time_step <= globalConstants::ZERO ) {
         SN_THROW_INVALID_ARGUMENT( "IA_Time_Step_Error" );
      }
      #endif
      
      simTime_ += time_step;
   }

private:

   Functor< void, World* > kif_;
   std::vector< Functor< void, World * > > stepFunctions_;
   
   TYPE_T simTime_ = {};
   TYPE_T endTime_ = {};
   uint_t stepCount_ = {};
};

}   // namespace simpleNewton
#endif
