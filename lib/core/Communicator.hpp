#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include "MPIManager.hpp"
#include <asserts/Asserts.hpp>
#include <types/BasicTypeTraits.hpp> 
#include <asserts/TypeConstraints.hpp>
#include <Types.hpp>

namespace simpleNewton {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Hack: WE WANT CPP! To make it a self-sufficient compile unit.
///////////////////////////////////////////////////////////////////

template< class TYPE >
struct Communicator_CPPHackClass {};

/**||***************************************************************************************************************************************
*
*   Description: MPI communication methods
*
|***************************************************************************************************************************************///+

class Communicator : public NonInstantiable {

public:
   
   /* Operation: Send basic types */
   
   /* Declaration: Blocking send */
   template< class TYPE_T >
   static void BSend( TYPE_T * , int , int );
   
   /* Declaration: Non-blocking send */
   template< class TYPE_T >
   static void NBSend( TYPE_T * , int , int );
   
   /* Operation: Receive basic types */
   
   /* Declaration: Blocking receive */
   template< typename TYPE_T >
   static void BRecv( TYPE_T * , int , int );
   
   /* Declaration: Blocking receive */
   template< class TYPE_T >
   static void NBRecv( TYPE_T * , int, int );

private:
   
   Communicator() = default;
   ~Communicator();
   
   // IMPLEMENTATION
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///   Definitions of members
////////////////////////////

template< class TYPE_T >
void Communicator::BSend( TYPE_T * ptr, int size, int target ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value || typetraits::is_array_of_basic_datatype<TYPE_T>::value >();
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), target );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( target, 0 );
   SN_ASSERT_LESS_THAN( target, SN_MPI_SIZE() );
   
