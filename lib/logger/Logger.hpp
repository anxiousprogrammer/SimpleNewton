#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iomanip>
#include <string>
#include <sstream>

#include <Types.hpp>
#include <core/ProcSingleton.hpp>

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: Simple logger library for the simpleNewton framework. Thread-safe I/O system, file writer, variable and event watcher.
*
|***************************************************************************************************************************************///+

// Some enumerators
enum class LogEventType  { ResAlloc = 0, ResDealloc, OMPFork, OMPJoin, MPISend, MPISsend, MPIIsend, MPIRecv, MPIIrecv, MPIBcast, 
                           MPIWait, MPIWaitAll, Other };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Light weight logger class
///////////////////////////////
   
class Logger {

public:
   
   ////////////////////////////////////
   ///   Output settings and assistance
   ////////////////////////////////////
   
   /* Dispensible logger instance - light and easy */
   static inline Logger createInstance() {
      return Logger();
   }
   
   /* Output characteristics */
   inline uint_t getFPPrecision()           { return buffer_.precision();                  }
   inline void setFPPrecision( uint_t pr)   { buffer_ << std::setprecision( pr );          }
   inline void fixFP()                      { buffer_ << std::fixed;                       }
   inline void unfixFP()                    { buffer_.unsetf( std::ios_base::floatfield ); }

public:

   /* Lifetime management which is possible from the outside: can be copied, moved and killed. */
   Logger( const Logger & ) = default;
   Logger( Logger && ) = default;
   ~Logger();
   
   ///////////////////////////
   ///   Primary functionality
   ///////////////////////////

public:   // INTERMEDIATE INTERFACE
   
   /* Buffering operator */
   template< typename INP_T >
   friend inline Logger & operator<<( Logger & lg, const INP_T & input ) {
   
      lg.buffer_ << input;
      return lg;
   }
   
   /* Print? Write? Both? Flush! */
   void flushBuffer( flag_t );
   
   /* Static member function: write process log to file */
   static void writeLog( const Logger & );
   

private:   // MEMBERS

   /* Trivial (primary) constructor is only accessible to the process' factory */
   Logger() = default;
   
   /* Buffer */
   std::stringstream buffer_ = std::stringstream( "" );
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Macros and helper functions
/////////////////////////////////

// Template function stays in header
namespace logger {
namespace impl {

void print_message( const std::string & );

void report_error( const std::string & , const std::string & , int );

void catch_exception( std::exception & , const std::string & , int );

void report_warning( const std::string & , const std::string & , int );

void markEventHorizon( const uint_t );

void report_L1_event( LogEventType , const std::string & , int , const std::string & );
void report_L2_event( const std::string & , int , const std::string & , const std::string & );

void watch_impl( Logger & );
template< class HEAD_PARAM, class... TAIL_PARAM >
void watch_impl( Logger & lg, const HEAD_PARAM & head, const TAIL_PARAM &... tail ) {

   lg << head << "   ";
   watch_impl( lg, tail... );   
}
template< class... PARAM >
void watch_variables( const std::string & msg, const std::string & file, int line, PARAM... arg ) {

   Logger lg( Logger::createInstance() );
   real_t time_point = ProcSingleton::getDurationFromStart();
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][VARIABLE WATCH ]:   " << "<Description>   " << msg << "   ";
   
   watch_impl( lg, arg... );
   
   lg << '\n' << ">--- From <" << file << " :" << line << " > ---<" << '\n';
   #ifdef __SN_LOGLEVEL_WRITE_WATCHES__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}

}   // namespace impl
}   // namespace logger



#define SN_LOG_MESSAGE( MSG ) \
do { \
      std::stringstream temporary_oss; \
      temporary_oss << MSG; \
      logger::impl::print_message( temporary_oss.str() ); } while(false)

#ifdef NDEBUG

 #define SN_LOG_REPORT_ERROR( MSG )
 #define SN_LOG_CATCH_EXCEPTION( EX )
 #define SN_LOG_REPORT_WARNING( MSG )
 #define SN_LOG_REPORT_L1_EVENT( EV, INFO )
 #define SN_LOG_REPORT_L2_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#else

   #ifdef __SN_LOGLEVEL_ERROR__
 
      #define SN_LOG_REPORT_ERROR( MSG ) \
      do { \
             std::stringstream temporary_oss; \
             temporary_oss << MSG; \
             logger::impl::report_error( temporary_oss.str(), std::string(__FILE__), __LINE__ ); } while(false)
  
      #define SN_LOG_CATCH_EXCEPTION( EX ) \
      do { logger::impl::catch_exception( EX, std::string(__FILE__), __LINE__ ); } while(false)
 
   #else
 
      #define SN_LOG_REPORT_ERROR( MSG )
      #define SN_LOG_CATCH_EXCEPTION( EX )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_WARNING__
 
      #define SN_LOG_REPORT_WARNING( MSG ) \
      do { \
             std::stringstream temporary_oss; \
             temporary_oss << MSG; \
             logger::impl::report_warning( temporary_oss.str(), std::string(__FILE__), __LINE__ ); } while(false)
 
   #else
 
      #define SN_LOG_REPORT_WARNING( MSG )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_WATCH__
 
      #define SN_LOG_WATCH_VARIABLES( MSG, ... ) \
      do { \
            std::stringstream temporary_oss; \
            temporary_oss << MSG; \
            logger::impl::watch_variables( temporary_oss.str(), std::string(__FILE__), __LINE__, __VA_ARGS__ ); } while(false)
 
   #else
 
      #define SN_LOG_WATCH_VARIABLES( MSG, ... )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_L1_EVENT__
 
      #define SN_LOG_L1_EVENT_WATCH_REGION_LIMIT() \
      do { logger::impl::markEventHorizon( 0 ); } while(false)
 
      #define SN_LOG_REPORT_L1_EVENT( EV, INFO ) \
      do { \
            std::stringstream temporary_oss; \
            temporary_oss << INFO; \
            logger::impl::report_L1_event( EV, std::string(__FILE__), __LINE__, temporary_oss.str() ); } while(false)
 
   #else
 
      #define SN_LOG_L1_EVENT_WATCH_REGION_LIMIT()
      #define SN_LOG_REPORT_L1_EVENT( EV, INFO )
  
   #endif
   
   #ifdef __SN_LOGLEVEL_L2_EVENT__
   
      #define SN_LOG_L2_EVENT_WATCH_REGION_LIMIT() \
      do { logger::impl::markEventHorizon( 1 ); } while(false)
 
      #define SN_LOG_REPORT_L2_EVENT( TAG, INFO ) \
      do { \
            std::stringstream temporary_oss_tag, temporary_oss_descr; \
            temporary_oss_tag << TAG; \
            temporary_oss_descr << INFO; \
            logger::impl::report_L2_event( std::string(__FILE__), __LINE__, temporary_oss_tag.str(), \
                                           temporary_oss_descr.str() ); } while(false)
 
   #else
 
      #define SN_LOG_L2_EVENT_WATCH_REGION_LIMIT()
      #define SN_LOG_REPORT_L2_EVENT( TAG, INFO )
  
   #endif

#endif

}   // namespace simpleNewton

#endif
