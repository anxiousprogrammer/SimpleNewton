#ifndef SN_PROCSINGLETON_HPP
#define SN_PROCSINGLETON_HPP

#include <chrono>

#include <Types.hpp>
#include <BasicBases.hpp>

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

/** ProcSingleton is a singleton class responsible for managing the most important functions and requirements of a process. The instance 
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
   
   /** A function which can be used to get the process rank. */
   static inline int getCommSize()   { return getPrivateInstance().comm_size_; }
   
   /** A function which can be used to get the number of processes in the communicator. */
   static inline int getCommRank()   { return getPrivateInstance().comm_rank_; }
   
   /** A function which can be used to ascertain the name of the executable. */
   static const std::string & getExecName();
   
   /** @} */
   
   /** \name Timer
   *   @{
   */
   /** A function which can be used to get the current, high resolution time-point
   *
   *   \return   The current time-point.
   */
   static inline std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime() {
      return std::chrono::high_resolution_clock::now();
   }
   
   /** A function which can be used to get the high resolution time-point from the start of the process.
   *
   *   \return   The starting time-point.
   */
   static inline std::chrono::time_point<std::chrono::high_resolution_clock> getStartTime() {
      return getPrivateInstance().start_time_;
   }
   
   /** A function which can be used to get the duration between two high resolution time-points.
   *
   *   \param t1   The chronologically first high resolution time-point.
   *   \param t2   The chronologically second high resolution time-point.
   *   \return     The duration in highest possible precision.
   */
   static inline real_t getDuration( const std::chrono::time_point<std::chrono::high_resolution_clock> & t1,
                                     const std::chrono::time_point<std::chrono::high_resolution_clock> & t2 ) {
      return std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 ).count();
   }
   
   /** A function which can be used to get the total duration from the start of the process.
   *
   *   \return   The duration from the start-point of the process in highest resolution.
   */
   static inline real_t getDurationFromStart() {
      return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - 
                                                                      getPrivateInstance().start_time_ ).count();
   }
   
   /** @} */
   
   /* Specified exit */
   static inline void ExitProgram() { std::exit( EXIT_FAILURE ); }
   
private:
   
   /* Matters of god (!) */
   ProcSingleton() = default;
   ~ProcSingleton();
   
   /* Access for static member functions */
   static inline ProcSingleton & getPrivateInstance() {
   
      static ProcSingleton single;
      return single;
   }
   
   /* Name of the exec */
   std::string exec_name_;
   
   /* State flag */
   bool is_initialized_ = false;
   
   /* Timer */
   std::chrono::time_point<std::chrono::high_resolution_clock> start_time_ = std::chrono::high_resolution_clock::now();
   
   /* Size and Rank */
   int comm_size_ = 0, comm_rank_ = 0;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Scope Macros and important global functions
/////////////////////////////////////////////////

// Give root process a name
#define SN_ROOTPROC 0

#ifdef __SN_USE_MPI__

 inline int SN_MPI_RANK()                  { return ProcSingleton::getCommRank(); }
 inline int SN_MPI_SIZE()                  { return ProcSingleton::getCommSize(); }
 #define SN_MPI_ROOTPROC_REGION()          if( ProcSingleton::getCommRank() == 0 )
 #define SN_MPI_EXCEPT_ROOTPROC_REGION()   if( ProcSingleton::getCommRank() != 0 )
 #define SN_MPI_PROC_REGION( ID )          if( ProcSingleton::getCommRank() == ID )
 #define SN_MPI_EXCEPT_PROC_REGION( ID )   if( ProcSingleton::getCommRank() != ID )
 #define SN_MPI_BARRIER()                  MPI_Barrier( MPI_COMM_WORLD )
 
#else

 inline int SN_MPI_RANK()                  { return 0; }
 inline int SN_MPI_SIZE()                  { return 1; }
 #define SN_MPI_ROOTPROC_REGION()          if( true  )
 #define SN_MPI_EXCEPT_ROOTPROC_REGION()   if( false )
 #define SN_MPI_PROC_REGION( ID )          if( false )
 #define SN_MPI_EXCEPT_PROC_REGION( ID )   if( true  )
 #define SN_MPI_BARRIER()
 
#endif

}   // namespace simpleNewton

#endif
