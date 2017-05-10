#include <vector>

#include <logger/Logger.hpp>

using namespace simpleNewton;

int main( int argc, char ** argv ) {

   SN_LOG_EVENT_WATCH_REGION_LIMIT();
   int j = 0;
   float k = 0.f;
   ProcSingleton::init( argc, argv );

   SN_LOG_EVENT_WATCH_REGION_LIMIT();
   SN_LOG_MESSAGE( "Hi! Testing the logger." );
   SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "j, int, 3" );
   SN_LOG_REPORT_EVENT( LogEventType::ResDealloc, "j, int, 3" );
   SN_LOG_REPORT_EVENT( LogEventType::OMPFork, "" );
   SN_LOG_REPORT_EVENT( LogEventType::OMPJoin, "" );
   SN_LOG_WATCH_VARIABLES( "Watch them", j, k );
   SN_LOG_REPORT_WARNING( " Watch out!" );
   SN_LOG_REPORT_ERROR( " It didn't work out between us" );
   
   return 0;
}
