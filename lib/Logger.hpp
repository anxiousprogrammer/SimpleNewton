#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <memory>

#include <Types.hpp>

#include "BasicTypeTraits.hpp"
#include "TypeConstraints.hpp"
#include "BasicBases.hpp"

namespace simpleNewton {

// Level of the logging
#define __SN_LOGLEVEL_INACTIVE__   -1
#define __SN_LOGLEVEL_ERROR__      0
#define __SN_LOGLEVEL_WARNING__    1
#define __SN_LOGLEVEL_EVENT__      2
#define __SN_LOGLEVEL_WATCH__      3

#ifndef __SN_LOGLEVEL__
 #define __SN_LOGLEVEL__ 1
#endif

// Typelist of logger streams
using __SN_LIST_OF_LOGGER_STREAMS__ = SN_CT_TYPELIST< std::fstream, std::ofstream >;   // Flexibility of output (writing)

// Some enumerators
enum class LogEvent { ResAlloc = 0, ResDealloc, OMPFork, OMPJoin, MPISend, MPIRecv, MPIBCast };

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
   static Logger & getInstance();
   
   /* indicate the level of output */
   static inline uint_t writeLevel()  { return Logger::getInstance().writeLevel_; }
   
   /* Provide the output stream */
   template< class STREAM_T >
   static void writeSettings( const uint_t _writeLevel = __SN_LOGLEVEL_ERROR__ ) {
      SN_CT_REQUIRE< typetraits::is_derived_from_list_member< STREAM_T, __SN_LIST_OF_LOGGER_STREAMS__ >::value >();
      Logger::getInstance().file_ = std::unique_ptr< STREAM_T >( new STREAM_T() );
      Logger::getInstance().writeLevel_ = _writeLevel;
      Logger::getInstance().streamSet_ = true;
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
   
   /* Mutex for thread safety */
   std::mutex file_guard_;
   /* Stream to direct reports */
   std::unique_ptr< std::ostream > file_;
   /* Flags */
   flag_t streamSet_ = false;
   uint_t writeLevel_ = 1;
   /* Buffer */
   std::stringstream buffer_;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Macros which are a talked with the logger
///////////////////////////////////////////////


// Forward declarations of the implemented functions
void report_error( const char * msg, const char * const file, int line );
void report_event( LogEvent event, const char * const file, int line, 
                   const char * ptr_name, const char * res_type, const char * array_size );

template< class HEAD_PARAM, class... TAIL_PARAM >
void watch_impl( const HEAD_PARAM & head, const TAIL_PARAM &... tail ) {
   Logger::getInstance() << head << Logger::nl;
   watch_impl(tail...);
}
template< class... PARAM >
void watch_variables( const char * const msg, const char * const file, int line, PARAM... arg ) {
   Logger::getInstance() << "[LOGGER__>][VARIABLE WATCH ]:   " << "<Description>   " << msg << Logger::nl
                         << Logger::nl;
   watch_impl( arg... );
   Logger::getInstance() << ">--- From <" << file << " :" << line << " > ---<" << Logger::nl
                         << "==============================================================================================>" << Logger::nl;

   if( Logger::writeLevel() >= __SN_LOGLEVEL_WATCH__ )
      Logger::getInstance() << Logger::b_write;
   else
      Logger::getInstance() << Logger::b_end;
}

void report_warning( const char * msg, const char * const file, int line );

#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_INACTIVE__

 #define SN_LOG_REPORT_ERROR( MSG )
 #define SN_LOG_REPORT_EVENT( EV, PTR_NAME, TYPE, SIZE )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )
 #define SN_LOG_REPORT_WARNING( MSG )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_ERROR__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, PTR_NAME, TYPE, SIZE )
 #define SN_LOG_WATCH_VARIABLE( MSG, ... )
 #define SN_LOG_REPORT_WARNING( MSG )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_WARNING__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, PTR_NAME, TYPE, SIZE ) \
 do { report_event( EV, __FILE__, __LINE__, PTR_NAME, TYPE, SIZE ); } while(false)
 #define SN_LOG_WATCH_VARIABLE( MSG, ... ) \
 do { watch_variables( MSG, __FILE__, __LINE__, __VA_ARGS__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG ) \
 do { report_warning( MSG, __FILE__, __LINE__ ); } while(false)

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_EVENT__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, PTR_NAME, TYPE, SIZE ) \
 do { report_event( EV, __FILE__, __LINE__, PTR_NAME, TYPE, SIZE ); } while(false)
 #define SN_LOG_WATCH_VARIABLE( MSG, ... )
 #define SN_LOG_REPORT_WARNING( MSG )

#endif
#if __SN_LOGLEVEL__ == __SN_LOGLEVEL_WATCH__

 #define SN_LOG_REPORT_ERROR( MSG ) \
 do { report_error( MSG, __FILE__, __LINE__ ); } while(false)
 #define SN_LOG_REPORT_EVENT( EV, PTR_NAME, TYPE, SIZE ) \
 do { report_event( EV, __FILE__, __LINE__, PTR_NAME, TYPE, SIZE ); } while(false)
 #define SN_LOG_WATCH_VARIABLE( MSG, ... ) \
 do { watch_variables( MSG, __FILE__, __LINE__, __VA_ARGS__ ); } while(false)
 #define SN_LOG_REPORT_WARNING( MSG )

#endif

}   // namespace simpleNewton

#endif
