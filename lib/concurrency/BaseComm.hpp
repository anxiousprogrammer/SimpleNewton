#ifndef SN_BASECOMM_HPP
#define SN_BASECOMM_HPP

#ifdef __SN_USE_STL_MULTITHREADING__
   #include <mutex>
#endif

#include <Types.hpp>
#include <types/DTInfo.hpp>

#include <asserts/Asserts.hpp>
#include <types/BasicTypeTraits.hpp> 
#include <asserts/TypeConstraints.hpp>

#include "OpenMP.hpp"

#include <core/ProcSingleton.hpp>
#include <core/Exceptions.hpp>

#include <containers/mpi/FastBuffer.hpp>
#include <containers/mpi/MPIRequest.hpp>

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

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

/** An enum which is used to select the type of MPI send operation: MPI_Send, MPI_Ssend or MPI_Isend */
enum class MPISendMode   { Standard, Synchronous, Immediate };

/** An enum which is used to select the type of MPI receive operation: MPI_Recv or MPI_Irecv */
enum class MPIRecvMode   { Standard, Immediate };

/** An enum which is used to select the type of MPI broadcast operation: MPI_Bcast or MPI_Ibcast */
enum class MPIBcastMode  { Standard, Immediate };

/** An enum which is used to specify on which operation it is to be waited: MPI_Isend, MPI_Irecv or MPI_Ibcast */
enum class MPIWaitOp     { Send, Receive, Broadcast };

//===CLASS==================================================================================================================================

/** An elementary message passing wrapper. It provides send, auto-send, receive, broadcast, auto-broadcast, reduce, gather and scatter 
*   functionalities, and their closely associated variations (synchronous/non-blocking) for any of thirteen, basic datatypes: char, 
*   unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double and bool.
*
*   \tparam TYPE_T   Data type which must necessarily be basic.
*/
//==========================================================================================================================================

template< typename TYPE_T >
class BaseComm : public NonInstantiable {

public:
   
   /** Function to send both the size as well as the contents of an array of basic data type from one process to another. */
   static void autoSend( const FastBuffer<TYPE_T> & , FastBuffer<TYPE_T> & , int , int );
   
   /** Function to send basic data types from one process to another. */
   template< MPISendMode = MPISendMode::Standard >
   static void send( const FastBuffer<TYPE_T> & , int , MPIRequest<TYPE_T> & = {} );
   
   /** Function to receive basic data types from one process to another. */
   template< MPIRecvMode = MPIRecvMode::Standard >
   static void receive( FastBuffer<TYPE_T> & , int , int, MPIRequest<TYPE_T> & = {} );
   
   /** Function to broadcast both the size as well as the contents of an array of basic data type from one process to the others. */
   static void autoBroadcast( FastBuffer<TYPE_T> & , int );
   
   /** Function to broadcast basic data types from one process to the others. */
   template< MPIBcastMode = MPIBcastMode::Standard >
   static void broadcast( FastBuffer<TYPE_T> & , int , int , MPIRequest<TYPE_T> & = {} );
   
   /* Operation: Reduce basic types to buffer */
   /*template< TYPE_T >
   static void reduce( FastBuffer<TYPE_T> & , int );*/
   
   /** Function to wait for the completion of non-blocking MPI operations. */
   template < MPIWaitOp >
   static void wait( MPIRequest<TYPE_T> & );
   
   /** Function to wait for the completion of a given set of non-blocking MPI operations. */
   static void waitAll( int , MPIRequest< TYPE_T > & );
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of send function
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument exception is thrown if the arguments are not logical. An MPIError exception is thrown if the return code 
*   of the MPI send operation is not MPI_SUCCESS.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \param sbuff     Array which contains the message to be sent.
*   \param rbuff     Array which will receive the message.
*   \param source    The rank of the sending process.
*   \param target    The rank of the receiving process.
*/
template< class TYPE_T >
void BaseComm<TYPE_T>::autoSend( const FastBuffer<TYPE_T> & sbuff, FastBuffer<TYPE_T> & rbuff, int source, int target ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();   // Free template input prerequires a Türsteher.
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)sbuff.getSize();
   (void)rbuff.getSize();
   (void)source;
   (void)target;
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {      // Running with MPI but only 1 proc
      return;
   }
   
