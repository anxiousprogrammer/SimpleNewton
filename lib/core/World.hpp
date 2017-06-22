#ifndef SN_WORLD_HPP
#define SN_WORLD_HPP

#include <algorithm>

#include <Types.hpp>
#include <types/Functor.hpp>
#include <BasicBases.hpp>
#include <GlobalConstants.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>

#include <core/Exceptions.hpp>

#include <containers/Vector3.hpp>

#include "kinematics/AllWKBBs.hpp"

#include <geometry/Object.hpp>

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

class World : private NonCopyable, private NonMovable {

   /* A friend indeed! */
   template< typename FP_T > friend class Simulator;

public:
   
   /** This typedef identifies the floating point precision being employed by the world. */
   using precType = real_t;
   
   World() = default;
   
private:

   Vector3< precType > domain_ = {};
   precType domain_offset_ = {};
   small_t parallel_dimension_ = -1;
};

}   // namespace simpleNewton
#endif
