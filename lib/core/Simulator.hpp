#ifndef SN_SIMULATOR_HPP
#define SN_SIMULATOR_HPP

#include <Types.hpp>
#include <BasicBases.hpp>
#include <GlobalConstants.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <logger/Logger.hpp>
#include <core/Exceptions.hpp>

#include <containers/Vector3.hpp>

#include <core/ProcSingleton.hpp>

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
///   Contains the non-instantiable class, Simulator which operates on all important objects to perform a simulation. In a way, this class 
///   is the super-friend of the framework.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template< typename FP_TYPE_T  >
class Simulator : private NonInstantiable {

   static void performTimeStep( small_t ts ) {
   
      
   }
   
public:

   /** This typedef identifies the floating point precision being employed for the simulation. */
   using precType = FP_TYPE_T;
   
   static setupDomains( Vector3<precType> && diag ) {
      
      // Check the argument for validity
      SN_ASSERT_POSITIVE( diag );
      
      #ifdef NDEBUG
      if( diag <= 0 )
         SN_THROW_INVALID_ARGUMENT( "IA_Domain_Diagonal_Error" )
      #endif
      
      small_t num_proc = SN_MPI_SIZE();
      small_t proc_rank = SN_MPI_RANK();
      
      if( num_proc > 1 ) {
      precType longest_dimension = diag.infinityNorm();
      
      if( std::fabs(diag.at(0) - longest_dimension) <= globalConstants::ZERO )
         ProcSingleton::getInstance().world_.parallel_dimension_ = 0;
      else if( std::fabs(diag.at(1) - longest_dimension) <= globalConstants::ZERO )
         ProcSingleton::getInstance().world_.parallel_dimension_ = 1;
      else if( std::fabs(diag.at(2) - longest_dimension) <= globalConstants::ZERO )
         ProcSingleton::getInstance().world_.parallel_dimension_ = 2;
      
      ProcSingleton::getInstance().world_.domain_ = std::move( diag );

      // Split up the parallel dimension into equal sized blocks -> worlds.
      precType block_side_length = longest_dimension / num_proc;
      ProcSingleton::getInstance().world_.domain_.at( ProcSingleton::getInstance().world_.parallel_dimension_ ) = block_side_length;

      ProcSingleton::getInstance().world_.domain_offset_ = proc_rank * block_side_length;
      
      // Paranoia! After all, that's what asserts are for!
      SN_ASSERT_INEQUAL( ProcSingleton::getInstance().parallel_dimension_, -1 );
      }
      else {
         ProcSingleton::getInstance().world_.domain_ = std::move( diag );
      }
      
      // Paranoia! After all, that's what asserts are for!
      SN_ASSERT_POSITIVE( ProcSingleton::getInstance().world_.domain_ );
   }
   
   static simulate( precType _totalTime, precType _max_resolution ) {
      
      small_t tsCount = small_cast( _totalTime / _max_resolution );
      
      for( small_t ts = 0; ts < tsCount; ++ts ) {
         
         performTimeStep( ts );
      }
   }
};

}   // namespace simpleNewton

#endif   // header guard
