
#include "Logger.hpp"

#include <ctime>
#include <iostream>
#include <fstream>
#include <mutex>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Basic logger module for the SimpleNewton framework 
*
|***************************************************************************************************************************************///+

void Logger::flushBuffer( flag_t _write ) {

   if( _write && ! buffer_.str().empty() )
      writeLog( (*this) );
   
   static std::mutex proc_cout_mutex;
   std::lock_guard< std::mutex > cout_lock( proc_cout_mutex );   // std::cout is also a shared, external 'resource'.
   std::cout << buffer_.str() << std::endl;
   buffer_.str( std::string() );
}



// This is process local. Threads must stand in line to get at this resource.
void Logger::writeLog( const Logger & lg ) {
   
   static std::mutex proc_file_mutex;   // Looks like lazy initialization;
   static std::ofstream file;           // owned by process, not threads.
   
   std::lock_guard< std::mutex > file_lock( proc_file_mutex );   // Thread safety
   
   file.open( ProcSingleton::getExecName() + "log_on_proc" + std::to_string( SN_MPI_RANK() ), std::ios_base::app );
   if( ! file.is_open() ) {
   
      real_t time_point = ProcSingleton::getDurationFromStart();
      std::cout << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK()
                << "][ERROR ]:   Could not open the log file for logger.";

      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
   
   time_t _now = time(nullptr);
   try {
      file << ctime( &_now) << lg.buffer_.str() << std::endl << std::endl;
   } 
   catch( std::exception & ex ) {

      real_t time_point = ProcSingleton::getDurationFromStart();
      std::cout << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK()
                << "][EXCEPTION CAUGHT ]: A standard exception was caught during the writing of the log file. " 
                << ex.what() << std::endl;
   }
   file.close();
}



// Bomb has been planted!
Logger::~Logger() {

   flushBuffer( true );
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   MACRO function implementation
///////////////////////////////////

namespace logger {
namespace impl {

bool eventWatchRegionSwitch_[] = { false, false };   // Here's a global!


void print_message( const std::string & msg ) {

   Logger lg( Logger::createInstance() );
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][MESSAGE ]:   " << msg << '\n';
   lg.flushBuffer( false );
}



void report_error( const std::string & msg, const std::string & file, int line ) {

   Logger lg( Logger::createInstance() );
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][ERROR ]:   " << msg << '\n' 
      << ">--- From <" << file << " :" << line << " > ---<" << '\n';
   lg.flushBuffer( true );
}



void catch_exception( std::exception & exc, const std::string & file, int line ) {

   Logger lg( Logger::createInstance() );
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][EXCEPTION CAUGHT ]:   " << exc.what() << '\n'
      << ">--- From <" << file << " :" << line << " > ---<" << '\n';
   lg.flushBuffer( true );
}



void report_warning( const std::string & msg, const std::string & file, int line ) {

   Logger lg( Logger::createInstance() );
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][WARNING ]:    " << msg << '\n'
      << ">--- From <" << file << " :" << line << " > ---<" << '\n';
      
   #ifdef __SN_LOGLEVEL_WRITE_WARNINGS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}



void markEventHorizon( const uint_t eventLevel ) {
   eventWatchRegionSwitch_[ eventLevel ] = ! eventWatchRegionSwitch_[ eventLevel ];
}
void report_L1_event( LogEventType event, const std::string & file, int line, const std::string & info ) {
   
   if( ! eventWatchRegionSwitch_[0] )
      return;
   
   Logger lg( Logger::createInstance() );
   
   std::string event_tag = "N/A";
   std::string descr = "N/A";

   switch( event ) {
      case LogEventType::ResAlloc: event_tag = "HEAP RESOURCE ALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
         
      case LogEventType::ResDealloc: event_tag = "HEAP RESOURCE DEALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
         
      case LogEventType::OMPFork: event_tag = "OMP PARALLEL REGION ENTERED"; descr = "OpenMP fork occurred. "; break;
         
      case LogEventType::OMPJoin: event_tag = "OMP PARALLEL REGION EXITED";  descr = "OpenMP operation synchronized. "; break;
         
      case LogEventType::MPISend: event_tag = "MPI COMMUNICATION (SEND)"; descr = "Package, source, target (in that order): "; break;
         
      case LogEventType::MPISsend: event_tag = "MPI COMMUNICATION (SYNC. SEND)"; 
                                   descr = "Package, source, target (in that order): "; break;
         
      case LogEventType::MPIIsend: event_tag = "MPI COMMUNICATION (ISEND)"; descr = "Package, source, target (in that order): "; break;
         
      case LogEventType::MPIRecv: event_tag = "MPI COMMUNICATION (RECV)"; descr = "Package, source, target (in that order): "; break;
        
      case LogEventType::MPIIrecv: event_tag = "MPI COMMUNICATION (IRECV)"; descr = "Package, source, target (in that order): "; break;
         
      case LogEventType::MPIBcast: event_tag = "MPI COMMUNICATION (BCAST)"; descr = "Package, source (in that order): "; break;
         
      case LogEventType::MPIWait: event_tag = "MPI COMMUNICATION (WAIT)"; 
                                  descr = "An immediate MPI operation has been completed."; break;
         
      case LogEventType::MPIWaitAll: event_tag = "MPI COMMUNICATION (WAITALL)"; 
                                     descr = "A set of immediate MPI operations has been completed."; break;
         
      case LogEventType::Other: event_tag = "SPECIAL EVENT"; descr = "A special event has occurred.";
         
      default: event_tag = "UNKNOWN EVENT"; descr = "An unspecified event has ocurred"; break;
   }
   
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][L1 EVENT - " << event_tag << " ]:   " 
      << descr << "   " << info << '\n' 
      << ">--- From <" << file << " :" << line << " > ---<" << '\n';
   
   #ifdef __SN_LOGLEVEL_WRITE_EVENTS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}
void report_L2_event( const std::string & file, int line, const std::string & event_tag, const std::string & descr ) {
   
   if( ! eventWatchRegionSwitch_[1] )
      return;
   
   Logger lg( Logger::createInstance() );
   
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][L2 EVENT - " << event_tag << " ]:   " 
      << descr << '\n' 
      << ">--- From <" << file << " :" << line << " > ---<" << '\n';
   
   #ifdef __SN_LOGLEVEL_WRITE_EVENTS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}



void watch_impl( Logger & ) {}

}   // namespace impl
}   // namespace logger

}   // namespace simpleNewton
