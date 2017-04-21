#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <memory>
#include <ctime>
#include <chrono>

#include <Types.hpp>

#include <asserts/Asserts.hpp>
#include <asserts/TypeConstraints.hpp>
#include "BasicBases.hpp"

namespace simpleNewton {

// Level of the logging
#define __SN_LOGLEVEL_INACTIVE__   -1
#define __SN_LOGLEVEL_ERROR__      0
#define __SN_LOGLEVEL_WARNING__    1
#define __SN_LOGLEVEL_EVENT__      2
#define __SN_LOGLEVEL_WATCH__      3

#ifdef NDEBUG
 #define __SN_LOGLEVEL__ 0
#else
 #define __SN_LOGLEVEL__ 3
#endif

// Typelist of logger streams
using __SN_LIST_OF_LOGGER_STREAMS__ = SN_CT_TYPELIST< std::fstream, std::ofstream >;   // Flexibility of output (writing)

// Some enumerators
enum class LogEventType { ResAlloc = 0, ResDealloc, OMPFork, OMPJoin, MPISend, MPIRecv, MPIBCast };

/**||***************************************************************************************************************************************
*
*   Description: Simple logger library for the simpleNewton framework. Thread-safe I/O system, file writer, variable and event watcher.
*
|***************************************************************************************************************************************///+

class Logger : public NonCopyable {
public:
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///   Logger management and access
   //////////////////////////////////
   
   /* instance */
   static inline Logger & getInstance() {
      static Logger single;
      return single;
   }
   
   /* indicate the level of output */
   static inline uint_t writeLevel()  { return Logger::getInstance().writeLevel_; }
   
   /* get start time */
   static inline std::chrono::time_point< std::chrono::high_resolution_clock > getStartTime() { return Logger::getInstance().start_time_; }
   
   /* Provide the output stream */
   template< class STREAM_T >
   static void writeSettings( int argc, char ** argv, const uint_t _writeLevel = __SN_LOGLEVEL_ERROR__  ) {
      SN_CT_REQUIRE< typetraits::is_derived_from_list_member< STREAM_T, __SN_LIST_OF_LOGGER_STREAMS__ >::value >();
      Logger::getInstance().file_ = std::unique_ptr< STREAM_T >( new STREAM_T() );
      Logger::getInstance().writeLevel_ = _writeLevel;
      Logger::getInstance().streamSet_ = true;
      
      SN_REQUIRE_GREQ( argc, 1 );
      Logger::getInstance().exec_ = argv[0];
      time_t _now( time(nullptr) );
      std::cout << "========================================================================================================>" << std::endl;
      std::cout << "********************************************************************************************************" << std::endl
                << ">>>   Simple Newton framework running \'" << Logger::getInstance().exec_ 
                << "\' with start time: " << ctime( &_now ) << std::endl;
   }
   
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///   Primary functionality
   ///////////////////////////
   
   /* Buffer into the I/O scene */
   static constexpr char nl = '\n';
   struct flush_buffer {} static b_end;
   struct flush_buffer_and_write {} static b_write;
   
private:   // IMPLEMENTATION

   void flushBuffer( flag_t );

public:
   
   /* Buffering operator */
   template< typename INP_T >
   friend inline Logger & operator<<( Logger & lg, const INP_T & input ) {
      lg.buffer_ << input;
      return lg;
   }
   friend inline void operator<<( Logger & lg, const flush_buffer & ) {
      lg.flushBuffer( false );
   }
   friend inline void operator<<( Logger & lg, const flush_buffer_and_write & ) {
      lg.flushBuffer( true );
   }
   
   /* write log to file */
   static void writeLog();
   

private:   // MEMBERS

   /* Constructor is only accessible to the class itself - Meyer's singleton */
   Logger() = default;
   ~Logger();
   
   /* Name of the exec */
   std::string exec_ = "N/A";
   /* Mutex for thread safety */
   std::mutex file_guard_;
   /* Stream to direct reports */
   std::unique_ptr< std::ostream > file_;
   /* Timers */
   std::chrono::time_point< std::chrono::high_resolution_clock > start_time_ = std::chrono::high_resolution_clock::now();
   /* Flags */
   flag_t streamSet_ = false;
   uint_t writeLevel_ = 1;
   /* Buffer */
   std::stringstream buffer_;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Macros which are a talked with the logger
///////////////////////////////////////////////


// Forward declarations for the macros
namespace logger {
namespace impl {

void print_message( const char * msg );
void report_error( const char * msg, const char * const file, int line );
void report_warning( const char * msg, const char * const file, int line );
void report_event( LogEventType event, const char * const file, int line, const char * info = " " );

void watch_impl();
template< class HEAD_PARAM, class... TAIL_PARAM >
void watch_impl( const HEAD_PARAM & head, const TAIL_PARAM &... tail ) {
   Logger::getInstance() << head << Logger::nl;
   watch_impl(tail...);
}
template< class... PARAM >
void watch_variables( const char * const msg, const char * const file, int line, PARAM... arg ) {
   auto timep = std::chrono::high_resolution_clock::now();
   real_t point = std::chrono::duration_cast< std::chrono::microseconds >(timep - Logger::getStartTime()).count() * 0.001f;
   Logger::getInstance() << "[" << point << "][LOGGER__>][VARIABLE WATCH ]:   " << "<Description>   " << msg << Logger::nl
                         << Logger::nl;
   watch_impl( arg... );
   Logger::getInstance() << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   if( Logger::writeLevel() >= __SN_LOGLEVEL_WATCH__ )
      Logger::getInstance() << Logger::b_write;
   else
      Logger::getInstance() << Logger::b_end;
}

}   // namespace impl
}   // namespace logger

#define SN_LOG_MESSAGE( MSG ) \
do { logger::impl::print_message( MSG ); } while(false)

#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_INACTIVE__

 #define SN_LOG_REPORT_ERROR( MSG )
 #define SN_LOG_REPORT_WARNING( MSG )
 #define SN_LOG_REPORT_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_ERROR__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { logger::impl::report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG )
 #define SN_LOG_REPORT_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_WARNING__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { logger::impl::report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG ) \
 do { logger::impl::report_warning( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_EVENT__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { logger::impl::report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG ) \
 do { logger::impl::report_warning( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, INFO ) \
 do { logger::impl::report_event( EV, __FILE__, __LINE__, INFO ); } while(false)
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_WATCH__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { logger::impl::report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG ) \
 do { logger::impl::report_warning( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, INFO ) \
 do { logger::impl::report_event( EV, __FILE__, __LINE__, INFO ); } while(false)
 #define SN_LOG_WATCH_VARIABLES( MSG, ... ) \
 do { logger::impl::watch_variables( MSG, __FILE__, __LINE__, __VA_ARGS__ ); } while(false)
 
#endif

}   // namespace simpleNewton

#endif
