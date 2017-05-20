#include "DArray.hpp"

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
///   Contains the explicit instantiations of the class template DArray with every basic data type.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template class DArray< bool >;
template class DArray< char >;
template class DArray< unsigned char >;
template class DArray< short >;
template class DArray< unsigned short >;
template class DArray< int >;
template class DArray< unsigned int >;
template class DArray< long >;
template class DArray< unsigned long >;
template class DArray< long long >;
template class DArray< unsigned long long >;
template class DArray< float >;
template class DArray< double >;

}   // namespace simpleNewton
#endif
