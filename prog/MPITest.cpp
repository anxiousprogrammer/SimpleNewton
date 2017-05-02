#include <iostream>

#include <core/MPIManager.hpp>
#include <core/Communicator.hpp>
#include <logger/Logger.hpp>

using namespace simpleNewton;

int main( int argc, char ** argv ) {
   
   MPIManager::init( argc, argv );
   Logger::writeSettings< std::ofstream >( argc, argv );
   
   SN_LOG_REPORT_WARNING( "Hi! Testing the MPI module." );
   
   float j[] = { single_cast( SN_MPI_RANK() ), single_cast( SN_MPI_RANK() ), single_cast( SN_MPI_RANK() ) };

   SN_MPI_PROC_REGION( 1 ) {
      Communicator::BSend( &j, 3, SN_ROOT_PROC );
   }
   
   float rec_j[] = { 20.0, 20.0, 20.0 };
   
   SN_MPI_PROC_REGION( SN_ROOT_PROC ) {
      Communicator::BRecv( &rec_j, 3, 1 );
      SN_LOG_WATCH_VARIABLES( "The received value: ", single_cast(rec_j[0]), single_cast(rec_j[1]), single_cast(rec_j[2]) );
   }
   
   return 0;
}
