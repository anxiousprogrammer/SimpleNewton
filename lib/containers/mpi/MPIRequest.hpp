#ifndef SN_MPIREQUEST_HPP
#define SN_MPIREQUEST_HPP

#ifdef __SN_USE_MPI__
#include <mpi.h>
#endif

#include <Types.hpp>
#include <BasicBases.hpp>
#include <asserts/Asserts.hpp>

#include <containers/RAIIWrapper.hpp>

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
///   Contains the class template MPIRequest, which serves as a bridge between a non-blocking MPI operation and its corresponding wait
///   function.
///   \file
///   \defgroup mpi MPI
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================


/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** MPI container which ships information (MPI_Request and operation transfer count) about at least one non-blocking MPI operation to the 
*   corresponding wait function. This container can also be treated as an array whose elements correspond to multiple non-blocking 
*   MPI operations.
*
*   \tparam TYPE_T   The type of the data upon which the non-blocking MPI operation is to be performed.
*/
//==========================================================================================================================================

#ifdef __SN_USE_MPI__
template< typename TYPE_T >
class MPIRequest : private NonCopyable {

public:

   /** \name Constructors and Destructors
   * @{
   */
   
   /** Direct initialization constructor.
   *
   *   \param size   The number of operations which this MPIRequest container shall manage.
   */
   MPIRequest( small_t size = 1 ) : size_(size), count_( createRAIIWrapper< small_t >( size, 0 ) ), 
                                    req_( createRAIIWrapper< MPI_Request >( size, MPI_REQUEST_NULL ) ) {}
   
   /** Move constructor */
   MPIRequest( MPIRequest && ) = default;
   
   /** Destructor */
   ~MPIRequest() = default;
   
   /** @} */



   /** \name Access
   * @{
   */
   /** A function to ascertain the size of the MPIRequest container.
   *   \return   The size of the MPIRequest container.
   */
   small_t getSize() const                                 { return size_; }
   
   /** A function to ascertain the exact transfer count of a non-blocking MPI operation pointed out by its corresponding container index. 
   *   \param i   The index corresponding to a certain non-blocking MPI operation. Takes a default value of 0.
   *   \return    The exact transfer count i.e., the size of the message of the non-blocking MPI operation.
   */
   small_t getTransferCount( small_t i = 0 ) const         { SN_ASSERT( i < size_ ); return count_[i]; }
   
   /** A function to set the exact transfer count of a non-blocking MPI operation pointed out by its corresponding container index.
   *   \param new_count   The value of the transfer count of a certain operation.
   *   \param i           The index corresponding to a certain non-blocking MPI operation. Takes a default value of 0.
   *   \return            The exact transfer count i.e., the size of the message of the non-blocking MPI operation.
   */
   void setTransferCount( small_t new_count, small_t i = 0 )   { SN_ASSERT( i < size_ ); count_[i] = new_count; }
   
   /** A user-defined conversion to expose the underlying MPI_Request array. This function will not be compiled if MPI is not included.
   *   \return   A pointer to the first element of the MPI_Request array.
   */
   inline operator MPI_Request*()   { return req_; }
   
   /** A function to expose the underlying MPI_Request array for when the user-defined conversion cannot be applied.
   *   \return   A pointer to the first element of the MPI_Request array.
   */
   inline MPI_Request * raw_ptr()   { return req_; }
   
   /** @} */
   
   
   
   /** \name State */
   /**   A function to check if all the MPI_Requests managed by the container have been cleared. Simply returns true if MPI is not included.
   *     \return   true if the MPI_Requests have been cleared, false if not.
   */
   bool isClear() {
      
      bool ret_val = true;
      
      for( small_t i = 0; i < size_; ++i ) {
         
         if( req_[i] != MPI_REQUEST_NULL )
            ret_val = false;
      }
      
      return ret_val;
   }

private:
   
   small_t size_;   ///< Size of the request array. A single request container can contain multiple requests.

   RAIIWrapper< small_t > count_;   ///< The container for the transfer counts. Each non-blocking MPI Op's data transfer count is recorded.
                                    ///  Will only be compiled if MPI is included.
   RAIIWrapper< MPI_Request > req_;   ///< The container of MPI_Request instances. Will only be compiled if MPI is included.
};

#else   // MPI Guard

template< typename TYPE_T >
class MPIRequest : private NonCopyable {

public:

   small_t getSize() const { return 0; }  
};
#endif   // MPI Guard

}   // namespace simpleNewton

#endif   // Header guard
