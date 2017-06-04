#ifndef SN_LOGGER_HPP
#define SN_LOGGER_HPP

#include <iomanip>
#include <string>
#include <sstream>

#include <core/ProcSingleton.hpp>
#include <Types.hpp>

#include <core/Exceptions.hpp>

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
///   Contains the class Logger along with essential macros which call multiple logging functions.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

/** An enumerator which helps specify the event type for level 1 (basic) event watching. */
enum class LogEventType  { ResAlloc = 0, ResDealloc, OMPFork, OMPJoin, ThreadFork, ThreadJoin, MPISend, MPISsend, MPIIsend, MPIRecv, 
                           MPIIrecv, MPIBcast, MPIIbcast, MPIWait, MPIWaitAll, Other };

//===CLASS==================================================================================================================================

/** This class serves as the primary logging tool for the simpleNewton framework. Its features can be listed as such - lightweight, thread- 
*   and basic exception safe.
*/
//==========================================================================================================================================
   
class Logger {

public:
   
   ///////////////////////////////
   //   Floating point formatting
   ///////////////////////////////
   
   /** \name Floating point output formatting
   *   @{
   */
   /** A function to get the number of decimal digits of a floating point value which shall be output by std::ostream.
   *
   *   \return   The output precision of floating point values.
   */
   inline uint_t getFPPrecision()                { return buffer_.precision();                                                      }
   
   /** A function to set the number of decimal digits of a floating point value which shall be output by std::ostream.
   *
   *   \param pr   The number of decimal digits to be displayed. Default value is 6.
   */
   inline void setFPPrecision( uint_t pr = 6 )   { buffer_ << std::setprecision( pr );                                              }
   
   /** A function to fix the number of decimal digits of a floating point value which shall be output by std::ostream.
   *
   *   \param pr   The number of decimal digits to be displayed. Default value is 6.
   */
   inline void fixFP( uint_t pr = 6 )            { buffer_ << std::setprecision( pr ); buffer_ << std::fixed;                       }
   
   /** A function to relax the restriction on the number of decimal digits of a floating point value which shall be output by std::ostream.
   *
   *   \param pr   The number of decimal digits to be displayed, depending on the value. Default value is 6.
   */
   inline void unfixFP( uint_t pr = 6 )          { buffer_.unsetf( std::ios_base::floatfield ); buffer_ << std::setprecision( pr ); }
   
   /** @} */
   
   //////////////////////////
   //   Lifecycle management
   //////////////////////////

   /** \name Constructors and destructor 
   *   @{
   */
   /** Default trivial constructor. */
   Logger() = default;

   /** Default copy constructor. */
   Logger( const Logger & ) = default;

   /** Default move constructor. */
   Logger( Logger && ) = default;
   
   /** Explicitly defined destructor. */
   ~Logger();
   
   /** @} */
   
   ///////////////////////////
   //   Primary functionality
   ///////////////////////////
   
   /** \name Primary functionality
   *   @{
   */
   /** Stream operator: Any kind of compatible input can be streamed into the buffer of the Logger. */
   template< typename INP_T >
   friend inline Logger & operator<<( Logger & , const INP_T & );
   
   /** A function which flushes the buffer and prints to screen. If necessary, a write to file will also be performed. */
   void flushBuffer( flag_t );
   
   /** A function which performs a write to file operation. */
   void writeLog();
   
   /** @} */

private:   // MEMBERS
   
