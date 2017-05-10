#ifndef PROCSINGLETON_HPP
#define PROCSINGLETON_HPP

#include <chrono>

#include <Types.hpp>
#include <BasicBases.hpp>

#ifdef __SN_USE_MPI__
#include <mpi.h>
#endif

namespace simpleNewton {

/**||**************************************************************************************************************************************
*
*   Description: Get that MPI scene going on. The only class which follows Meyer's Singleton scheme in the framework.
*
|**************************************************************************************************************************************///+



class ProcSingleton : private Singleton {

public:
   
   /* Get the One: wrapper for proper access */
   static const ProcSingleton & getInstance();
   
   /* Setup the process singleton. Must do for every process */
   static void init( int argc, char ** argv );
   
   /* State inspection */
   static bool isInitialized();
   static inline int getCommSize()   { return getPrivateInstance().comm_size_; }
   static inline int getCommRank()   { return getPrivateInstance().comm_rank_; }
   
   /* Exec name is required by many a module */
   static const std::string & getExecName();
   
   /* Timers */
   static inline std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime() { 
      return std::chrono::high_resolution_clock::now();
   }
   static inline std::chrono::time_point<std::chrono::high_resolution_clock> getStartTime() {
      return getPrivateInstance().start_time_;
   }
   static inline real_t getDuration( const std::chrono::time_point<std::chrono::high_resolution_clock> & t1,
                                     const std::chrono::time_point<std::chrono::high_resolution_clock> & t2 ) {
      return std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 ).count();
   }
   static inline real_t getDurationFromStart() {
      return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - 
                                                                      getPrivateInstance().start_time_ ).count();
   }
   
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
///   Scope Macros and important global functions
/////////////////////////////////////////////////

// Give root process a name
#define SN_ROOT_PROC 0

#ifdef __SN_USE_MPI__

 inline int SN_MPI_RANK()           { return ProcSingleton::getCommRank(); }
 inline int SN_MPI_SIZE()           { return ProcSingleton::getCommSize(); }
 #define SN_MPI_ROOTPROC_REGION()   if( ProcSingleton::getCommRank() == 0 )
 #define SN_MPI_PROC_REGION( ID )   if( ProcSingleton::getCommRank() == ID )
 #define SN_MPI_BARRIER()           MPI_Barrier( MPI_COMM_WORLD )
 
#else

 inline int SN_MPI_RANK()           { return 0; }
 inline int SN_MPI_SIZE()           { return 1; }
 #define SN_MPI_ROOTPROC_REGION()   if( true  )
 #define SN_MPI_PROC_REGION( ID )   if( false )
 #define SN_MPI_BARRIER()
 
#endif

}   // namespace simpleNewton

#endif