   // Assertions
   SN_ASSERT_POSITIVE( sbuff.size_ );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   
   #ifdef __SN_USE_MPI__   // MPI Guard
   
   #ifdef NDEBUG
   if( sbuff.size_ <= 0 || target < 0 || target >= SN_MPI_SIZE() || source < 0 || source >= SN_MPI_SIZE() ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_Send" );
   }
   #endif
   
   int tag = source + target;
   int info = -1;
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   SN_MPI_PROC_REGION( source ) {

      // Sendd the contents of sbuff right away!
      info = MPI_Send( sbuff.data_, sbuff.size_, DTInfo< TYPE_T >::mpi_type, target, tag, MPI_COMM_WORLD );
   
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Send_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISend, "[ " << DTInfo< TYPE_T >::mpi_name
                                                     << ", " << std::to_string( sbuff.size_ ) << " ], "
                                                     << std::to_string( source ) << ", " << std::to_string( target )
                                                     << " --tag" << std::to_string( tag ) );
   }
   
   SN_MPI_PROC_REGION( target ) {
      
      int recv_size = 0;
      MPI_Status stat;
      
      // Probe for size
      info = MPI_Probe( source, tag, MPI_COMM_WORLD, &stat );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Send_Error" );
      }
      #endif
      
      // Get the size
      MPI_Get_count( &stat, DTInfo< TYPE_T >::mpi_type, &recv_size );
      
      // Resize receiving container.
      rbuff.resize( recv_size );
      
      // Now receive the whole thing.
      info = MPI_Recv( rbuff.data_, recv_size, DTInfo< TYPE_T >::mpi_type, source, MPI_ANY_TAG, MPI_COMM_WORLD, 
                       &stat );
      
      // Check status - count
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      
      int count = 0;
      MPI_Get_count( &stat, DTInfo< TYPE_T >::mpi_type, &count );
      SN_ASSERT_EQUAL( count, recv_size );
      
      #ifdef NDEBUG
      if( count != recv_size ) {
         SN_THROW_MPI_ERROR( "MPI_Recv_Count_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIRecv, "[ " << DTInfo< TYPE_T >::mpi_name
                                                     << ", " << std::to_string( recv_size ) << " ], "
                                                     << std::to_string( source ) << ", " << std::to_string( target ) );
   }
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument exception is thrown if the arguments are not logical. An MPIError exception is thrown if the return code 
*   of the MPI send operation is not MPI_SUCCESS.
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
void BaseComm<TYPE_T>::send( const FastBuffer<TYPE_T> & buff, int target, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();   // Free template input prerequires a Türsteher.
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)buff.getSize();
   (void)mpiR.getSize();
   (void)target;
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {      // Running with MPI but only 1 proc
      return;
   }
   
   // Assertions
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_POSITIVE( buff.getSize() );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   #ifdef NDEBUG
   if( target == SN_MPI_RANK() || buff.getSize() <= 0 || target < 0 || target >= SN_MPI_SIZE() ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_Send" );
   }
   #endif


   #ifdef __SN_USE_MPI__   // MPI Guard
   
   int tag = SN_MPI_RANK() + target;
   int info = -1;
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   // Decision: the if-conditionals are evaluated at compile time.
   if( SMODE == MPISendMode::Standard ) {
      
      info = MPI_Send( buff.data_, buff.getSize(), DTInfo< TYPE_T >::mpi_type, target, tag, MPI_COMM_WORLD );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Send_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISend, "[ " << DTInfo< TYPE_T >::mpi_name 
                                                     << ", " << std::to_string(buff.getSize()) << "], " 
                                                     << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                     << " --tag" << std::to_string( tag ) );
   }
   else if( SMODE == MPISendMode::Synchronous ) {
      
      info = MPI_Ssend( buff.data_, buff.getSize(), DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Ssend_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPISsend, "[ " << DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], "
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                      << " --tag" << std::to_string( tag ) );
   }
   else if( SMODE == MPISendMode::Immediate ) {
      
      info = MPI_Isend( buff.data_, buff.getSize(), DTInfo< TYPE_T >::mpi_type, target, tag++, MPI_COMM_WORLD, 
                        mpiR );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Isend_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIsend, "[ " << DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(buff.getSize()) << "], " 
                                                      << std::to_string(SN_MPI_RANK()) << ", " << std::to_string(target)
                                                      << " --tag" << std::to_string( tag - 1 ) );
   }
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of receive function
////////////////////////////////////

