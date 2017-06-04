
#include "Logger.hpp"

#include <ctime>
#include <iostream>
#include <fstream>

#ifdef __SN_USE_STL_MULTITHREADING__
   #include <mutex>
#endif

#include <concurrency/OpenMP.hpp>

//==========================================================================================================================================
//
//  This file is part of simpleNewton. simpleNewton is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  simpleNewton is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with simpleNewton (see LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
//
///   Contains the implementation of Logger class.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace logger {
namespace internal {

bool eventWatchRegionSwitch_[] = { false, false };   // Here's a global!
bool consoleSwitch_ = true;                          // Here's another global!

}   // namespace internal
}   // namespace logger
#endif   // DOXYSKIP


/** The buffer must be flushed after streaming to ensure output.
*
*   \param _write   A flag which decides whether or not the buffer will be written to process' log file.
*/
void Logger::flushBuffer( flag_t _write ) {

   if( _write && ! buffer_.str().empty() )
      writeLog();
   
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex proc_cout_mutex;
   std::lock_guard< std::mutex > cout_lock( proc_cout_mutex );   // std::cout is also a shared, 'external' resource.
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   
   if( logger::internal::consoleSwitch_ )
      std::cout << buffer_.str() << std::endl;
   buffer_.str( std::string() );
   
   #ifdef __SN_USE_OPENMP__
   }
   #endif
}



/** This function writes the buffer to process' log file with name, "<executable_name>_log_on_proc<process_rank>".
*   Notes on exception safety: this function has a basic exception safety guarantee. It will throw IOError exceptions upon failure to 
*   open, write or close the log file.
*/
void Logger::writeLog() {
   
   static std::mutex proc_file_mutex;   // Looks like lazy initialization; mutex is shared resource.
   static std::ofstream file;           // owned by process, not threads.
   
   file.exceptions( std::ios_base::badbit );   // Exceptions to be thrown only for serious (non-logic) errors.
   
   #ifdef __SN_USE_STL_MULTITHREADING__
   std::lock_guard< std::mutex > file_lock( proc_file_mutex );   // Thread safety
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif

   time_t _now = time(nullptr);                                  // Time stamp
   
   try {
      file.open( ProcSingleton::getExecName() + "_log_on_proc" + std::to_string( SN_MPI_RANK() ), std::ios_base::app );
   }
   catch( const std::ios_base::failure & ex ) {
      
      if( logger::internal::consoleSwitch_ ) {
      
         real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
         fixFP(2);
         std::cerr << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK()
                   << "][FILE ERROR ]:   Could not open the log file for logger. A standard exception was caught. "
                   << "Type: std::ios_base::failure; string: " << ex.what()
                   << ". The program will continue but the buffer was not written to process' log file in this instance." << std::endl;
         unfixFP();
      }
      
      SN_THROW_IO_ERROR( "IO_Log_File_Open_Error" );
   }
   
   try {
      file << std::endl << ctime( &_now) << buffer_.str() << std::endl << std::endl;
   } 
   catch( const std::ios_base::failure & ex ) {
      
      if( logger::internal::consoleSwitch_ ) {
      
         real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
         fixFP(2);
         std::cerr << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK()
                   << "][EXCEPTION CAUGHT ]: A standard exception was caught during the writing of the log file. "
                   << "Type: std::ios_base::failure; string: " << ex.what()
                   << ". The program will continue but the buffer was not written to process' log file in this instance. "
                   << std::endl;
         unfixFP();
      }
      
      SN_THROW_IO_ERROR( "IO_Log_Write_To_File_Error" );
   }
   
   try {
      file.close();
   }
   catch( const std::ios_base::failure & ex ) {

      if( logger::internal::consoleSwitch_ ) {
         real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
         fixFP(2);
         std::cerr << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK()
                   << "][EXCEPTION CAUGHT ]: A standard exception was caught while closing the log file. "
                   << "Type: std::ios_base::failure; string: " << ex.what() << std::endl;
         unfixFP();
      }
      
      SN_THROW_IO_ERROR( "IO_Log_Close_File_Error" );
   }
   
   #ifdef __SN_USE_OPENMP__
   }
   #endif
}



/** The destructor flushes the buffer with an order to write to process' log file. */
Logger::~Logger() {

   flushBuffer( true );
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   MACRO function implementation
///////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace logger {
namespace internal {

void toggleConsole( bool _switch ) {
   consoleSwitch_ = _switch;
}

void print_message( const std::string & msg ) {

   Logger lg;
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][MESSAGE ]:   " << msg << '\n';
   lg.unfixFP();
   lg.flushBuffer( false );
}



void report_error( const std::string & msg, const std::string & file, int line, const std::string & func ) {

   Logger lg;
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][ERROR ]:   " << msg << '\n' 
      << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   lg.unfixFP();
   lg.flushBuffer( true );
}



void catch_exception( const std::exception & exc, const std::string & file, int line, const std::string & func ) {

   Logger lg;
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][EXCEPTION CAUGHT ]:   " << exc.what() << '\n'
      << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   lg.unfixFP();
   lg.flushBuffer( true );
}



void report_warning( const std::string & msg, const std::string & file, int line, const std::string & func ) {

   Logger lg;
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][WARNING ]:    " << msg << '\n'
      << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   lg.unfixFP();
      
   #ifdef __SN_LOGLEVEL_WRITE_WARNINGS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}



void markEventHorizon( const uint_t eventLevel ) {
   eventWatchRegionSwitch_[ eventLevel ] = ! eventWatchRegionSwitch_[ eventLevel ];
}
void report_L1_event( LogEventType event, const std::string & file, int line, const std::string & func, const std::string & info ) {
   
   if( ! eventWatchRegionSwitch_[0] )
      return;
   
   Logger lg;
   
   std::string event_tag = "N/A";
   std::string descr = "N/A";

   switch( event ) {
      case LogEventType::ResAlloc: event_tag = "HEAP RESOURCE ALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
         
      case LogEventType::ResDealloc: event_tag = "HEAP RESOURCE DEALLOCATED"; descr = "Pointer, Type, Size (in that order): "; break;
         
      case LogEventType::OMPFork: event_tag = "OMP PARALLEL REGION ENTERED"; descr = "OpenMP fork occurred. "; break;
         
      case LogEventType::OMPJoin: event_tag = "OMP PARALLEL REGION EXITED";  descr = "OpenMP operation synchronized. "; break;
      
      case LogEventType::ThreadFork: event_tag = "THREAD PARALLEL REGION ENTERED";  descr = "Thread task begun. "; break;
      
      case LogEventType::ThreadJoin: event_tag = "THREAD PARALLEL REGION EXITED";  descr = "Thread joined with master. "; break;
         
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
   
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][L1 EVENT - " << event_tag << " ]:   " 
      << descr << "   " << info << '\n' 
      << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   lg.unfixFP();
   
   #ifdef __SN_LOGLEVEL_WRITE_EVENTS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}
void report_L2_event( const std::string & file, int line, const std::string & func, const std::string & event_tag, 
                      const std::string & descr ) {
   
   if( ! eventWatchRegionSwitch_[1] )
      return;
   
   Logger lg;
   
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);
   lg.fixFP(2);
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][L2 EVENT - " << event_tag << " ]:   " 
      << descr << '\n' 
      << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   lg.unfixFP();
   
   #ifdef __SN_LOGLEVEL_WRITE_EVENTS__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}



void watch_impl( Logger & ) {}

}   // namespace internal
}   // namespace logger

#endif   //DOXYSKIP

}   // namespace simpleNewton
