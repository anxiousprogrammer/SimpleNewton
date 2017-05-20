#include "MPIRequest.hpp"

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
///   Contains the explicit instantiations of MPIRequest with every basic data type.
///   \file
///   \addtogroup containers Containers
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace simpleNewton {

template<> class MPIRequest< char >;
template<> class MPIRequest< unsigned char >;

template<> class MPIRequest< short >;
template<> class MPIRequest< unsigned short >;

template<> class MPIRequest< int >;
template<> class MPIRequest< unsigned int >;

template<> class MPIRequest< long >;
template<> class MPIRequest< unsigned long >;

template<> class MPIRequest< long long >;
template<> class MPIRequest< unsigned long long >;

template<> class MPIRequest< float >;
template<> class MPIRequest< double >;

}   // namespace simpleNewton
#endif
