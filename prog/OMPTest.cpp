#include <iostream>

#include <core/ProcSingleton.hpp>
#include <logger/Logger.hpp>

#include <concurrency/OpenMP.hpp>
#include <concurrency/ThreadPool.hpp>

using namespace simpleNewton;

void func() {
   SN_LOG_MESSAGE( "Slave thread says hello!" );
}

int main( int argc, char ** argv ) {
   
   ProcSingleton::init( argc, argv );
   SN_LOG_SWITCH_ON_CONSOLE_OUTPUT();
   
   SN_LOG_L1_EVENT_WATCH_REGION_LIMIT();
   
   SN_OPENMP_FORK_REGION( OMP_THREADS(5) )
      
      SN_LOG_MESSAGE( "Critical region test passed." );   // All Logger functions are inherently atomic ops.
      
      OMP_FOR_LOOP( OMP_ORDERED )
      for( uint_t i = 0; i < 10; ++i ) {
         SN_LOG_WATCH_VARIABLES( "Itertion number", i );
      }
      
   SN_OPENMP_SYNC()

   ThreadPool ThreadMan;
   ThreadMan.spinThread( &func );
   
   return 0;
}
