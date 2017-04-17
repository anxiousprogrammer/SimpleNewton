#include <Logger.hpp>
#include <Asserts.hpp>

using namespace simpleNewton;

int main() {
   
   Logger::writeSettings< std::ofstream >( __SN_LOGLEVEL_WARNING__ );
   SN_LOG_REPORT_ERROR( " It didn't work out between us" );
   SN_LOG_REPORT_EVENT( LogEvent::ResAlloc, "j", "int", "3" );
   
   return 0;
}
