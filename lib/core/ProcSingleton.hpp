#ifndef SN_PROCSINGLETON_HPP
#define SN_PROCSINGLETON_HPP

#include <chrono>

#include <Types.hpp>
#include <BasicBases.hpp>

#include "ProcTimer.hpp"

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
///   Contains the class ProcSingleton, which is a vital, process managing singleton class.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//=== CLASS ================================================================================================================================

/** This is a singleton class responsible for managing the most important functions and requirements of a process. The instance 
*   manages the MPI initialization and finalization, provides an unconventional exit strategy for the program and also a timer, among other 
*   functions and services. The lifetime of the singleton spans the lifetime of the program. Any program using the simpleNewton framework
*   must necessarily begin by calling the ProcSingleton's init member function.
*/
//==========================================================================================================================================

class ProcSingleton : private Singleton {

public:
   
   /** A function which setups the process singleton. */
   static void init( int argc, char ** argv );
   
   /** \name Access
   *   @{
   */
   /** A function to obtain the singleton instance */
   static const ProcSingleton & getInstance();
   
   /** A function which inspects the state of the process singleton: has it been initialised? */
   static bool isInitialized();
   
   /** A function which inspects the state of the process singleton: has it been initialised with thread support? */
   static bool isInitializedWithMultithreading();
   
   /** A function which can be used to ascertain the name of the executable. */
   static const std::string & getExecName();
   
   /** A function which can be used to get the process rank.
   *
   *   \return   The size of the communicator.
   */
   static inline int getCommSize()   { return getPrivateInstance().comm_size_; }
   
   /** A function which can be used to get the number of processes in the communicator.
   *
   *   \return   The process rank in the communicator.
   */
   static inline int getCommRank()   { return getPrivateInstance().comm_rank_; }
   
   /** @} */
   
   /** \name Timer
   *   @{
   */
   /** A function to get the resolution of the clock in seconds
   *
   *   \return   The resolution of the chosen clock in seconds.
   */
   static inline real_t getProcTimerRes()   { return ProcTimer::getExactResolution(); }
   
   /** A function which can be used to get the total duration from the start of the process.
   *
   *   \return   The duration from the start-point of the process in highest resolution.
   */
   static inline real_t getDurationFromStart() {
      return getPrivateInstance().timer_.getAge();
   }
   
   /** @} */
   
   /** A function which decides the unconventional exit strategy for errors, exceptions and other reasons. */
   static inline void ExitProgram() { std::exit( EXIT_FAILURE ); }
   
private:
   
   /* Matters of god (!) */
   /** \name Constructors and destructor
   *   @{
   */
   /** Default trivial constructor. */
   ProcSingleton() = default;
   
   /** Explicitly defined destructor. */
   ~ProcSingleton();
   
   /** @} */
   
   /** Access for static member functions.
   *
   *   \return   The singleton instance
   */
   static inline ProcSingleton & getPrivateInstance() {
   
      static ProcSingleton single;
      return single;
   }
   
   /** Name of the exec */
   std::string exec_name_;
   
   /** State flags */
   bool is_initialized_ = false;
   bool is_initialized_with_multithreading_ = false;
   
   /** Timer */
   ProcTimer timer_ = {};
   
   /** Size and Rank */
   int comm_size_ = 0, comm_rank_ = 0;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Scope Macros and important global functions
/////////////////////////////////////////////////

/** A macro which identifies the root process. */
#define SN_ROOTPROC 0

#ifdef __SN_USE_MPI__

 /** A global function which can be used to obtain the rank of the process. */
 #define SN_MPI_INITIALIZED()              ( ProcSingleton::isInitialized() || ProcSingleton::isInitializedWithMultithreading() )
 
 /** A global function which can be used to obtain the rank of the process. */
 inline int SN_MPI_RANK()                  { return ProcSingleton::getCommRank(); }
 
 /** A global function which can be used to obtain the size of the communicator. */
 inline int SN_MPI_SIZE()                  { return ProcSingleton::getCommSize(); }
 
 /** A global scope macro which can be used to specify code intended for execution only on the root process. */
 #define SN_MPI_ROOTPROC_REGION()          if( ProcSingleton::getCommRank() == 0 )
 
 /** A global scope macro which can be used to specify code intended for execution on every process except the root process. */
 #define SN_MPI_EXCEPT_ROOTPROC_REGION()   if( ProcSingleton::getCommRank() != 0 )
 
 /** A global scope macro which can be used to specify code intended for execution only on the process with rank ID. */
 #define SN_MPI_PROC_REGION( ID )          if( ProcSingleton::getCommRank() == ID )
 
 /** A global scope macro which can be used to specify code intended for execution on every process except the process with rank ID. */
 #define SN_MPI_EXCEPT_PROC_REGION( ID )   if( ProcSingleton::getCommRank() != ID )
 
 /** A global macro which makes an MPI Barrier i.e., process synchronization point. */
 #define SN_MPI_BARRIER()                  MPI_Barrier( MPI_COMM_WORLD )
 
#else

#ifndef DOXYGEN_SHOULD_SKIP_THIS
 #define SN_MPI_INITIALIZED()              false
 inline int SN_MPI_RANK()                  { return 0; }
 inline int SN_MPI_SIZE()                  { return 1; }
 #define SN_MPI_ROOTPROC_REGION()          if( true  )
 #define SN_MPI_EXCEPT_ROOTPROC_REGION()   if( false )
 #define SN_MPI_PROC_REGION( ID )          if( false )
 #define SN_MPI_EXCEPT_PROC_REGION( ID )   if( true  )
 #define SN_MPI_BARRIER()
#endif   // DOXYSKIP
 
#endif

}   // namespace simpleNewton

#endif
