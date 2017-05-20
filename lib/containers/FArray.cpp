#include "FArray.hpp"

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
///   Contains the explicit instantiations of the class template FArray with every basic data type.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template class FArray< bool, 1000000 >;
template class FArray< char, 1000000 >;
template class FArray< unsigned char, 1000000 >;
template class FArray< short, 1000000 >;
template class FArray< unsigned short, 1000000 >;
template class FArray< int, 1000000 >;
template class FArray< unsigned int, 1000000 >;
template class FArray< long, 1000000 >;
template class FArray< unsigned long, 1000000 >;
template class FArray< long long, 1000000 >;
template class FArray< unsigned long long, 1000000 >;
template class FArray< float, 1000000 >;
template class FArray< double, 1000000 >;

}   // namespace simpleNewton
#endif
