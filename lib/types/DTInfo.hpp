#ifndef SN_DTINFO_HPP
#define SN_DTINFO_HPP

#ifdef __SN_USE_MPI__
   #include <mpi.h>
#endif

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
///   Contains the struct template DTInfo, which gets rid of some boilerplate coding and serves as an implementation-independent typeid 
///   operator of sorts for basic data types only.
///   \file
///   \addtogroup types Types
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {


//===CLASS==================================================================================================================================

/** This class serves as a tool for eliminating repetitive coding induced by certain requirements of type information e.g., typename 
*   of basic data types in string, basic MPI data typenames etc.
*
*   \tparam TYPE   The type about which it is desired to have certain information.
*/
//==========================================================================================================================================

template< typename TYPE > struct DTInfo {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_DATATYPE_NULL;   ///< The MPI_Datatype to be used for the type specified by template 
                                                                 ///  parameter.
   static constexpr char mpi_name[] = "N/A";                     ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "N/A";                         ///< The typename of basic data type in string.
};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* Explicit specialization: bool */
template<> struct DTInfo< bool > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_INT;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_INT";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "bool";              ///< The typename of basic data type in string.
};



/* Explicit specialization: char */
template<> struct DTInfo< char > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_CHAR;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_CHAR";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "char";               ///< The typename of basic data type in string.
};
                                           
template<> struct DTInfo< unsigned char > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_CHAR;   ///< The MPI_Datatype to be used for the type specified by template 
                                                                 ///  parameter.
   static constexpr char mpi_name[] = "MPI_UNSIGNED_CHAR";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "unsigned char";               ///< The typename of basic data type in string.
};



/* Explicit specialization: short */
template<> struct DTInfo< short > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_SHORT;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_SHORT";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "short";               ///< The typename of basic data type in string.
};
                                            
template<> struct DTInfo< unsigned short > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_SHORT;   ///< The MPI_Datatype to be used for the type specified by template 
                                                                  ///  parameter.
   static constexpr char mpi_name[] = "MPI_UNSIGNED_SHORT";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "unsigned short";               ///< The typename of basic data type in string.
};



/* Explicit specialization: int */
template<> struct DTInfo< int > {

   #ifdef __SN_USE_MPI__    
   static constexpr MPI_Datatype mpi_type = MPI_INT;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_INT";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "int";               ///< The typename of basic data type in string.
};

template<> struct DTInfo< unsigned int > {

   #ifdef __SN_USE_MPI__   
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_UNSIGNED";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "unsigned int";           ///< The typename of basic data type in string.
};



/* Explicit specialization: long */
template<> struct DTInfo< long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_LONG;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_LONG";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "long";               ///< The typename of basic data type in string.
};

template<> struct DTInfo< unsigned long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_LONG;   ///< The MPI_Datatype to be used for the type specified by template 
                                                                 ///  parameter.
   static constexpr char mpi_name[] = "MPI_UNSIGNED_LONG";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "unsigned long";               ///< The typename of basic data type in string.
};



/* Explicit specialization: long long */
template<> struct DTInfo< long long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_LONG_LONG;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_LONG_LONG";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "long long";               ///< The typename of basic data type in string.
};
                                                
template<> struct DTInfo< unsigned long long > {

   #ifdef __SN_USE_MPI__   
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_LONG_LONG;   ///< The MPI_Datatype to be used for the type specified by template 
                                                                      ///  parameter.
   static constexpr char mpi_name[] = "MPI_UNSIGNED_LONG_LONG";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "unsigned long long";               ///< The typename of basic data type in string.
};



/* Explicit specialization: floating point */
template<> struct DTInfo< float >  {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_FLOAT;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_FLOAT";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "float";               ///< The typename of basic data type in string.
};

template<> struct DTInfo< double > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_DOUBLE;   ///< The MPI_Datatype to be used for the type specified by template parameter.
   static constexpr char mpi_name[] = "MPI_DOUBLE";       ///< The MPI_Datatype's name in string (for logging purposes).
   #endif
   
   static constexpr char name[] = "double";               ///< The typename of basic data type in string.
};

#endif   // DOXYSKIP

}   // namespace simpleNewton

#endif


