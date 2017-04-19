#include <vector>
#include <Logger.hpp>
#include <Asserts.hpp>

using namespace simpleNewton;

int main( int argc, char ** argv ) {
   
   int j;
   float k;
   std::vector< std::string > v;
   Logger::writeSettings< std::ofstream >( argc, argv, __SN_LOGLEVEL_WARNING__ );
   SN_LOG_MESSAGE( "Hi! Testing the logger." );
   SN_LOG_REPORT_EVENT( LogEventType::ResAlloc, "j, int, 3" );
   SN_LOG_REPORT_EVENT( LogEventType::ResDealloc, "j, int, 3" );
   SN_LOG_REPORT_EVENT( LogEventType::OMPFork, "" );
   SN_LOG_REPORT_EVENT( LogEventType::OMPJoin, "" );
   //SN_LOG_WATCH_VARIABLES( "Watch them", j, k, v );
   SN_LOG_REPORT_WARNING( " Watch out!" );
   SN_LOG_REPORT_ERROR( " It didn't work out between us" );
   
   return 0;
}
