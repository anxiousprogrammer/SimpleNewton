#include "Logger.hpp"
#include "BasicTypeTraits.hpp" 

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Basic logger module for the SimpleNewton framework 
*
|***************************************************************************************************************************************///+

Logger & Logger::getInstance() {
   static Logger single;
   return single;
}

void Logger::flushBuffer( flag_t _write ) {
   std::cout << buffer_.str() << std::endl;
   if( _write )
      writeLog();
   buffer_.str( std::string() );
}

void Logger::writeLog() {
   if( ! Logger::getInstance().streamSet_ ) {
      std::cout << "[LOGGER__>][ERROR ]:   Logger attempted to write to no destination. Please set write settings first." << std::endl;
      std::cout << "========================================================================================================>" << std::endl;
      std::abort();
   }
   
   if( Logger::getInstance().buffer_.str().empty() ) {
      return;
   }
   
   Logger::getInstance().file_guard_.lock();
   static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).open( "log.txt", std::ios_base::app );
   if( ! static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).is_open() ) {
      std::cout << "[LOGGER__>][ERROR ]:   Could not open the log file for logger.";
      std::cout << "========================================================================================================>" << std::endl;
      std::abort();
   }
   
   try {
   (*Logger::getInstance().file_) << Logger::getInstance().buffer_.str() << std::endl;
   } 
   catch( std::exception & ex ) {
      std::cout << "[LOGGER__>][EXCEPTION ]: A standard exception was caught during the writing of the log file. " 
                << ex.what() << std::endl;
      std::cout << "========================================================================================================>" << std::endl;
   }
   static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).close();
   Logger::getInstance().file_guard_.unlock();
}

Logger::~Logger() {
   flushBuffer( true );
   writeLevel_ = 0;
}



void report_error( const char * msg, const char * const file, int line ) {
   Logger::getInstance() << "[LOGGER__>][ERROR ]:   " << "<Description>   " << msg
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   Logger::getInstance() << "==============================================================================================>" << Logger::nl;
   Logger::getInstance() << Logger::b_write;
}



void report_warning( const char * msg, const char * const file, int line ) {
   Logger::getInstance() << "[LOGGER__>][WARNING ]:    " << msg
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   Logger::getInstance() << "==============================================================================================>" << Logger::nl;

   if( Logger::writeLevel() >= __SN_LOGLEVEL_WARNING__ )
      Logger::getInstance() << Logger::b_write;
   else
      Logger::getInstance() << Logger::b_end;
}



void report_event( LogEvent event, const char * const file, int line, 
                   const char * ptr_name = "", const char * res_type = "", const char * array_size = "" ) {
   std::string event_tag;
   std::string descr;
   switch( event ) {
   case LogEvent::ResAlloc: event_tag = "RESOURCE ALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
   case LogEvent::ResDealloc: event_tag = "RESOURCE DEALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
   case LogEvent::OMPFork: event_tag = "OMP PARALLEL REGION ENTERED"; descr = "OpenMP fork occurred. "; break;
   case LogEvent::OMPJoin: event_tag = "OMP PARALLEL REGION EXITED";  descr = "OpenMP operation synchronized. "; break;
   case LogEvent::MPISend: event_tag = "MPI COMMUNICATION (SEND)"; descr = "An MPI_Send operation was completed successfully. "; break;
   case LogEvent::MPIRecv: event_tag = "MPI COMMUNICATION (RECV)"; descr = "An MPI_Recv operation was completed successfully. "; break;
   case LogEvent::MPIBCast: event_tag = "MPI COMMUNICATION (BCAST)"; descr = "An MPI_BCast operation was completed successfully. "; break;
   default: event_tag = "UNKNOWN EVENT"; break;
   };
   Logger::getInstance() << "[LOGGER__>][EVENT - " << event_tag << " ]:   " << descr << ptr_name << ", " << res_type << ", " << array_size
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   Logger::getInstance() << "==============================================================================================>" << Logger::nl;
   if( Logger::writeLevel() >= __SN_LOGLEVEL_EVENT__ )
      Logger::getInstance() << Logger::b_write;
   else
      Logger::getInstance() << Logger::b_end;
}

}   // namespace simpleNewton
