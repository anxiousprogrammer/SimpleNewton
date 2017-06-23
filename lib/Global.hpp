#ifndef SN_GLOBAL_HPP
#define SN_GLOBAL_HPP

#include <limits>
#include <cstdlib>

#include <Types.hpp>

//=========================================================================================================================================
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
///   This file provides essential, global support functions required by all modules of the framework.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//=========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Global constants
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** The space in which all constexpr and const global entities of the framework are accessible. */
namespace globalConstants {

/** A global, compile-time constant which stores the lowest floating point value which can be representable by the machine. */
constexpr real_t ZERO = std::numeric_limits< real_t >::epsilon();

}   // namespace globalConstants



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Global variables (declaration)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace globalVariables {

/** The cardinality of the array of command line arguments. */
extern int argc;

/** The array of command line arguments. */
extern char ** argv;

}   // namespace globalVariables
#endif   // DOXYSKIP



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Global functions (declarations)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** The standard, exceptional exit strategy to be used by the framework. This will be called by asserts as well. Warning! It is inadvisable 
*   to create too many potential exit points in a program.
*/
void ExitProgram();



}   // namespace simpleNewton

#endif   // header guard
