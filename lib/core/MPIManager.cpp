#include "MPIManager.hpp"
#include <iostream>
#include <ctime>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: implementation of the simpleNewton MPIManager
*
|***************************************************************************************************************************************///+

const MPIManager & MPIManager::getInstance() {
   
   if( ! MPIManager::getPrivateInstance().is_initialized_ ) {
   
      SN_MPI_ROOTPROC_REGION() {
   
         std::cout << "[MPIMAN__>][FATAL ERROR ]:   MPI Manager was not initialised before being called to service. "
                   << "Please use the member function MPIManager::init for this purpose. The program will now exit."
                   << std::endl;
      }
      
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   return static_cast< const MPIManager & >( MPIManager::getPrivateInstance() );
}



void MPIManager::init( int argc, char ** argv ) {
   if( ! MPIManager::getPrivateInstance().is_initialized_ ) {
      
      if( argc < 1 || argv == nullptr ) {   // Killing that -Wunused-parameter warning when not using MPI
         SN_MPI_ROOTPROC_REGION() {
            std::cout << "[MPIMAN__>][EVENT ]:   Improper initializing arguments provided to MPIManager::init." << std::endl;
         }
         
         /////////////////
         ///   EXIT POINT!
         SN_EXIT();
         /////////////////
      }
      
      #ifdef __SN_USE_MPI__
      MPI_Init( &argc, &argv );

      MPI_Comm_size( MPI_COMM_WORLD, & MPIManager::getPrivateInstance().comm_size_ );
      MPI_Comm_rank( MPI_COMM_WORLD, & MPIManager::getPrivateInstance().comm_rank_ );
      #endif
      
      // Console initialization
      SN_MPI_ROOTPROC_REGION() {
      
         time_t _now( time(nullptr) );
         std::cout << "========================================================================================================>" 
                   << std::endl
                   << "********************************************************************************************************" 
                   << std::endl
                   << ">>>   Simple Newton framework running \'" << argv[0] 
                   << "\' with start time: " << ctime( &_now ) << std::endl;
      }
      SN_MPI_BARRIER();
      
      #ifdef __SN_USE_MPI__
      SN_MPI_ROOTPROC_REGION() {
         std::cout << "[MPIMAN__>][ROOTPROC][EVENT ]:   MPI has been initialized." << std::endl << std::endl;
      }
      #endif

      // Fly the flag: all is well!
      MPIManager::getPrivateInstance().is_initialized_  = true;
   }
}



MPIManager::~MPIManager() {

   SN_MPI_BARRIER();
   SN_MPI_ROOTPROC_REGION() {
   
   #ifdef __SN_USE_MPI__
   std::cout << "[MPIMAN__>][ROOTPROC][EVENT ]:   MPI has been finalized." << std::endl;
   #endif
   
      time_t _now = time(nullptr);
      //Wrap up I/O
      std::cout << ">>>   Program completed execution with end time " << ctime( &_now );
      std::cout << "********************************************************************************************************" << std::endl
                << "========================================================================================================>" << std::endl;
   }
   
   #ifdef __SN_USE_MPI__
   MPI_Finalize();
   #endif

   is_initialized_ = false;
   comm_size_ = 0;
   comm_rank_ = 0;
}



bool MPIManager::isInitialized() {
   return MPIManager::getPrivateInstance().is_initialized_;
}


}   // namespace simpleNewton