   static int tag = 0;
   int info;
 
 
   if( typetraits::are_type_similar< TYPE_T, char >::value || typetraits::is_array_of_type< TYPE_T, char >::value ) {
      info = MPI_Send( ptr, size, MPI_CHAR, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, bool >::value || typetraits::is_array_of_type< TYPE_T, bool >::value ) {
      info = MPI_Send( ptr, size, MPI_INT, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, int >::value || typetraits::is_array_of_type< TYPE_T, int >::value ) {
      info = MPI_Send( ptr, size, MPI_INT, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, short >::value || typetraits::is_array_of_type< TYPE_T, short >::value ) {
      info = MPI_Send( ptr, size, MPI_SHORT, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, long >::value || typetraits::is_array_of_type< TYPE_T, long >::value ) {
      info = MPI_Send( ptr, size, MPI_LONG, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, long long >::value || typetraits::is_array_of_type< TYPE_T, long long >::value ) {
      info = MPI_Send( ptr, size, MPI_LONG_LONG, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned char >::value || typetraits::is_array_of_type< TYPE_T, unsigned char >::value ) {
      info = MPI_Send( ptr, size, MPI_UNSIGNED_CHAR, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned short >::value || 
            typetraits::is_array_of_type< TYPE_T, unsigned short >::value ) {
      info = MPI_Send( ptr, size, MPI_UNSIGNED_SHORT, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned int >::value || typetraits::is_array_of_type< TYPE_T, unsigned int >::value ) {
      info = MPI_Send( ptr, size, MPI_UNSIGNED, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned long >::value || typetraits::is_array_of_type< TYPE_T, unsigned long >::value ) {
      info = MPI_Send( ptr, size, MPI_UNSIGNED_LONG, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned long long >::value || 
            typetraits::is_array_of_type< TYPE_T, unsigned long long >::value ) {
      info = MPI_Send( ptr, size, MPI_UNSIGNED_LONG_LONG, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, float >::value || typetraits::is_array_of_type< TYPE_T, float >::value ) {
      info = MPI_Send( ptr, size, MPI_FLOAT, target, tag++, MPI_COMM_WORLD );
   }
   else if( typetraits::are_type_similar< TYPE_T, double >::value || typetraits::is_array_of_type< TYPE_T, double >::value ) {
      info = MPI_Send( ptr, size, MPI_DOUBLE, target, tag++, MPI_COMM_WORLD );
   }
   else {
      SN_LOG_REPORT_ERROR( "An attempt was made to call MPI_Send with a compound datatype. The program will now exit." );
      
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   
   if( info != MPI_SUCCESS ) {
   
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI blocking send operation. The program will now exit." );
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   if( tag == 1000 ) {
      tag = 0;
   }
}



template< typename TYPE_T >
void Communicator::BRecv( TYPE_T * ptr, int size, int source ) {
   
   SN_CT_REQUIRE< typetraits::is_basic_datatype<TYPE_T>::value || typetraits::is_array_of_basic_datatype<TYPE_T>::value >();
   
   SN_ASSERT_INEQUAL( SN_MPI_RANK(), source );
   SN_ASSERT_POSITIVE( size );
   SN_ASSERT_GREQ( source, 0 );
   SN_ASSERT_LESS_THAN( source, SN_MPI_SIZE() );

   static int tag = 0;
   int info = -1;
   MPI_Status stat;
   
   
   if( typetraits::are_type_similar< TYPE_T, char >::value || typetraits::is_array_of_type< TYPE_T, char >::value ) {
      info = MPI_Recv( ptr, size, MPI_CHAR, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, bool >::value || typetraits::is_array_of_type< TYPE_T, bool >::value ) {
      info = MPI_Recv( ptr, size, MPI_INT, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, int >::value || typetraits::is_array_of_type< TYPE_T, int >::value ) {
      info = MPI_Recv( ptr, size, MPI_INT, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, short >::value || typetraits::is_array_of_type< TYPE_T, short >::value ) {
      info = MPI_Recv( ptr, size, MPI_SHORT, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, long >::value || typetraits::is_array_of_type< TYPE_T, long >::value ) {
      info = MPI_Recv( ptr, size, MPI_LONG, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, long long >::value || typetraits::is_array_of_type< TYPE_T, long long >::value ) {
      info = MPI_Recv( ptr, size, MPI_LONG_LONG, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned char >::value || typetraits::is_array_of_type< TYPE_T, unsigned char >::value ) {
      info = MPI_Recv( ptr, size, MPI_UNSIGNED_CHAR, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned short >::value || 
            typetraits::is_array_of_type< TYPE_T, unsigned short >::value ) {
      info = MPI_Recv( ptr, size, MPI_UNSIGNED_SHORT, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned int >::value || typetraits::is_array_of_type< TYPE_T, unsigned int >::value ) {
      info = MPI_Recv( ptr, size, MPI_UNSIGNED, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned long >::value || typetraits::is_array_of_type< TYPE_T, unsigned long >::value ) {
      info = MPI_Recv( ptr, size, MPI_UNSIGNED_LONG, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, unsigned long long >::value || 
            typetraits::is_array_of_type< TYPE_T, unsigned long long >::value ) {
      info = MPI_Recv( ptr, size, MPI_UNSIGNED_LONG_LONG, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, float >::value || typetraits::is_array_of_type< TYPE_T, float >::value ) {
      info = MPI_Recv( ptr, size, MPI_FLOAT, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else if( typetraits::are_type_similar< TYPE_T, double >::value || typetraits::is_array_of_type< TYPE_T, double >::value ) {
      info = MPI_Recv( ptr, size, MPI_DOUBLE, source, tag++, MPI_COMM_WORLD, &stat );
   }
   else {
      SN_LOG_REPORT_ERROR( "An attempt was made to call MPI_Send with a compound datatype. The program will now exit." );
      
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   
   if( info != MPI_SUCCESS ) {
      SN_LOG_REPORT_ERROR( "An unknown error occured while attempted to perform an MPI blocking send operation. The program will now exit." );
      
      /////////////////
      ///   EXIT POINT!
      SN_EXIT();
      /////////////////
   }
   
   SN_ASSERT_EQUAL( stat.MPI_SOURCE, source  );
   SN_ASSERT( ! stat.MPI_ERROR );
  
   if( tag == 1000 ) {
      tag = 0;
   }
}

}   // namespace simpleNewton

#endif
