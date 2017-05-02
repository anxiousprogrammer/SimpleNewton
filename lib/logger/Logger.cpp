#include "Logger.hpp"

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Basic logger module for the SimpleNewton framework 
*
|***************************************************************************************************************************************///+


void Logger::flushBuffer( flag_t _write ) {

   std::cout << buffer_.str() << std::endl;
   if( _write )
      writeLog();
   buffer_.str( std::string() );
}



void Logger::writeLog() {

   if( ! Logger::getInstance().streamSet_ ) {
   
      auto timep = getCurrentTime();
      real_t point = millisecondDuration( getStartTime(), timep );
      std::cout << "["<< point << " ms][LOGGER__>][P" << MPIManager::getCommRank() 
                << "][ERROR ]:   Logger attempted to write using no proper stream. Please set write settings first." << std::endl;
      
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   if( Logger::getInstance().buffer_.str().empty() ) {
      return;
   }
   
   Logger::getInstance().file_guard_.lock();   // Thread safety
   static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).open( Logger::getInstance().exec_.substr(2) + "log_on_proc" + 
                                                                          std::to_string( SN_MPI_RANK() ), std::ios_base::app );
   if( ! static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).is_open() ) {
   
      auto timep = getCurrentTime();
      real_t point = millisecondDuration( getStartTime(), timep );
      std::cout << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() 
                << "][ERROR ]:   Could not open the log file for logger.";

      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   time_t _now = time(nullptr);
   try {
   (*Logger::getInstance().file_) << ctime( &_now) << Logger::getInstance().buffer_.str() << std::endl << std::endl;
   } 
   catch( std::exception & ex ) {
   
      auto timep = getCurrentTime();
      real_t point = millisecondDuration( getStartTime(), timep );
      std::cout << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() 
                << "][EXCEPTION CAUGHT ]: A standard exception was caught during the writing of the log file. " 
                << ex.what() << std::endl;
   }
   static_cast< std::ofstream & >( (*Logger::getInstance().file_) ).close();
   Logger::getInstance().file_guard_.unlock();
}



Logger::~Logger() {

   flushBuffer( true );
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Implementation of the macros
//////////////////////////////////

namespace logger {
namespace impl {



void print_message( const std::string & msg ) {

   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][MESSAGE ]:   " << msg 
                         << Logger::nl << Logger::b_print;
}



void report_error( const std::string & msg, const std::string & file, int line ) {

   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][ERROR ]:   " << msg
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   Logger::getInstance() << Logger::b_write;
}



void catch_exception( std::exception & exc, const std::string & file, int line ) {

   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][EXCEPTION CAUGHT ]:   " << exc.what()
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   Logger::getInstance() << Logger::b_write;
}



void report_warning( const std::string & msg, const std::string & file, int line ) {

   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][WARNING ]:    " << msg
                         << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   #ifdef __SN_LOGLEVEL_WRITE_WARNINGS__
      Logger::getInstance() << Logger::b_write;
   #else
      Logger::getInstance() << Logger::b_print;
   #endif
}



void markEventHorizon() {
   Logger::getInstance().eventWatchRegionSwitch_ = ! Logger::getInstance().eventWatchRegionSwitch_;
}
void report_event( LogEventType event, const std::string & file, int line, const std::string & info ) {
   
   if( ! Logger::getInstance().eventWatchRegionSwitch_ )
      return;
   
   std::string event_tag;
   std::string descr;
   switch( event ) {
   case LogEventType::ResAlloc: event_tag = "RESOURCE ALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
   case LogEventType::ResDealloc: event_tag = "RESOURCE DEALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
   case LogEventType::OMPFork: event_tag = "OMP PARALLEL REGION ENTERED"; descr = "OpenMP fork occurred. "; break;
   case LogEventType::OMPJoin: event_tag = "OMP PARALLEL REGION EXITED";  descr = "OpenMP operation synchronized. "; break;
   case LogEventType::MPISend: event_tag = "MPI COMMUNICATION (SEND)"; descr = "An MPI_Send operation was completed successfully. "; break;
   case LogEventType::MPIRecv: event_tag = "MPI COMMUNICATION (RECV)"; descr = "An MPI_Recv operation was completed successfully. "; break;
   case LogEventType::MPIBCast: event_tag = "MPI COMMUNICATION (BCAST)"; descr = "An MPI_BCast operation was completed successfully. ";
   break;
   case LogEventType::Other: event_tag = "SPECIAL EVENT"; descr = "A special event has occurred.";
   default: event_tag = "UNKNOWN EVENT"; descr = "An unspecified event has ocurred"; break;
   };
   
   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][EVENT - " << event_tag << " ]:   " 
                         << descr << "   " << info << Logger::nl
                         << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   #ifdef __SN_LOGLEVEL_WRITE_EVENTS__
      Logger::getInstance() << Logger::b_write;
   #else
      Logger::getInstance() << Logger::b_print;
   #endif
}



void print_message_impl() {}
void watch_impl() {}

}   // namespace impl
}   // namespace logger

}   // namespace simpleNewton