/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument exception is thrown if the arguments are not logical. An MPIError exception is thrown if the return code 
*   of the operation is not MPI_SUCCESS or if the transfer count doesn't match the size provided (in case of blocking send).
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
void BaseComm<TYPE_T>::receive( FastBuffer<TYPE_T> & buff, int size, int source, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();   // Free template input prerequires a Türsteher.
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)buff.getSize();
   (void)mpiR.getSize();
   (void)source;
   (void)size;
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), source );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   #ifdef NDEBUG
   if( source == SN_MPI_RANK() || size <= 0 || source < 0 || source >= SN_MPI_SIZE() ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_Recv" );
   }
   #endif

   /* Firstly resize the buffer */
   buff.resize( size );
   
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   
   MPI_Status stat;
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   // Decision: the if conditionals are evaluated at compile time
   if( RMODE == MPIRecvMode::Standard ) {
      
      info = MPI_Recv( buff.data_, size, DTInfo< TYPE_T >::mpi_type, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat );
      
      // Run-time error checking - success
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Recv_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIRecv, "[ " << DTInfo< TYPE_T >::mpi_name
                                                     << ", " << std::to_string(size) << " ], "
                                                     << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK()) );
      // Check status - count
      SN_ASSERT_EQUAL( stat.MPI_SOURCE, source );
      
      int count = 0; 
      MPI_Get_count( &stat, DTInfo< TYPE_T >::mpi_type, &count );
      
      SN_ASSERT_EQUAL( count, size );
      
      #ifdef NDEBUG
      if( count != size ) {
         SN_THROW_MPI_ERROR( "MPI_Recv_Count_Error" );
      }
      #endif
   }
   else if( RMODE == MPIRecvMode::Immediate ) {
      
      mpiR.setTransferCount( size );
      
      info = MPI_Irecv( buff.data_, size, DTInfo< TYPE_T >::mpi_type, source, MPI_ANY_TAG, MPI_COMM_WORLD, mpiR );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Irecv_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIrecv, "[ " << DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(size) << " ], "
                                                      << std::to_string(source) << ", " << std::to_string(SN_MPI_RANK()) );
   }
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of automatic broadcast function
////////////////////////////////////////////////

/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An MPIError exception is thrown if the return code of the operation is not MPI_SUCCESS.
*
*   \tparam TYPE_T   Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \param buff      Array which holds the contents of the message.
*   \param source    The rank of the broadcasting process.
*/

template< typename TYPE_T >
void BaseComm<TYPE_T>::autoBroadcast( FastBuffer<TYPE_T> & buff, int source ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();   // Free template input prerequires a Türsteher.
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)buff.getSize();
   (void)source;
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   #ifdef NDEBUG
   if( source < 0 || source > SN_MPI_SIZE() ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_autoBcast" );
   }
   #endif
   
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   /* First, the broadcasting process broadcasts the size of the message */
   int size_msg = static_cast< int >( buff.getSize() );
   info = MPI_Bcast( &size_msg, 1, MPI_INT, source, MPI_COMM_WORLD );
   
   // Run-time error checking
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   #ifdef NDEBUG
   if( info != MPI_SUCCESS ) {
      SN_THROW_MPI_ERROR( "MPI_AutoBcast1_Error" );
   }
   #endif
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ MPI_INT, 1 ], " << std::to_string(source) );

   info = -1;
   
   /* Receiving processes shall resize their containers suitably */
   SN_MPI_EXCEPT_PROC_REGION( source ) {
      buff.resize( static_cast< small_t >( size_msg ) );
   }
   
   /* Next, the actual message */
   info = MPI_Bcast( buff.data_, size_msg, DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD );
   
   // Run-time error checking
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   
   #ifdef NDEBUG
   if( info != MPI_SUCCESS ) {   
      SN_THROW_MPI_ERROR( "MPI_AutoBcast2_Error" );
   }
   #endif
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ " << DTInfo< TYPE_T >::mpi_name
                                                   << ", " << std::to_string(size_msg) << " ], "
                                                   << std::to_string(source) );
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of broadcast function
//////////////////////////////////////

