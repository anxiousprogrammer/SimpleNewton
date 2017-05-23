#ifndef SN_BASECOMM_HPP
#define SN_BASECOMM_HPP

#include <mutex>

#include <Types.hpp>
#include <types/DTInfo.hpp>

#include <asserts/Asserts.hpp>
#include <types/BasicTypeTraits.hpp> 
#include <asserts/TypeConstraints.hpp>

#include <core/ProcSingleton.hpp>

#include <containers/mpi/OpenMPIBuffer.hpp>
#include <containers/mpi/MPIRequest.hpp>


/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

/** The count after which it is desired to reset the MPI tags. */
#define __SN_MPI_LARGE_MESSAGE_COUNT__   1000

//=========================================================================================================================================
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
///   Contains the class template BaseComm.
///   \file
///   \defgroup mpi MPI
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//=========================================================================================================================================

/** An enum which is used to select the type of MPI send operation: MPI_Send, MPI_Ssend or MPI_Isend */
enum class MPISendMode   { Standard, Synchronous, Immediate };

/** An enum which is used to select the type of MPI receive operation: MPI_Recv or MPI_Irecv */
enum class MPIRecvMode   { Standard, Immediate };

/** An enum which is used to select the type of MPI broadcast operation: MPI_Bcast or MPI_Ibcast */
enum class MPIBcastMode  { Standard, Immediate };

/** An enum which is used to specify on which operation it is to be waited: MPI_Isend, MPI_Irecv or MPI_Ibcast */
enum class MPIWaitOp     { Send, Receive, Broadcast };

//===CLASS==================================================================================================================================

