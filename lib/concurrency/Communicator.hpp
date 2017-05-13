#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#ifdef __SN_USE_MPI__

#include <mutex>

#include <Types.hpp>
#include <types/DTInfo.hpp>

#include <asserts/Asserts.hpp>
#include <types/BasicTypeTraits.hpp> 
#include <asserts/TypeConstraints.hpp>

#include <core/ProcSingleton.hpp>

#include <containers/mpi/OpenMPIBuffer.hpp>
#include <containers/mpi/MPIRequest.hpp>


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

class Communicator : public NonInstantiable, NonCopyable {

public:
   
   /* Operation: Send basic types */
   template< class TYPE_T >
   static void send( const OpenMPIBuffer<TYPE_T> & , int , MPISendMode = MPISendMode::Standard, 
                     MPIRequest<TYPE_T> & = MPIRequest<TYPE_T>()  );
   
   /* Operation: Receive basic types */
   template< typename TYPE_T >
   static void receive( OpenMPIBuffer<TYPE_T> & , int , int , MPIRecvMode = MPIRecvMode::Standard, 
                        MPIRequest<TYPE_T> & = MPIRequest<TYPE_T>() );
   
   /* Operation: Broadcast basic types */
   template< typename TYPE_T >
   static void broadcast( OpenMPIBuffer<TYPE_T> & , int , int );
   
   /* Wait for the immediate actions */
   template < typename TYPE_T >
   static void waitOnSend( MPIRequest<TYPE_T> & );

   template < typename TYPE_T >
   static void waitOnRecv( MPIRequest<TYPE_T> & );

   template < typename TYPE_T >
   static void waitAll( int , MPIRequest<TYPE_T> & );

};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Definitions of members
////////////////////////////

template< class TYPE_T >
void Communicator::send( const OpenMPIBuffer<TYPE_T> & buff, int target, MPISendMode smode, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value >();
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_POSITIVE( buff.getSize() );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   static int tag = 0;
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   // Decision making requires only 3 if-conditionals
   if( smode == MPISendMode::Standard ) {
    
      info = MPI_Send( buff, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD );
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISend, "[ " << types::DTInfo< TYPE_T >::mpi_name 
                                                     << ", " << std::to_string(buff.getSize()) << "], " 
                                                     << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target) );
   }
   else if( smode == MPISendMode::Synchronous ) {

      info = MPI_Ssend( buff, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD );
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISsend, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], "
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target) );
   }
   else if( smode == MPISendMode::Immediate ) {

      info = MPI_Isend( buff, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD, mpiR );
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIsend, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], " 
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   // Clear tags
   if( tag == __SN_MPI_LARGE_MESSAGE_COUNT__ ) {
      tag = 0;
      SN_LOG_REPORT_L1_EVENT( LogEventType::Other, "MPI tags were cleared. New tag for the next communication event set to zero." );
   }
}



// What goes up must come down.
template< typename TYPE_T >
void Communicator::receive( OpenMPIBuffer<TYPE_T> & buff, int size, int source, MPIRecvMode rmode, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value >();
   
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
   buff.resize( size );
   if( rmode == MPIRecvMode::Standard ) {

      info = MPI_Recv( buff, size, types::DTInfo< TYPE_T >::mpi_type, source, tag++, MPI_COMM_WORLD, &stat );
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIRecv, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                     << ", " << std::to_string(size) << " ], "
                                                     << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK()) );
      // Check status
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      #ifndef NDEBUG
      int count = 0; 
      MPI_Get_count( &stat, types::DTInfo< TYPE_T >::mpi_type, &count );
      #endif
      SN_ASSERT_EQUAL( count, size );
   }
   else if( rmode == MPIRecvMode::Immediate ) {
      
      mpiR.setTransferCount( size );
      info = MPI_Irecv( buff, size, types::DTInfo< TYPE_T >::mpi_type, source, tag++, MPI_COMM_WORLD, mpiR );
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIrecv, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(size) << " ], "
                                                      << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK()) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   // Clear tags
   if( tag == __SN_MPI_LARGE_MESSAGE_COUNT__ ) {
      tag = 0;
      SN_LOG_REPORT_L1_EVENT( LogEventType::Other, "MPI tags were cleared. New tag for the next communication event set to zero." );
   }
}



template< typename TYPE_T >
void Communicator::broadcast( OpenMPIBuffer<TYPE_T> & buff, int size, int source ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value >();
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   info = MPI_Bcast( buff, size, types::DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD );
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                   << ", " << std::to_string(size) << " ], "
                                                   << std::to_string(source) );
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
}



template < typename TYPE_T >
void Communicator::waitOnSend( MPIRequest<TYPE_T> & req ) {
   
   int info = -1;
   MPI_Status stat;
   
   // Make sure that the request hasn't been laid to rest already
   SN_ASSERT( req.getSize() == 1 );
   SN_ASSERT( *req != MPI_REQUEST_NULL);
   
   info = MPI_Wait( req, &stat );
   
   // Check status: Has every little bit of data arrived as expected?
   int actual_transfer_count = 0;
   MPI_Get_count( &stat, types::DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

   SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount() );
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( ISEND )" );
}
template < typename TYPE_T >
void Communicator::waitOnRecv( MPIRequest<TYPE_T> & req ) {
   
   int info = -1;
   MPI_Status stat;
   
   // Make sure that the request hasn't been laid to rest already
   SN_ASSERT( req.getSize() == 1 );
   SN_ASSERT( *req != MPI_REQUEST_NULL);
   
   info = MPI_Wait( req, &stat );
   
   // Check status: Has every little bit of data arrived as expected?
   int actual_transfer_count = 0;
   MPI_Get_count( &stat, types::DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

   SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount() );
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( IRECV )" );
}



template < typename TYPE_T >
void Communicator::waitAll( int count, MPIRequest< TYPE_T > & req ) {
   
   SN_ASSERT_EQUAL( count, req.getSize() );
   int info = -1;
   OpenMPIBuffer< MPI_Status > stat( count );
   
   info = MPI_Waitall( count, req, stat );
   
   // Check status
   for( int i=0; i<count; ++i ) {
  
      // Check status: Has every little bit of data arrived as expected?
      int actual_transfer_count = 0;
      MPI_Get_count( &stat[i], types::DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

      SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount(i) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWaitAll, "" );
}

}   // namespace simpleNewton

#endif   // __SN_USE_MPI__
#endif   // Header guard