/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument is thrown is the arguments are not suitable. An MPIError exception is thrown if the return code of the 
*   operation is not MPI_SUCCESS.
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
void BaseComm<TYPE_T>::broadcast( FastBuffer<TYPE_T> & buff, int size, int source, MPIRequest<TYPE_T> & mpiR ) {
   
   SN_CT_REQUIRE< typetraits::is_basic<TYPE_T>::value >();   // Free template input prerequires a Türsteher.
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)buff.getSize();
   (void)mpiR.getSize();
   (void)source;
   (void)size;
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );
   
   #ifdef NDEBUG
   if( size <= 0 || source < 0 || source > SN_MPI_SIZE() ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_Bcast" );
   }
   #endif
   
   /* Receiving processes shall resize their containers suitably */
   SN_MPI_EXCEPT_PROC_REGION( source ) {
      buff.resize( static_cast< small_t >( size ) );
   }
   
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   /* Decision */
   if( BCMODE == MPIBcastMode::Standard ) {
      
      info = MPI_Bcast( buff.data_, size, DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Bcast_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIBcast, "[ " << DTInfo< TYPE_T >::mpi_name
                                                      << ", " << std::to_string(size) << " ], "
                                                      << std::to_string(source) );
   }
   else if( BCMODE == MPIBcastMode::Immediate ) {
      
      info = MPI_Ibcast( buff.data_, size, DTInfo< TYPE_T >::mpi_type, source, MPI_COMM_WORLD, mpiR );
      
      // Run-time error checking
      SN_ASSERT_EQUAL( info, MPI_SUCCESS );
      
      #ifdef NDEBUG
      if( info != MPI_SUCCESS ) {
         SN_THROW_MPI_ERROR( "MPI_Ibcast_Error" );
      }
      #endif
      
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIIbcast, "[ " << DTInfo< TYPE_T >::mpi_name
                                                       << ", " << std::to_string(size) << " ], "
                                                       << std::to_string(source) );
   }
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definitions of MPI_Wait functions
///////////////////////////////////////

/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument exception is thrown if the request is invalid. An MPIError exception is thrown if the wait operation is 
*   either unsuccessful or the transfer count doesn't match the one registered in the request container.
*
*   This function derives from a template which specifies the exact operation, which in turn helps debugging greatly.
*
*   \tparam TYPE_T    Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \tparam WAIT_ON   Indicates for the completion of which MPI operation it is being waited.
*   \param req        Provides information required for the completion of the non-blocking operation for which it is being waited.
*/

template < typename TYPE_T >
template< MPIWaitOp WAIT_ON >
void BaseComm<TYPE_T>::wait( MPIRequest<TYPE_T> & req ) {
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)req.getSize();
   
   #endif   // MPI Guard
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   MPI_Status stat;
   
   // Make sure that the request hasn't been laid to rest already
   SN_ASSERT( req.getSize() == 1 );
   SN_ASSERT( *req != MPI_REQUEST_NULL );
   
   #ifdef NDEBUG
   if( req.getSize() != 1 || *req == MPI_REQUEST_NULL ) {
      SN_THROW_INVALID_ARGUMENT( "IA_MPI_Wait" );
   }
   #endif
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   info = MPI_Wait( req, &stat );
   
   // Check status: Has every little bit of data arrived as expected?
   int actual_transfer_count = 0;
   MPI_Get_count( &stat, DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );

   // Run-time error checking - success and count
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount() );
   
   #ifdef NDEBUG
   if( info != MPI_SUCCESS || ! req.isClear() ) {   
      SN_THROW_MPI_ERROR( "MPI_Wait_Error" );
   }
   if( actual_transfer_count != static_cast< int >( req.getTransferCount() ) ) {   
      SN_THROW_MPI_ERROR( "MPI_Wait_Count_Error" );
   }
   #endif
   
   if( WAIT_ON == MPIWaitOp::Send )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( ISEND )" );
   else if( WAIT_ON == MPIWaitOp::Receive )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( IRECV )" );
   else if( WAIT_ON == MPIWaitOp::Broadcast )
      SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWait, "( IBCAST )" );
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Definition of MPI_Waitall function
////////////////////////////////////////

