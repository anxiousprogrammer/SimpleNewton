#include "BaseComm.hpp"

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
///   This source file explicitly instantiates the class template of BaseComm in order to ensure there is no error in any instantiation.
///   The instantiation is performed with template parameter taking on every basic data type.
///   \file
///   \addtogroup concurrency Concurrency
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//===========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace simpleNewton {

template struct BaseComm< bool >;
template struct BaseComm< char >;
template struct BaseComm< unsigned char >;
template struct BaseComm< short >;
template struct BaseComm< unsigned short >;
template struct BaseComm< int >;
template struct BaseComm< unsigned int >;
template struct BaseComm< long >;
template struct BaseComm< unsigned long >;
template struct BaseComm< long long >;
template struct BaseComm< unsigned long long >;
template struct BaseComm< float >;
template struct BaseComm< double >;

}   // namespace simpleNewton
#endif
