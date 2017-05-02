#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <memory>
#include <ctime>
#include <chrono>

#include <Types.hpp>
#include <core/MPIManager.hpp>
#include <BasicBases.hpp>

namespace simpleNewton {

// Some enumerators
enum class LogEventType  { ResAlloc = 0, ResDealloc, OMPFork, OMPJoin, MPISend, MPIRecv, MPIBCast, Other };

/**||***************************************************************************************************************************************
*
*   Description: Simple logger library for the simpleNewton framework. Thread-safe I/O system, file writer, variable and event watcher.
*
|***************************************************************************************************************************************///+

// Forward declarations of functions for the macros
namespace logger {
namespace impl {

void print_message( const std::string & msg );

void report_error( const std::string & msg, const std::string & file, int line );

void catch_exception( std::exception & exc, const std::string & file, int line );

void report_warning( const std::string & msg, const std::string & file, int line );

void markEventHorizon();

void report_event( LogEventType event, const std::string & , int , const std::string & );

}   // namespace impl
}   // namespace logger



class Logger : private Singleton {
public:
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///   Logger management and access
   //////////////////////////////////
   
   /* instance */
   static inline Logger & getInstance() {
      static Logger single;
      return single;
   }
   
   /* Output characteristics */
   static inline uint_t getFPPrecision()           { return Logger::getInstance().buffer_.precision();                  }
   static inline void setFPPrecision( uint_t pr)   { Logger::getInstance().buffer_ << std::setprecision( pr );          }
   static inline void fixFP()                      { Logger::getInstance().buffer_ << std::fixed;                       }
   static inline void unfixFP()                    { Logger::getInstance().buffer_.unsetf( std::ios_base::floatfield ); }
   
   /* Timer comes with logger */
   static inline std::chrono::time_point< std::chrono::high_resolution_clock > getStartTime() { return Logger::getInstance().start_time_; }
   static inline std::chrono::time_point< std::chrono::high_resolution_clock > getCurrentTime() {
      return std::chrono::high_resolution_clock::now();
   }
   static inline real_t millisecondDuration( const std::chrono::time_point< std::chrono::high_resolution_clock > & t1,
                                             const std::chrono::time_point< std::chrono::high_resolution_clock > & t2 ) {
      return static_cast< real_t >(std::chrono::duration_cast< std::chrono::microseconds >(t2 - t1).count() * 0.001f);
   }
   static inline real_t microsecondDuration( const std::chrono::time_point< std::chrono::high_resolution_clock > & t1,
                                             const std::chrono::time_point< std::chrono::high_resolution_clock > & t2 ) {
      return static_cast< real_t >(std::chrono::duration_cast< std::chrono::microseconds >(t2 - t1).count());
   }
   
   /* Provide the output stream */
   template< class STREAM_T >
   static void writeSettings( int argc, char ** argv  ) {
   
      if( ! MPIManager::isInitialized() ) {
         std::cout << "[ERROR ]: The MPIManager was not initialized before setting up the Logger. The program will now exit." << std::endl;
         
         /////////////////
         ///   EXIT POINT!
         SN_EXIT();
         /////////////////
      }
      Logger::getInstance().file_ = std::unique_ptr< STREAM_T >( new STREAM_T() );
      Logger::getInstance().streamSet_ = true;
      
      if( argc >= 1 )   // Killing that -Wunused-parameter warning
         Logger::getInstance().exec_ = argv[0];
   }
   
   /* Event watching friends */
   friend void logger::impl::markEventHorizon();
   friend void logger::impl::report_event( LogEventType event, const std::string & , int , const std::string & );

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///   Primary functionality
   ///////////////////////////
   
   /* Buffer into the I/O scene */
   static constexpr char nl = '\n';
   struct flush_buffer {} static b_print;
   struct flush_buffer_and_write {} static b_write;
   template< class ENDER >
   static inline ENDER b_end( bool cond ) {
   
      if( cond )
         return b_write;
      return b_end;
   }
   
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
   bool eventWatchRegionSwitch_ = false;
   /* Buffer */
   std::stringstream buffer_;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Macros which are a talked with the logger
///////////////////////////////////////////////

// Template function stays in the header
namespace logger {
namespace impl {

void watch_impl();
template< class HEAD_PARAM, class... TAIL_PARAM >
void watch_impl( const HEAD_PARAM & head, const TAIL_PARAM &... tail ) {

   Logger::getInstance() << head << "   ";
   watch_impl(tail...);   
}
template< class... PARAM >
void watch_variables( const std::string & msg, const std::string & file, int line, PARAM... arg ) {

   auto timep = Logger::getCurrentTime();
   real_t point = Logger::millisecondDuration( Logger::getStartTime(), timep );
   Logger::getInstance() << "[" << point << " ms][LOGGER__>][P" << MPIManager::getCommRank() << "][VARIABLE WATCH ]:   " 
                         << "<Description>   " << msg << "   ";
   watch_impl( arg... );
   Logger::getInstance() << Logger::nl << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl;
   #ifdef __SN_LOGLEVEL_WRITE_WATCHES__
      Logger::getInstance() << Logger::b_write;
   #else
      Logger::getInstance() << Logger::b_print;
   #endif
}

}   // namespace impl
}   // namespace logger



#define SN_LOG_MESSAGE( MSG ) \
do { logger::impl::print_message( std::string(MSG) ); } while(false)

#ifdef NDEBUG

 #define SN_LOG_REPORT_ERROR( MSG )
 #define SN_LOG_CATCH_EXCEPTION( EX )
 #define SN_LOG_REPORT_WARNING( MSG )
 #define SN_LOG_REPORT_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#else

 #ifdef __SN_LOGLEVEL_ERROR__
  #define SN_LOG_REPORT_ERROR( MSG ) \
  do { logger::impl::report_error( std::string(MSG), std::string(__FILE__), __LINE__ ); } while(false)
  #define SN_LOG_CATCH_EXCEPTION( EX ) \
  do { logger::impl::catch_exception( EX, std::string(__FILE__), __LINE__ ); } while(false)
 #else
  #define SN_LOG_REPORT_ERROR( MSG )
  #define SN_LOG_CATCH_EXCEPTION( EX )
 #endif
 
 #ifdef __SN_LOGLEVEL_WARNING__
  #define SN_LOG_REPORT_WARNING( MSG ) \
  do { logger::impl::report_warning( std::string(MSG), std::string(__FILE__), __LINE__ ); } while(false)
 #else
  #define SN_LOG_REPORT_WARNING( MSG )
 #endif
 
 #ifdef __SN_LOGLEVEL_WATCH__
  #define SN_LOG_WATCH_VARIABLES( MSG, ... ) \
  do { logger::impl::watch_variables( std::string(MSG), std::string(__FILE__), __LINE__, __VA_ARGS__ ); } while(false)
 #else
  #define SN_LOG_WATCH_VARIABLES( MSG, ... )
 #endif
 
 #ifdef __SN_LOGLEVEL_EVENT__
  #define SN_LOG_EVENT_WATCH_REGION_LIMIT() \
  do { logger::impl::markEventHorizon(); } while(false)
  #define SN_LOG_REPORT_EVENT( EV, INFO ) \
  do { logger::impl::report_event( EV, std::string(__FILE__), __LINE__, std::string(INFO) ); } while(false)
 #else
  #define SN_LOG_EVENT_WATCH_REGION_LIMIT()
  #define SN_LOG_REPORT_EVENT( EV, INFO )
 #endif

#endif

}   // namespace simpleNewton

#endif
