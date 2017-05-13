#include "DTInfo.hpp"

/**||**************************************************************************************************************************************
*
*   Description: struct DTInfo's static constexpr literals have to be 'defined'
*
|**************************************************************************************************************************************///+

namespace simpleNewton {
namespace types {



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< char >::mpi_type;
constexpr char DTInfo< char >::mpi_name[];
#endif
constexpr char DTInfo< char >::name[];




#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned char >::mpi_type;
constexpr char DTInfo< unsigned char >::mpi_name[];
#endif
constexpr char DTInfo< unsigned char >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< short >::mpi_type;
constexpr char DTInfo< short >::mpi_name[];
#endif
constexpr char DTInfo< short >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned short >::mpi_type;
constexpr char DTInfo< unsigned short >::mpi_name[];
#endif
constexpr char DTInfo< unsigned short >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< int >::mpi_type;
constexpr char DTInfo< int >::mpi_name[];
#endif
constexpr char DTInfo< int >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned int >::mpi_type;
constexpr char DTInfo< unsigned int >::mpi_name[];
#endif
constexpr char DTInfo< unsigned int >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< long >::mpi_type;
constexpr char DTInfo< long >::mpi_name[];
#endif
constexpr char DTInfo< long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned long >::mpi_type;
constexpr char DTInfo< unsigned long >::mpi_name[];
#endif
constexpr char DTInfo< unsigned long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< long long >::mpi_type;
constexpr char DTInfo< long long >::mpi_name[];
#endif
constexpr char DTInfo< long long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< unsigned long long >::mpi_type;
constexpr char DTInfo< unsigned long long >::mpi_name[];
#endif
constexpr char DTInfo< unsigned long long >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< float >::mpi_type;
constexpr char DTInfo< float >::mpi_name[];
#endif
constexpr char DTInfo< float >::name[];



#ifdef __SN_USE_MPI__
constexpr MPI_Datatype DTInfo< double >::mpi_type;
constexpr char DTInfo< double >::mpi_name[];
#endif
constexpr char DTInfo< double >::name[];



}   // namespace types
}   // namespace simpleNewton
