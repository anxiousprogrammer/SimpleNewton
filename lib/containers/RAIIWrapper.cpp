#include "RAIIWrapper.hpp"

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
///   Contains the explicit instantiations of class template RAIIWrapper with all basic data types.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

template class RAIIWrapper< char >;
template class RAIIWrapper< unsigned char >;
template class RAIIWrapper< real_t >;
template class RAIIWrapper< single_t >;
template class RAIIWrapper< int >;
template class RAIIWrapper< unsigned int >;
template class RAIIWrapper< short >;
template class RAIIWrapper< unsigned short >;
template class RAIIWrapper< long >;
template class RAIIWrapper< unsigned long >;
template class RAIIWrapper< long long >;
template class RAIIWrapper< unsigned long long >;

}   // namespace simpleNewton
#endif
