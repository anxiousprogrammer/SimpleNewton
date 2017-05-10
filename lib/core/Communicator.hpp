#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <mutex>

#include "ProcSingleton.hpp"

#include <asserts/Asserts.hpp>
#include <types/BasicTypeTraits.hpp> 
#include <asserts/TypeConstraints.hpp>

#include <Types.hpp>

#include <containers/OpenStringBuffer.hpp>


namespace simpleNewton {

#define __SN_MPI_LARGE_MESSAGE_COUNT__   1000

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

template< class TYPE >
struct Communicator_CPPHackClass {};

/**||**************************************************************************************************************************************
*
*   Description: MPI communication methods
*
|**************************************************************************************************************************************///+

enum class MPISendMode { Standard, Synchronous, Immediate };
enum class MPIRecvMode { Standard, Immediate };

class Communicator : public NonCopyable {

public:
   
   /* Operation: Send basic types */
   template< class TYPE_T >
   static void send( TYPE_T * , int , int , MPISendMode = MPISendMode::Standard, MPI_Request * = nullptr );
   static void send( const OpenStringBuffer & , int , MPISendMode = MPISendMode::Standard, MPI_Request * = nullptr );
   
   /* Operation: Receive basic types */
   template< typename TYPE_T >
   static void receive( TYPE_T * , int , int , MPIRecvMode = MPIRecvMode::Standard, MPI_Request * = nullptr );
   static void receive( OpenStringBuffer & , int , int , MPIRecvMode = MPIRecvMode::Standard, MPI_Request * = nullptr );
   
   /* Wait for the immediate actions */
   static void waitOnSend( MPI_Request * );
   static void waitOnRecv( MPI_Request * );
   static void waitAll( int , MPI_Request * );

private:
   
   /* Internal implementation for wait */
   static void wait( MPI_Request * );
   
   Communicator() = delete;
   ~Communicator() = delete;
   