   std::stringstream buffer_ = std::stringstream( "" );   ///< The Buffer.
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Friend: stream operator.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** The stream operator feeds variables to the buffer. The input's not being compatible with the logger causes compiler errors and 
*   therefore no special checking is performed.
*
*   \tparam INP_T   The type of the input variable. This will be deduced by the compiler.
*   \param lg       A reference to a Logger instance.
*   \param input    An input variable as prvalue.
*/
template< typename INP_T >
inline Logger & operator<<( Logger & lg, const INP_T & input ) {
   
   lg.buffer_ << input;
   return lg;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Macros and helper functions
/////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Template function stays in header
namespace logger {
namespace internal {

void toggleConsole( bool );

void print_message( const std::string & );

void report_error( const std::string & , const std::string & , int , const std::string & );

void catch_exception( const std::exception & , const std::string & , int , const std::string & );

void report_warning( const std::string & , const std::string & , int , const std::string & );

void markEventHorizon( const uint_t );

void report_L1_event( LogEventType , const std::string & , int , const std::string & , const std::string & );
void report_L2_event( const std::string & , int , const std::string & , const std::string & , const std::string & );

void watch_impl( Logger & );
template< class HEAD_PARAM, class... TAIL_PARAM >
void watch_impl( Logger & lg, const HEAD_PARAM & head, const TAIL_PARAM &... tail ) {

   lg << head << "   ";
   watch_impl( lg, tail... );   
}
template< class... PARAM >
void watch_variables( const std::string & msg, const std::string & file, int line, const std::string & func, PARAM... arg ) {

   Logger lg;
   real_t time_point = ProcSingleton::getDurationFromStart() * real_cast(1e+3);

   lg.fixFP( 2 );
   lg << "[" << time_point << " ms][LOGGER__>][P" << SN_MPI_RANK() << "][VARIABLE WATCH ]:   " << "<Description>   " << msg << "   ";
   lg.unfixFP();
   
   watch_impl( lg, arg... );
   
   lg << '\n' << ">--- From function, " << func << " <" << file << " :" << line << " > ---<" << '\n';
   #ifdef __SN_LOGLEVEL_WRITE_WATCHES__
      lg.flushBuffer( true );
   #else
      lg.flushBuffer( false );
   #endif
}

}   // namespace internal
}   // namespace logger
#endif   // DOXYSKIP



/** A function which switches off console display. */
#define SN_LOG_SWITCH_OFF_CONSOLE_OUTPUT() logger::internal::toggleConsole( 0 )

/** A function which switches on console display. */
#define SN_LOG_SWITCH_ON_CONSOLE_OUTPUT() logger::internal::toggleConsole( 1 )

/** A macro which prints a simple text message to screen.
*
*   \param MSG   The text message to be printed. Can be streamed.
*/
#define SN_LOG_MESSAGE( MSG ) \
do { \
      std::stringstream temporary_oss; \
      temporary_oss << MSG; \
      logger::internal::print_message( temporary_oss.str() ); } while(false)

#ifdef NDEBUG

 #define SN_LOG_REPORT_ERROR( MSG )
 #define SN_LOG_CATCH_EXCEPTION( EX )
 #define SN_LOG_REPORT_WARNING( MSG )
 #define SN_LOG_L1_EVENT_WATCH_REGION_LIMIT()
 #define SN_LOG_REPORT_L1_EVENT( EV, INFO )
 #define SN_LOG_L2_EVENT_WATCH_REGION_LIMIT()
 #define SN_LOG_REPORT_L2_EVENT( EV, INFO )
 #define SN_LOG_WATCH_VARIABLES( MSG, ... )

#else
   
   #ifdef __SN_LOGLEVEL_ERROR__
      
      /** A macro which prints an error message to screen if __SN_LOGLEVEL_ERROR__ has been defined by the make system. If this is the 
      *   case, the content of the message will also be written to the process' log file.
      *
      *   \param MSG   The error message to be printed. Can be streamed.
      */
      #define SN_LOG_REPORT_ERROR( MSG ) \
      do { \
             std::stringstream temporary_oss; \
             temporary_oss << MSG; \
             logger::internal::report_error( temporary_oss.str(), std::string(__FILE__), __LINE__, __func__ ); } while(false)
      
      /** A macro which prints an exceptional error message to screen if __SN_LOGLEVEL_ERROR__ has been defined by the make system. If this 
      *   is the case, the content of the message will also be written to the process' log file.
      *
      *   \param EX   A std::exception with details of the exceptional error.
      */
      #define SN_LOG_CATCH_EXCEPTION( EX ) \
      do { logger::internal::catch_exception( EX, std::string(__FILE__), __LINE__, __func__ ); } while(false)
 
   #else
 
      #define SN_LOG_REPORT_ERROR( MSG )
      #define SN_LOG_CATCH_EXCEPTION( EX )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_WARNING__
      
      /** A macro which prints a warning to screen if __SN_LOGLEVEL_WARNING__ has been defined by the make system. The content 
      *   of the message will be written to the process' log file if __SN_LOGLEVEL_WRITE_WARNINGS__ has also been defined.
      *
      *   \param MSG   The warning message to be printed. Can be streamed.
      */
      #define SN_LOG_REPORT_WARNING( MSG ) \
      do { \
             std::stringstream temporary_oss; \
             temporary_oss << MSG; \
             logger::internal::report_warning( temporary_oss.str(), std::string(__FILE__), __LINE__, __func__ ); } while(false)
 
   #else
 
      #define SN_LOG_REPORT_WARNING( MSG )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_WATCH__
      
      /** A macro which prints a brief description along with a set of variables, whose values it is desired to be observed, to screen if 
      *   __SN_LOGLEVEL_WATCH__ has been defined by the make system. The content of the message will be written to the process' log file if 
      *   __SN_LOGLEVEL_WRITE_WATCHES__ has also been defined.
      *
      *   The ellipsis operator captures the variables to be observed.
      *
      *   \param MSG   The error message to be printed. Can be streamed.
      */
      #define SN_LOG_WATCH_VARIABLES( MSG, ... ) \
      do { \
            std::stringstream temporary_oss; \
            temporary_oss << MSG; \
            logger::internal::watch_variables( temporary_oss.str(), std::string(__FILE__), __LINE__, __func__, __VA_ARGS__ ); } while(false)
 
   #else
 
      #define SN_LOG_WATCH_VARIABLES( MSG, ... )
 
   #endif
 
   #ifdef __SN_LOGLEVEL_L1_EVENT__
      
      /** A macro which declares the entry point of a level 1 Event Watch Region, in which event watching is enabled. L1 events declared 
      *   outside of this region are ignored. In this way, although numerous L1 event declarations may exist in different regions of the 
      *   code, only a single region can be closely watched. 
      *   
      *   Only one L1 Event Watch Region can be active. When multiple L1 Event Watch Regions have been declared, only the last one will
      *   effectively be active.
      */
      #define SN_LOG_L1_EVENT_WATCH_REGION_LIMIT() \
      do { logger::internal::markEventHorizon( 0 ); } while(false)
      
      /** A macro which declares the completion of any of the basic events listed by the enumeration, LogEventType. This prints a brief 
      *   description of the event to screen if __SN_LOGLEVEL_L1_EVENT__ has been defined by the make system. The content of the message 
      *   will be written to the process' log file if __SN_LOGLEVEL_WRITE_EVENTS__ has also been defined.
      *
      *   \param EV     The type of event to be declared.
      *   \param INFO   A brief, textual description of the event. This message needs to be aware of certain templates. ResAlloc and 
      *                 ResDealloc have the template, "Pointer, Type, Size (in that order): ". All MPI send and receive events follow 
      *                 the template, "Package, source, target (in that order): " and the MPI broadcast event follows, "Package, source (in 
      *                 that order): ". This argument can be streamed.
      */
      #define SN_LOG_REPORT_L1_EVENT( EV, INFO ) \
      do { \
            std::stringstream temporary_oss; \
            temporary_oss << INFO; \
            logger::internal::report_L1_event( EV, std::string(__FILE__), __LINE__, __func__, temporary_oss.str() ); } while(false)
 
   #else
 
      #define SN_LOG_L1_EVENT_WATCH_REGION_LIMIT()
      #define SN_LOG_REPORT_L1_EVENT( EV, INFO )
  
   #endif
   
   #ifdef __SN_LOGLEVEL_L2_EVENT__
      
      /** A macro which declares the entry point of a level 2 Event Watch Region, in which event watching is enabled. L2 events declared 
      *   outside of this region are ignored. In this way, although numerous L2 event declarations may exist in different regions of the 
      *   code, only a single region can be closely watched. 
      *   
      *   Only one L2 Event Watch Region can be active. When multiple L2 Event Watch Regions have been declared, only the last one will
      *   effectively be active.
      */
      #define SN_LOG_L2_EVENT_WATCH_REGION_LIMIT() \
      do { logger::internal::markEventHorizon( 1 ); } while(false)
      
      /** A macro which declares the completion of any high level event. This prints a brief description of the event to screen if 
      *   __SN_LOGLEVEL_L2_EVENT__ has been defined by the make system. The content of the message will be written to the process' log file 
      *   if __SN_LOGLEVEL_WRITE_EVENTS__ has also been defined.
      *
      *   \param TAG    The event tag, which is completely user-defined. Can be streamed.
      *   \param INFO   A brief, textual description of the event. Can be streamed.
      */
      #define SN_LOG_REPORT_L2_EVENT( TAG, INFO ) \
      do { \
            std::stringstream temporary_oss_tag, temporary_oss_descr; \
            temporary_oss_tag << TAG; \
            temporary_oss_descr << INFO; \
            logger::internal::report_L2_event( std::string(__FILE__), __LINE__, __func__, temporary_oss_tag.str(), \
                                               temporary_oss_descr.str() ); } while(false)
 
   #else
 
      #define SN_LOG_L2_EVENT_WATCH_REGION_LIMIT()
      #define SN_LOG_REPORT_L2_EVENT( TAG, INFO )
  
   #endif

#endif

}   // namespace simpleNewton

#endif
