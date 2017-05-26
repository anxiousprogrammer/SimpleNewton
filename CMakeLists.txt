cmake_minimum_required (VERSION 2.6)
project( simpleNewton )

# The version number.
set( simpleNewton_VERSION_MAJOR 1 )
set( simpleNewton_VERSION_MINOR 0 )



# Options
option( SN_USE_MPI              "Include and use the message passing interface (MPI) libraries"     ON  )
option( SN_USE_MULTITHREADING   "Enable the use of multithreading"                                  ON  )
option( SN_USE_OPENMP           "Include and use the OpenMP API"                                    ON  )

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE        Debug CACHE STRING "Debug or Release" FORCE                             )
endif()
SET_PROPERTY( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release )

option( SN_EXCEPTION_WITH_FUNC_LINE_INFO   "Exceptions will carry function and line information"    ON  )
option( SN_LOGLEVEL_ERROR                  "Enables logging of errors"                              ON  )
option( SN_LOGLEVEL_WARNING                "Enables logging of warnings"                            ON  )
option( SN_LOGLEVEL_WATCH                  "Enables watching of variables"                          ON  )
option( SN_LOGLEVEL_L1_EVENT               "Enables logging of low-level events"                    ON  )
option( SN_LOGLEVEL_L2_EVENT               "Enables logging of high-level events"                   ON  )
option( SN_LOGLEVEL_WRITE_WARNINGS         "Enables writing warnings to log"                        ON  )
option( SN_LOGLEVEL_WRITE_WATCHES          "Enables writing watches to log"                         OFF )
option( SN_LOGLEVEL_WRITE_EVENTS           "Enables writing events to log"                          OFF )
option( BUILD_DOXYDOC                      "Enables documentation using Doxygen"                    ON  )

# Finding libraries/packages and such
if( SN_USE_MPI )
   find_package( MPI REQUIRED )
   add_definitions( -D__SN_USE_MPI__ )
endif()
if( SN_USE_OPENMP )
   include( FindOpenMP )
endif()
if( BUILD_DOXYDOC )
   find_package( Doxygen REQUIRED )
   configure_file ( ${simpleNewton_SOURCE_DIR}/doc/doxycon.in ${simpleNewton_BINARY_DIR}/doc/doxygen.cfg @ONLY )
   add_custom_target( doc
                      COMMAND ${DOXYGEN_EXECUTABLE} ${simpleNewton_BINARY_DIR}/doc/doxygen.cfg
                      COMMENT "Generating API documentation with Doxygen" VERBATIM )
endif()



# Compiler - flags
set( simpleNewton_GENERAL_COMPILE_FLAGS "-O3 -std=c++11 -Wall -Winline -Wshadow -Wextra -Wpedantic" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${simpleNewton_GENERAL_COMPILE_FLAGS}" )

if( SN_USE_OPENMP )
   add_definitions( -D__SN_USE_OPENMP__ )
   set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

if( SN_USE_MPI )
   if( MPI_COMPILE_FLAGS )
      set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_COMPILE_FLAGS}" )
   endif()
   if( MPI_CXX_LINK_FLAGS )
      set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}" )
   endif()
endif()



# Important definitions
if( SN_USE_MULTITHREADING )
   add_definitions( -D__SN_USE_MULTITHREADING__ )
endif()
if( CMAKE_BUILD_TYPE MATCHES Release )
   add_definitions( -DNDEBUG )
endif()
if( SN_EXCEPTION_WITH_FUNC_LINE_INFO )
   add_definitions( -D__SN_EXCEPTION_WITH_FUNC_LINE_INFO__ )
endif()
if( SN_LOGLEVEL_ERROR )
   add_definitions( -D__SN_LOGLEVEL_ERROR__ )
endif()
if( SN_LOGLEVEL_WARNING )
   add_definitions( -D__SN_LOGLEVEL_WARNING__ )
endif()
if( SN_LOGLEVEL_WATCH )
   add_definitions( -D__SN_LOGLEVEL_WATCH__ )
endif()
if( SN_LOGLEVEL_L1_EVENT )
   add_definitions( -D__SN_LOGLEVEL_L1_EVENT__ )
endif()
if( SN_LOGLEVEL_L2_EVENT )
   add_definitions( -D__SN_LOGLEVEL_L2_EVENT__ )
endif()
if( SN_LOGLEVEL_WRITE_WARNINGS )
   add_definitions( -D__SN_LOGLEVEL_WRITE_WARNINGS__ )
endif()
if( SN_LOGLEVEL_WRITE_WATCHES )
   add_definitions( -D__SN_LOGLEVEL_WRITE_WATCHES__ )
endif()
if( SN_LOGLEVEL_WRITE_EVENTS )
   add_definitions( -D__SN_LOGLEVEL_WRITE_EVENTS__ )
endif()



# Configure a header file to pass some of the CMake settings to the source code
configure_file(
   "${simpleNewton_SOURCE_DIR}/simpleNewtonConfig.h.in"
   "${simpleNewton_BINARY_DIR}/simpleNewtonConfig.h" )



# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories( "${simpleNewton_BINARY_DIR}" )
# Now the libraries
if( MPI_CXX_FOUND AND SN_USE_MPI )
   include_directories( ${MPI_INCLUDE_PATH} )
endif()

include_directories( "${simpleNewton_SOURCE_DIR}/lib" )

add_subdirectory( lib )

set( BASIC_LIBRARIES ASSERTS LOGGER PROCMAN EXCEPTIONS TYPES )   # Opposite order makes sure dependencies are taken care of

if( SN_USE_MPI )
   set( BASIC_LIBRARIES ${BASIC_LIBRARIES} ${MPI_CXX_LIBRARIES} MPI )
endif()

#if( SN_USE_MULTITHREADING )
#   set( BASIC_LIBRARIES ${BASIC_LIBRARIES} CONCURRENCY )
#endif()

#if( SN_USE_OPENMP )
#   set( BASIC_LIBRARIES ${BASIC_LIBRARIES} OMP )
#endif()

set( ALL_LIBRARIES ${BASIC_LIBRARIES} BASICTYPETRAITS TYPECONSTRAINTS CONTAINERS )



# add the executables
add_executable( AssertTest ${simpleNewton_SOURCE_DIR}/prog/AssertTest.cpp )
add_executable( LoggerTest ${simpleNewton_SOURCE_DIR}/prog/LoggerTest.cpp )
add_executable( ContainerTest ${simpleNewton_SOURCE_DIR}/prog/ContainerTest.cpp )
add_executable( MPITest ${simpleNewton_SOURCE_DIR}/prog/MPITest.cpp )
add_executable( TypelistTest ${simpleNewton_SOURCE_DIR}/prog/TypelistTest.cpp )
# link the execs
target_link_libraries( AssertTest ${BASIC_LIBRARIES} TYPECONSTRAINTS )
target_link_libraries( LoggerTest ${BASIC_LIBRARIES} TYPECONSTRAINTS )
target_link_libraries( ContainerTest ${BASIC_LIBRARIES} TYPECONSTRAINTS CONTAINERS )
target_link_libraries( MPITest ${BASIC_LIBRARIES} TYPECONSTRAINTS CONTAINERS )
target_link_libraries( TypelistTest ${BASIC_LIBRARIES} TYPECONSTRAINTS )
