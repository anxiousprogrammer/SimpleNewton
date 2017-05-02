#ifndef MPIMANAGER_HPP
#define MPIMANAGER_HPP

#include <iostream>
#include <Types.hpp>
#include <BasicBases.hpp>

#ifdef __SN_USE_MPI__
#include <mpi.h>
#endif

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Get that MPI scene going on. The Manager class follows Meyer's Singleton scheme.
*
|***************************************************************************************************************************************///+



class MPIManager : private Singleton {

public:
   
   /* Get the One: wrapper for proper access */
   static const MPIManager & getInstance();
   
   /* Setup the MPI Manager. */
   static void init( int argc, char ** argv );
   
   /* State inspection */
   static bool isInitialized();
   static inline int getCommSize()   { return MPIManager::getPrivateInstance().comm_size_; }
   static inline int getCommRank()   { return MPIManager::getPrivateInstance().comm_rank_; }
   
private:
   
   /* Matters of god (!) */
   MPIManager() = default;
   ~MPIManager();
   
   /* Access for static member functions */
   static inline MPIManager & getPrivateInstance() {
   
      static MPIManager single;
      return single;
   }
   
   /* State flag */
   bool is_initialized_ = false;
   
   /* Size and Rank */
   int comm_size_ = 0, comm_rank_ = 0;
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Scope Macros and important global functions
/////////////////////////////////////////////////

// Give root process a name
#define SN_ROOT_PROC 0

// Localize the unconventional exit procedure to this point.
inline void SN_EXIT() {
   std::exit( EXIT_FAILURE );
}

#ifdef __SN_USE_MPI__
 inline int SN_MPI_RANK()           { return MPIManager::getCommRank(); }
 inline int SN_MPI_SIZE()           { return MPIManager::getCommSize(); }
 #define SN_MPI_ROOTPROC_REGION()   if( MPIManager::getCommRank() == 0 )
 #define SN_MPI_PROC_REGION( ID )   if( MPIManager::getCommRank() == ID )
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