/** An elementary message passing wrapper. It provides send, receive, broadcast, reduce, gather and scatter functionalities,
*   and their closely associated variations for any of thirteen, basic datatypes: char, unsigned char, short, unsigned short, 
*   int, unsigned int, long, unsigned long, long long, unsigned long long, float, double and bool.
*
*   \tparam TYPE_T   Data type which must necessarily be basic.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class BaseComm : public NonInstantiable {

public:
   
   /** Function to send basic data types from one process to another. */
   template< MPISendMode = MPISendMode::Standard >
   static void send( const OpenMPIBuffer<TYPE_T> & , int , MPIRequest<TYPE_T> & = {}  );
   
   /** Function to receive basic data types from one process to another. */
   template< MPIRecvMode = MPIRecvMode::Standard >
   static void receive( OpenMPIBuffer<TYPE_T> & , int , int, MPIRequest<TYPE_T> & = {} );
   
   /** Function to broadcast both the size as well as the contents of arrays of basic data types from one process to the others. */
   static void autoBroadcast( OpenMPIBuffer<TYPE_T> & , int );
   
   /** Function to broadcast basic data types from one process to the others. */
   template< MPIBcastMode = MPIBcastMode::Standard >
   static void broadcast( OpenMPIBuffer<TYPE_T> & , int , int , MPIRequest<TYPE_T> & = {} );
   
   /* Operation: Reduce basic types to buffer */
   /*template< TYPE_T >
   static void reduce( OpenMPIBuffer<TYPE_T> & , int );*/
   
   /** Function to wait for the completion of non-blocking MPI operations. */
   template < MPIWaitOp >
   static void wait( MPIRequest<TYPE_T> & );
   
   /** Function to wait for the completion of a given set of non-blocking MPI operations. */
   static void waitAll( int , MPIRequest< TYPE_T > & );
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of send function
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** The container OpenMPIBuffer is used to provide pointer access to the underlying array.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \tparam SMODE    Specifies if the send operation is to be of blocking, synchronous or non-blocking type.
*   \param buff      Array which makes up the contents of the message.
*   \param target    The rank of the receiving process.
*   \param mpiR      In case of non-blocking send operation, this container will be given important information which must be reclaimed by 
*                    the corresponding wait function. In case of non-blocking operations, this parameter will take on default value and 
*                    hence need not be specified.
*/
template< class TYPE_T >
template< MPISendMode SMODE >
void BaseComm<TYPE_T>::send( const OpenMPIBuffer<TYPE_T> & buff, int target, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_POSITIVE( buff.getSize() );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );

   #ifdef __SN_USE_MPI__
   
   static int tag = 0;
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   // Decision: the if-conditionals are evaluated at compile time.
   if( SMODE == MPISendMode::Standard ) {
      
      try {
         info = MPI_Send( buff.data_, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISend, "[ " << types::DTInfo< TYPE_T >::mpi_name 
                                                     << ", " << std::to_string(buff.getSize()) << "], " 
                                                     << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                     << " --tag" << std::to_string( tag ) );
   }
   else if( SMODE == MPISendMode::Synchronous ) {
      
      try {
         info = MPI_Ssend( buff.data_, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISsend, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], "
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                      << " --tag" << std::to_string( tag ) );
   }
   else if( SMODE == MPISendMode::Immediate ) {
      
      try {
         info = MPI_Isend( buff.data_, buff.getSize(), types::DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD, mpiR );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIsend, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], " 
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                      << " --tag" << std::to_string( tag ) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   // Clear tags
   if( tag == __SN_MPI_LARGE_MESSAGE_COUNT__ ) {
      tag = 0;
      SN_LOG_REPORT_L1_EVENT( LogEventType::Other, "MPI tags were cleared. New tag for the next communication event set to zero." );
   }
   
   #else
   (void)mpiR.getSize();   // Get rid of -Wunused
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of receive function
////////////////////////////////////

/** The container OpenMPIBuffer is used to provide pointer access to the underlying array.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \tparam RMODE    Specifies if the receive operation is to be of blocking, synchronous or non-blocking type.
*   \param buff      Array which shall receive the contents of the message.
*   \param size      Size of the incoming message.
*   \param source    The rank of the sending process.
*   \param mpiR      In case of non-blocking receive operation, this container will be given important information which must be reclaimed
*                    by the corresponding wait function. In case of non-blocking operations, this parameter will take on default value and
*                    hence need not be specified.
*/

template< typename TYPE_T >
template< MPIRecvMode RMODE >
void BaseComm<TYPE_T>::receive( OpenMPIBuffer<TYPE_T> & buff, int size, int source, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), source );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );

   /* Firstly resize the buffer */
   buff.resize( size );
   
   #ifdef __SN_USE_MPI__
   
   static int tag = 0;
   int info = -1;
   
   MPI_Status stat;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   // Decision: the if conditionals are evaluated at compile time
   if( RMODE == MPIRecvMode::Standard ) {
      
      try {
         info = MPI_Recv( buff.data_, size, types::DTInfo< TYPE_T >::mpi_type, source, tag++, MPI_COMM_WORLD, &stat );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIRecv, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                     << ", " << std::to_string(size) << " ], "
                                                     << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK())
                                                     << " --tag" << std::to_string( tag ) );
      // Check status
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      #ifndef NDEBUG
      int count = 0; 
      MPI_Get_count( &stat, types::DTInfo< TYPE_T >::mpi_type, &count );
      SN_ASSERT_EQUAL( count, size );
      #endif
   }
   else if( RMODE == MPIRecvMode::Immediate ) {
      
      mpiR.setTransferCount( size );
      try {
         info = MPI_Irecv( buff.data_, size, types::DTInfo< TYPE_T >::mpi_type, source, tag++, MPI_COMM_WORLD, mpiR );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIrecv, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(size) << " ], "
                                                      << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK())
                                                      << " --tag" << std::to_string( tag ) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   // Clear tags
   if( tag == __SN_MPI_LARGE_MESSAGE_COUNT__ ) {
      tag = 0;
      SN_LOG_REPORT_L1_EVENT( LogEventType::Other, "MPI tags were cleared. New tag for the next communication event set to zero." );
   }
   
   #else
   (void)mpiR.getSize();   // Getting rid of that -Wunused
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of automatic broadcast function
////////////////////////////////////////////////

/** The container OpenMPIBuffer is used to provide pointer access to the underlying array.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \param buff      Array which holds the contents of the message.
*   \param source    The rank of the broadcasting process.
*/

template< typename TYPE_T >
void BaseComm<TYPE_T>::autoBroadcast( OpenMPIBuffer<TYPE_T> & buff, int source ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   /* First, the broadcasting process broadcasts the size of the message */
   int size_msg = static_cast< int >( buff.getSize() );
   try {
      info = MPI_Bcast( &size_msg, 1, MPI_INT, source, MPI_COMM_WORLD );
   } catch( const std::exception & ex ) {
      SN_LOG_CATCH_EXCEPTION( ex );
   }

   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   info = -1;
   
   /* Receiving processes shall resize their containers suitably */
   SN_MPI_EXCEPT_PROC_REGION( source ) {
      buff.resize( static_cast< small_t >( size_msg ) );
   }
   
   /* Next, the actual message */
   try {
      info = MPI_Bcast( buff.data_, size_msg, types::DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD );
   } catch( const std::exception & ex ) {
      SN_LOG_CATCH_EXCEPTION( ex );
   }
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                   << ", " << std::to_string(size_msg) << " ], "
                                                   << std::to_string(source) );
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   #else
   (void)buff.getSize();   // No -Wunused
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of broadcast function
//////////////////////////////////////

/** The container OpenMPIBuffer is used to provide pointer access to the underlying array.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \tparam BCMODE   Specifies if the broadcast operation is to be of blocking or non-blocking type.
*   \param buff      Array which makes up the contents of the message.
*   \param size      Size of the message.
*   \param source    The rank of the broadcasting process.
*   \param mpiR      In case of non-blocking send operation, this container will be given important information which must be reclaimed by
*                    the corresponding wait function. In case of non-blocking operations, this parameter will take on default value and
*                    hence need not be specified.
*/

template< typename TYPE_T >
template< MPIBcastMode BCMODE >
void BaseComm<TYPE_T>::broadcast( OpenMPIBuffer<TYPE_T> & buff, int size, int source, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   /* Receiving processes shall resize their containers suitably */
   SN_MPI_EXCEPT_PROC_REGION( source ) {
      buff.resize( static_cast< small_t >( size ) );
   }
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   
   /* Thread safety is important */
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   
   /* Next, the actual message */
   if( BCMODE == MPIBcastMode::Standard ) {
      
      try {
         info = MPI_Bcast( buff.data_, size, types::DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(size) << " ], "
                                                      << std::to_string(source) );
   }
   else if( BCMODE == MPIBcastMode::Immediate ) {
      
      try {
         info = MPI_Ibcast( buff.data_, size, types::DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD, mpiR );
      } catch( const std::exception & ex ) {
         SN_LOG_CATCH_EXCEPTION( ex );
      }
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIbcast, "[ " << types::DTInfo< TYPE_T >::mpi_name
                                                       << ", " << std::to_string(size) << " ], "
                                                       << std::to_string(source) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   #else
   (void)mpiR.getSize();   // No -Wunused
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definitions of MPI_Wait functions
///////////////////////////////////////

/** This function derives from a template which specifies the exact operation, which in turn helps debugging greatly.
*
*   \tparam TYPE_T    Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \tparam WAIT_ON   Indicates for the completion of which MPI operation it is being waited.
*   \param req        Provides information required for the completion of the non-blocking operation for which it is being waited.
*/

template < typename TYPE_T >
template< MPIWaitOp WAIT_ON >
void BaseComm<TYPE_T>::wait( MPIRequest<TYPE_T> & req ) {
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   MPI_Status stat;
   
   // Make sure that the request hasn't been laid to rest already
   SN_ASSERT( req.getSize() == 1 );
   SN_ASSERT( *req != MPI_REQUEST_NULL);
   
   try {
      info = MPI_Wait( req, &stat );
   } catch( const std::exception & ex ) {
      SN_LOG_CATCH_EXCEPTION( ex );
   }
   
   // Check status: Has every little bit of data arrived as expected?
   int actual_transfer_count = 0;
   MPI_Get_count( &stat, types::DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

   SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount() );
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   if( WAIT_ON == MPIWaitOp::Send )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( ISEND )" );
   else if( WAIT_ON == MPIWaitOp::Receive )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( IRECV )" );
   else if( WAIT_ON == MPIWaitOp::Broadcast )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( IBCAST )" );
   
   #else
   (void)req.getSize();   // No -Wunused
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of MPI_Waitall function
////////////////////////////////////////

/** This function is used to wait on the completion of multiple, non-blocking operations all at once.
*
*   \tparam TYPE_T    Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \param count      The number of non-blocking operations.
*   \param req        Provides information required for the completion of the non-blocking operations for which it is being waited.
*/

template < typename TYPE_T >
void BaseComm<TYPE_T>::waitAll( int count, MPIRequest< TYPE_T > & req ) {
   
   SN_ASSERT_EQUAL( count, static_cast< int >( req.getSize() ) );
   
   if( SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   OpenMPIBuffer< MPI_Status > stat( count );
   
   try {
      info = MPI_Waitall( count, req, stat.data_ );
   } catch( const std::exception & ex ) {
      SN_LOG_CATCH_EXCEPTION( ex );
   }
   
   // Check status
   for( int i=0; i<count; ++i ) {
  
      // Check status: Has every little bit of data arrived as expected?
      int actual_transfer_count = 0;
      MPI_Get_count( &stat.data_[i], types::DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

      SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount(i) );
   }
   
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWaitAll, "" );
   
   #else
   (void)req.getSize();   // No -Wunused
   
   #endif   // MPI Guard
}


}   // namespace simpleNewton

#endif   // Header guard
