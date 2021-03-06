#include <iostream>

#include <core/ProcSingleton.hpp>
#include <concurrency/BaseComm.hpp>
#include <logger/Logger.hpp>

using namespace simpleNewton;

int main( int argc, char ** argv ) {
   
   ProcSingleton::init( argc, argv );
   
   SN_LOG_L1_EVENT_WATCH_REGION_LIMIT();
   
   SN_LOG_REPORT_WARNING( "Hi! Testing the MPI module." );
   
   FastBuffer< char > j     = "Hallo, MPI World!";
   FastBuffer< char > rec_j = "Not arrived";
   MPIRequest< char > r1, r2;
   
   SN_MPI_PROC_REGION( 1 ) {
      BaseComm< char >::send< MPISendMode::Immediate >( j, SN_ROOTPROC, r1 );
      BaseComm< char >::wait< MPIWaitOp::Send >( r1 );
   }
   SN_MPI_PROC_REGION( SN_ROOTPROC ) {
   
      BaseComm< char >::receive< MPIRecvMode::Immediate >( rec_j, 17, 1, r2 );
      BaseComm< char >::wait< MPIWaitOp::Receive >( r2 );
      SN_LOG_WATCH_VARIABLES( "The received value: ", make_std_string( rec_j ), rec_j.getSize() );
      rec_j = "autoSend Futter";
   }
   
   BaseComm< char >::autoSend( j, rec_j, SN_ROOTPROC, 1 );
   
   SN_MPI_PROC_REGION( 1 ) {
      SN_LOG_WATCH_VARIABLES( "The value received from the autoSend is: ", make_std_string( rec_j ) );
   }
   
   SN_MPI_PROC_REGION( SN_ROOTPROC ) {
      rec_j = "bcast Futter";
   }
   
   BaseComm< char >::autoBroadcast( rec_j, SN_ROOTPROC );
   
   SN_LOG_WATCH_VARIABLES( "The value received from the autoBCast is: ", make_std_string( rec_j ) );
   
   return 0;
}