   // IMPLEMENTATION
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Definitions of members
////////////////////////////

namespace communicator {
namespace impl {

// internal implementation to reduce the boilerplate effect
// caused by the combination of various MPI functions and datatypes

// Take care of type first
template< typename TYPE > struct MPIDT;

/* char */
template<> struct MPIDT< char & >          { static constexpr MPI_Datatype type = MPI_CHAR; static constexpr char str[] = "MPI_CHAR"; };
template<> struct MPIDT< unsigned char & > { static constexpr MPI_Datatype type = MPI_UNSIGNED_CHAR; 
                                             static constexpr char str[] = "MPI_UNSIGNED_CHAR"; };

/* short */
template<> struct MPIDT< short & >          { static constexpr MPI_Datatype type = MPI_SHORT; static constexpr char str[] = "MPI_SHORT"; };
template<> struct MPIDT< unsigned short & > { static constexpr MPI_Datatype type = MPI_UNSIGNED_SHORT; 
                                              static constexpr char str[] = "MPI_UNSIGNED_SHORT"; };
/* int */
template<> struct MPIDT< int & >          { static constexpr MPI_Datatype type = MPI_INT; static constexpr char str[] = "MPI_INT"; };
template<> struct MPIDT< unsigned int & > { static constexpr MPI_Datatype type = MPI_UNSIGNED; 
                                            static constexpr char str[] = "MPI_UNSIGNED"; };

/* long */
template<> struct MPIDT< long & >          { static constexpr MPI_Datatype type = MPI_LONG; static constexpr char str[] = "MPI_LONG"; };
template<> struct MPIDT< unsigned long & > { static constexpr MPI_Datatype type = MPI_UNSIGNED_LONG; 
                                             static constexpr char str[] = "MPI_UNSIGNED_LONG"; };

/* long long */
template<> struct MPIDT< long long & >          { static constexpr MPI_Datatype type = MPI_LONG_LONG; 
                                                  static constexpr char str[] = "MPI_LONG_LONG"; };
template<> struct MPIDT< unsigned long long & > { static constexpr MPI_Datatype type = MPI_UNSIGNED_LONG_LONG; 
                                                  static constexpr char str[] = "MPI_UNSIGNED_LONG_LONG"; };

/* floating point */
template<> struct MPIDT< float & >  { static constexpr MPI_Datatype type = MPI_FLOAT; static constexpr char str[] = "MPI_FLOAT"; };
template<> struct MPIDT< double & > { static constexpr MPI_Datatype type = MPI_DOUBLE; static constexpr char str[] = "MPI_DOUBLE"; };

}   // namespace impl
}   // namespace communicator



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Definitions of members
////////////////////////////

template< class TYPE_T >
void Communicator::send( TYPE_T * ptr, int size, int target, MPISendMode smode, MPI_Request * mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value || typetraits::is_array_of_basic_datatype<TYPE_T>::value >();
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   static int tag = 0;
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   // Decision making requires only 3 if-conditionals
   if( smode == MPISendMode::Standard ) {
    
      info = MPI_Send( ptr, size, communicator::impl::MPIDT< decltype(*ptr) >::type, target, tag++, MPI_COMM_WORLD );
      SN_LOG_REPORT_EVENT( LogEventType::MPISend, string_cast("[ " ) + string_cast(communicator::impl::MPIDT< decltype(*ptr) >::str) + 
                                                  string_cast(", ") + std::to_string(size) + string_cast("], ") + 
                                                  std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   else if( smode == MPISendMode::Synchronous ) {

      info = MPI_Ssend( ptr, size, communicator::impl::MPIDT< decltype(*ptr) >::type, target, tag++, MPI_COMM_WORLD );
      SN_LOG_REPORT_EVENT( LogEventType::MPISsend, string_cast("[ " ) + string_cast(communicator::impl::MPIDT< decltype(*ptr) >::str) + 
                                                  string_cast(", ") + std::to_string(size) + string_cast("], ") + 
                                                  std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   else if( smode == MPISendMode::Immediate ) {

      info = MPI_Isend( ptr, size, communicator::impl::MPIDT< decltype(*ptr) >::type, target, tag++, MPI_COMM_WORLD, mpiR );
      SN_LOG_REPORT_EVENT( LogEventType::MPIIsend, string_cast("[ " ) + string_cast(communicator::impl::MPIDT< decltype(*ptr) >::str) + 
                                                  string_cast(", ") + std::to_string(size) + string_cast("], ") + 
                                                  std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI send operation. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
   
   // Clear tags
   if( tag == __SN_MPI_LARGE_MESSAGE_COUNT__ ) {
      tag = 0;
      SN_LOG_REPORT_EVENT( LogEventType::Other, "MPI tags were cleared. New tag for the next communication event set to zero." );
   }
}



// General send operation: Specialization for stringondrix
void Communicator::send( const OpenStringBuffer & str, int target, MPISendMode smode, MPI_Request * mpiR ) {

   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   static int tag = 0;
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   if( smode == MPISendMode::Standard ) {
    
      info = MPI_Send( str, str.getSize(), MPI_CHAR, target, tag++, MPI_COMM_WORLD );
      SN_LOG_REPORT_EVENT( LogEventType::MPISend, string_cast("[ std::string, " ) + std::to_string(str.getSize()) + string_cast(" ], ") + 
                                                  std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   else if( smode == MPISendMode::Synchronous ) {
    
      info = MPI_Ssend( str, str.getSize(), MPI_CHAR, target, tag++, MPI_COMM_WORLD );
      SN_LOG_REPORT_EVENT( LogEventType::MPISsend, string_cast("[ std::string, " ) + std::to_string(str.getSize()) + string_cast(" ], ") + 
                                                   std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   else if( smode == MPISendMode::Immediate ) {

      info = MPI_Isend( str, str.getSize(), MPI_CHAR, target, tag++, MPI_COMM_WORLD, mpiR );
      SN_LOG_REPORT_EVENT( LogEventType::MPIIsend, string_cast("[ std::string, " ) + std::to_string(str.getSize()) + string_cast(" ], ") + 
                                                   std::to_string(SN_MPI_RANK()) + string_cast(", ") + std::to_string(target) );
   }
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI send operation. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
   
   if( tag == 1000 ) {
      tag = 0;
   }
}



// What goes up must come down.
template< typename TYPE_T >
void Communicator::receive( TYPE_T * ptr, int size, int source, MPIRecvMode rmode, MPI_Request * mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value || typetraits::is_array_of_basic_datatype<TYPE_T>::value >();
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), source );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );

   static int tag = 0;
   int info = -1;
   MPI_Status stat;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   // Decision: total if-conditional cost reduced to three or four.
   if( rmode == MPIRecvMode::Standard ) {

      info = MPI_Recv( ptr, size, communicator::impl::MPIDT< decltype(*ptr) >::type, source, tag++, MPI_COMM_WORLD, &stat );
      SN_LOG_REPORT_EVENT( LogEventType::MPIRecv, string_cast("[ ") + string_cast(communicator::impl::MPIDT< decltype(*ptr) >::str) + 
                                                  string_cast(", ") + std::to_string(size) + string_cast(" ], ") + 
                                                  std::to_string(source) + string_cast(", ") + std::to_string(SN_MPI_RANK()) );
      // Check status
      SN_ASSERT( ! stat.MPI_ERROR );
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      #ifndef NDEBUG
      int count = 0; 
      MPI_Get_count( &stat, communicator::impl::MPIDT< decltype(*ptr) >::type, &count );
      #endif
      SN_ASSERT_EQUAL( count, size );
   }
   else if( rmode == MPIRecvMode::Immediate ) {

      info = MPI_Irecv( ptr, size, communicator::impl::MPIDT< decltype(*ptr) >::type, source, tag++, MPI_COMM_WORLD, mpiR );
      SN_LOG_REPORT_EVENT( LogEventType::MPIIrecv, string_cast("[ ") + string_cast(communicator::impl::MPIDT< decltype(*ptr) >::str) + 
                                                  string_cast(", ") + std::to_string(size) + string_cast(" ], ") + 
                                                  std::to_string(source) + string_cast(", ") + std::to_string(SN_MPI_RANK()) );
   }
   
   if( info != MPI_SUCCESS ) {
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI receive operation. The program will now exit." );
      
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
  
   if( tag == 1000 ) {
      tag = 0;
   }
}



// General receive operation: Specialization for stringondrix
void Communicator::receive( OpenStringBuffer & str, int size, int source, MPIRecvMode rmode, MPI_Request * mpiR ) {

   SN_ASSERT_INEQUAL( SN_MPI_RANK(), source );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );

   static int tag = 0;
   int info = -1;
   MPI_Status stat;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   /* Resize buffer before letting the data flood in */
   str.resize( size );
   if( rmode == MPIRecvMode::Standard ) {

      info = MPI_Recv( str, size, MPI_CHAR, source, tag++, MPI_COMM_WORLD, &stat );
      SN_LOG_REPORT_EVENT( LogEventType::MPIRecv, string_cast("[ std::string, ") + std::to_string(size) + 
                                                  string_cast(" ], ") + std::to_string(source) + string_cast(", ") +
                                                  std::to_string(SN_MPI_RANK()) );
      // Check status
      SN_ASSERT( ! stat.MPI_ERROR );
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      #ifndef NDEBUG
      int count = 0; 
      MPI_Get_count( &stat, MPI_CHAR, &count );
      #endif
      SN_ASSERT_EQUAL( count, size );
   }
   else if( rmode == MPIRecvMode::Immediate ) {

      info = MPI_Irecv( str, size, MPI_CHAR, source, tag++, MPI_COMM_WORLD, mpiR );
      SN_LOG_REPORT_EVENT( LogEventType::MPIIrecv, string_cast("[ std::string, ") + std::to_string(size) + 
                                                   string_cast(" ], ") + std::to_string(source) + string_cast(", ") +
                                                   std::to_string(SN_MPI_RANK()) );
   }
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI receive operation. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
   
   if( tag == 1000 ) {
      tag = 0;
   }
}



void Communicator::waitOnSend( MPI_Request * req ) {
   
   wait( req );
   SN_LOG_REPORT_EVENT( LogEventType::MPIWait, "( ISEND )" );
}
void Communicator::waitOnRecv( MPI_Request * req ) {
   
   wait( req );
   SN_LOG_REPORT_EVENT( LogEventType::MPIWait, "( IRECV )" );
}
void Communicator::wait( MPI_Request * req ) {
   
   int info = -1;
   MPI_Status stat;
   
   // Make sure that the request hasn't been laid to rest already
   SN_ASSERT( *req != MPI_REQUEST_NULL);
   
   info = MPI_Wait( req, &stat );
   
   // Check status
   SN_ASSERT( ! stat.MPI_ERROR );
   SN_ASSERT( *req == MPI_REQUEST_NULL);
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to wait on an MPI operation. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
}



void Communicator::waitAll( int count, MPI_Request * req ) {
   
   int info = -1;
   DArray< MPI_Status > stat( count );
   
   info = MPI_Waitall( count, req, stat );
   
   // Check status
   for( int i=0; i<count; ++i ) {

      SN_ASSERT( ! stat[i].MPI_ERROR );
   }
   SN_ASSERT( *req == MPI_REQUEST_NULL);
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to wait on a set of MPI operations. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      ProcSingleton::ExitProgram();
      /////////////////
   }
   SN_LOG_REPORT_EVENT( LogEventType::MPIWaitAll, "" );
}

}   // namespace simpleNewton

#endif
