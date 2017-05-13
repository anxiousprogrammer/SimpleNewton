#ifndef MPIREQUEST_HPP
#define MPIREQUEST_HPP

#ifdef __SN_USE_MPI__

#include <mpi.h>

#include <Types.hpp>
#include <BasicBases.hpp>
#include <asserts/Asserts.hpp>

#include <containers/RAIIWrapper.hpp>

/**||**************************************************************************************************************************************
*
*   Description: MPI container which ships information about an immediate send or receive to the corresponding wait function
*
|**************************************************************************************************************************************///+

namespace simpleNewton {

template< typename TYPE_T >
class MPIRequest : private NonCopyable {

public:

   /* LCM */
   MPIRequest( small_t size = 1 ) : size_(size), count_( createRAIIWrapper< small_t >( size, 0 ) ), 
                                    req_( createRAIIWrapper< MPI_Request >( size, MPI_REQUEST_NULL ) ) {}
   MPIRequest( MPIRequest && ) = default;
   ~MPIRequest() = default;

   // Access
   small_t getSize() const                                 { return size_; }
   small_t getTransferCount() const                        { return count_[0]; }
   small_t getTransferCount( small_t i ) const             { SN_ASSERT( i < size_ ); return count_[i]; }
   void setTransferCount( small_t new_count )              { count_[0] = new_count; }
   void setTransferCount( small_t new_count, small_t i )   { SN_ASSERT( i < size_ ); count_[i] = new_count; }
   
   // User defined conversion to yield access to the underlying request unit(s)
   inline operator MPI_Request*()   { return req_;   }
   inline MPI_Request * raw_ptr()   { return req_;   }
   
   // State - have all requests been waited upon and cleared?
   bool isClear() {
      
      bool ret_val = true;
      for( small_t i = 0; i < size_; ++i ) {
         
         if( req_[i] != MPI_REQUEST_NULL )
            ret_val = false;
      }
      
      return ret_val;
   }

private:
   
   small_t size_;
   RAIIWrapper< small_t > count_;
   RAIIWrapper< MPI_Request > req_;
};

}   // namespace simpleNewton

#endif   // __SN_USE_MPI__
#endif   // Header guard
