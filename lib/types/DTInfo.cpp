#include "DTInfo.hpp"

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
///   Declarations in this source file are for the constexpr variables in DTInfo.
///   \file
///   \defgroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< char >::mpi_type;
constexpr char DTInfo< char >::mpi_name[];
#endif
constexpr char DTInfo< char >::name[];




#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned char >::mpi_type;
constexpr char DTInfo< unsigned char >::mpi_name[];
#endif
constexpr char DTInfo< unsigned char >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< short >::mpi_type;
constexpr char DTInfo< short >::mpi_name[];
#endif
constexpr char DTInfo< short >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned short >::mpi_type;
constexpr char DTInfo< unsigned short >::mpi_name[];
#endif
constexpr char DTInfo< unsigned short >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< int >::mpi_type;
constexpr char DTInfo< int >::mpi_name[];
#endif
constexpr char DTInfo< int >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned int >::mpi_type;
constexpr char DTInfo< unsigned int >::mpi_name[];
#endif
constexpr char DTInfo< unsigned int >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< long >::mpi_type;
constexpr char DTInfo< long >::mpi_name[];
#endif
constexpr char DTInfo< long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned long >::mpi_type;
constexpr char DTInfo< unsigned long >::mpi_name[];
#endif
constexpr char DTInfo< unsigned long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< long long >::mpi_type;
constexpr char DTInfo< long long >::mpi_name[];
#endif
constexpr char DTInfo< long long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned long long >::mpi_type;
constexpr char DTInfo< unsigned long long >::mpi_name[];
#endif
constexpr char DTInfo< unsigned long long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< float >::mpi_type;
constexpr char DTInfo< float >::mpi_name[];
#endif
constexpr char DTInfo< float >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< double >::mpi_type;
constexpr char DTInfo< double >::mpi_name[];
#endif
constexpr char DTInfo< double >::name[];

}   // namespace simpleNewton
#endif   // DOXYSKIP
