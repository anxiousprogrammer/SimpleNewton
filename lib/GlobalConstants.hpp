#ifndef SN_GLOBALCONSTANTS_HPP
#define SN_GLOBALCONSTANTS_HPP

#include <limits>
#include <Types.hpp>

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
///   Contains the global constants which may be needed by multiple modules/headers in the framework.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {
namespace globalConstants {

/** A global, compile-time constant which stores the lowest floating point value which can be representable by the machine. */
constexpr real_t ZERO = std::numeric_limits< real_t >::epsilon();

}   // namespace globalConstants
}   // namespace simpleNewton

#endif
