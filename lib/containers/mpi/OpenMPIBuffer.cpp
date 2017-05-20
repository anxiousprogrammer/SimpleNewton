#include "OpenMPIBuffer.hpp"

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
///   Contains the explicit instantiations of class template OpenMPIBuffer with all basic data types.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace simpleNewton {

template class OpenMPIBuffer< char >;
template class OpenMPIBuffer< unsigned char >;
template class OpenMPIBuffer< int >;
template class OpenMPIBuffer< unsigned int >;
template class OpenMPIBuffer< long >;
template class OpenMPIBuffer< unsigned long >;
template class OpenMPIBuffer< long long >;
template class OpenMPIBuffer< unsigned long long >;
template class OpenMPIBuffer< float >;
template class OpenMPIBuffer< double >;

}   // namespace simpleNewton
#endif
