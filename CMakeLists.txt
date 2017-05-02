cmake_minimum_required (VERSION 2.6)
project( simpleNewton )

# The version number.
set( simpleNewton_VERSION_MAJOR 1 )
set( simpleNewton_VERSION_MINOR 0 )

# Options
option( SN_USE_MPI         "Include and use the message passing interface (MPI) libraries"   ON  )
if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE   Debug CACHE STRING "Debug or Release" FORCE                           )
endif()
option( SN_LOGLEVEL_ERROR            "Enables logging of errors"                             ON  )
option( SN_LOGLEVEL_WARNING          "Enables logging of warnings"                           ON  )
option( SN_LOGLEVEL_WATCH            "Enables watching of variables"                         ON  )
option( SN_LOGLEVEL_EVENT            "Enables logging of events"                             ON  )
option( SN_LOGLEVEL_WRITE_WARNINGS   "Enables writing warnings to log"                       ON  )
option( SN_LOGLEVEL_WRITE_WATCHES    "Enables writing watches to log"                        OFF )
option( SN_LOGLEVEL_WRITE_EVENTS     "Enables writing events to log"                         OFF )

# Finding libraries/packages and such
if( SN_USE_MPI )
   find_package( MPI REQUIRED )
   add_definitions( -D__SN_USE_MPI__ )
endif()

# Compiler - flags
set( PROJECT_GENERAL_COMPILE_FLAGS "-O3 -std=c++11 -Wall -Winline -Wshadow -Wextra -Wpedantic" )
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${PROJECT_GENERAL_COMPILE_FLAGS} )
if( SN_USE_MPI )
   if( MPI_COMPILE_FLAGS )
      set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${MPI_COMPILE_FLAGS} )
   endif()
   if( MPI_CXX_LINK_FLAGS )
      set( CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS} )
   endif()
endif()

# Important definitions
if( CMAKE_BUILD_TYPE MATCHES Release )
   add_definitions( -DNDEBUG )
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
if( SN_LOGLEVEL_EVENT )
   add_definitions( -D__SN_LOGLEVEL_EVENT__ )
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
   "${PROJECT_SOURCE_DIR}/simpleNewtonConfig.h.in"
   "${PROJECT_BINARY_DIR}/simpleNewtonConfig.h" )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories( "${PROJECT_BINARY_DIR}" )
# Now the libraries
if( MPI_CXX_FOUND AND SN_USE_MPI )
   include_directories( ${MPI_INCLUDE_PATH} )
endif()
include_directories( "${PROJECT_SOURCE_DIR}/lib" )
add_subdirectory( lib )
set( BASIC_LIBRARIES MPIWRAPPER LOGGER ASSERTS )
if( SN_USE_MPI )
   set( BASIC_LIBRARIES ${BASIC_LIBRARIES} ${MPI_CXX_LIBRARIES} )
endif()
set( ALL_LIBRARIES MPIWRAPPER LOGGER ASSERTS BASICTYPETRAITS TYPECONSTRAINTS FASTLOOPS CONTAINERS )

# add the executables
add_executable( AssertTest ${PROJECT_SOURCE_DIR}/prog/AssertTest.cpp )
add_executable( LoggerTest ${PROJECT_SOURCE_DIR}/prog/LoggerTest.cpp )
add_executable( ContainerTest ${PROJECT_SOURCE_DIR}/prog/ContainerTest.cpp )
add_executable( MPITest ${PROJECT_SOURCE_DIR}/prog/MPITest.cpp )
#add_executable( TypelistTest ${PROJECT_SOURCE_DIR}/prog/TypelistTest.cpp )
# link the execs
target_link_libraries( AssertTest ${BASIC_LIBRARIES} TYPECONSTRAINTS )
target_link_libraries( LoggerTest ${BASIC_LIBRARIES} TYPECONSTRAINTS )
target_link_libraries( ContainerTest ${BASIC_LIBRARIES} TYPECONSTRAINTS FASTLOOPS CONTAINERS )
target_link_libraries( MPITest ${BASIC_LIBRARIES} TYPECONSTRAINTS CONTAINERS )
#target_link_libraries( TypelistTest ${ALL_LIBRARIES} )