/** The container FastBuffer is used to provide pointer access to the underlying array. Notes on exception safety: basic safety 
*   guaranteed. An InvalidArgument exception is thrown if the argument count does not equal the size of the MPIRequest container. An 
*   MPIError exception is thrown if the return code is not MPI_SUCCESS.
*
*   \tparam TYPE_T    Datatype of the array, which must be basic as defined by the BasicTypeTraits library.
*   \param count      The number of non-blocking operations.
*   \param req        Provides information required for the completion of the non-blocking operations for which it is being waited.
*/

template < typename TYPE_T >
void BaseComm<TYPE_T>::waitAll( int count, MPIRequest< TYPE_T > & req ) {
   
   #ifndef __SN_USE_MPI__
   return;               // Speedy return prevents adding an if conditional to serial overhead
   
   // Killing the -Wunused-parameter warnings in case of no MPI and release mode
   (void)req.getSize();
   (void)count;
   
   #endif   // MPI Guard
   
   // Logic check
   SN_ASSERT_EQUAL( count, static_cast< int >( req.getSize() ) );
   
   #ifdef NDEBUG
   if( count != static_cast< int >( req.getSize() ) ) {
      SN_THROW_INVALID_ARGUMENT( "IA_Request_Count_Mismatch" );
   }
   #endif
   
   if( ! SN_MPI_INITIALIZED() || SN_MPI_SIZE() == 1 ) {   // Running with MPI but only 1 proc
      return;
   }
   
   
   #ifdef __SN_USE_MPI__
   
   int info = -1;
   FastBuffer< MPI_Status > stat( count );
   
   /* Thread safety is important */
   #ifdef __SN_USE_STL_MULTITHREADING__
   static std::mutex mt;
   std::lock_guard< std::mutex > lguard( mt );
   #endif
   
   #ifdef __SN_USE_OPENMP__
   OMP_CRITICAL_REGION()
   {
   #endif
   
   info = MPI_Waitall( count, req, stat.data_ );
   
   // Run-time error checking - success
   SN_ASSERT_EQUAL( info, MPI_SUCCESS );
   SN_ASSERT( req.isClear() );
   
   #ifdef NDEBUG
   if( info != MPI_SUCCESS || ! req.isClear() ) {   
      SN_THROW_MPI_ERROR( "MPI_Waitall_Error" );
   }
   #endif
   
   // Check status
   for( int i=0; i<count; ++i ) {
  
      // Check status: Has every little bit of data arrived as expected?
      int actual_transfer_count = 0;
      MPI_Get_count( &stat.data_[i], DTInfo< TYPE_T >::mpi_type, &actual_transfer_count );
      
      // Run-time error checking - count
      SN_ASSERT_EQUAL( static_cast< small_t >( actual_transfer_count ), req.getTransferCount(i) );
      
      #ifdef NDEBUG
      if( actual_transfer_count != static_cast< int >( req.getTransferCount(i) ) ) {   
         SN_THROW_MPI_ERROR( "MPI_Waitall_Count_Error" );
      }
      #endif
   }
   
   SN_LOG_REPORT_L1_EVENT( LogEventType::MPIWaitAll, "" );
   
   #ifdef __SN_USE_OPENMP__
   }                          // Closing up the critical region
   #endif
   
   #endif   // MPI Guard
}


}   // namespace simpleNewton

#endif   // Header guard
