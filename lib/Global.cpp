
#include <Global.hpp>

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
///   This file provides the implementation of the header, Global.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//=========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Global variables (mostly internal - non-client info)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace globalVariables {

/** The cardinality of the array of command line arguments. */
int argc = 0;

/** The array of command line arguments. */
char ** argv = nullptr;

}   // namespace globalVariables
#endif   // DOXYSKIP



void ExitProgram() {
   
   std::quick_exit( EXIT_FAILURE );
   
}

}   // namespace simpleNewton
