add_library( CONCURRENCY BaseComm.cpp
                         ${PROJECT_SOURCE_DIR}/lib/containers/mpi/OpenMPIBuffer.cpp
                         ${PROJECT_SOURCE_DIR}/lib/containers/mpi/MPIRequest.cpp )
