cmake_minimum_required (VERSION 2.6)
project( simpleNewton )

# The version number.
set( simpleNewton_VERSION_MAJOR 1 )
set( simpleNewton_VERSION_MINOR 0 )

# Compiler
add_definitions( -O3 -std=c++11 -Wall -Winline -Wshadow -Wextra -Wpedantic )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
   "${PROJECT_SOURCE_DIR}/simpleNewtonConfig.h.in"
   "${PROJECT_BINARY_DIR}/simpleNewtonConfig.h" )
  
# options

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories( "${PROJECT_BINARY_DIR}" )
# Now the libraries
include_directories( "${PROJECT_SOURCE_DIR}/lib" )
add_subdirectory( lib )
set( ALL_LIBRARIES ASSERTS BASICTYPETRAITS CONTAINERS LOGGER TYPECONSTRAINTS )

# add the executable - assert tester
add_executable( AssertTest ${PROJECT_SOURCE_DIR}/prog/AssertTest.cpp )
add_executable( LoggerTest ${PROJECT_SOURCE_DIR}/prog/LoggerTest.cpp )
#add_executable( TypelistTest ${PROJECT_SOURCE_DIR}/prog/TypelistTest.cpp )
target_link_libraries( AssertTest ASSERTS BASICTYPETRAITS TYPECONSTRAINTS )
target_link_libraries( LoggerTest ASSERTS BASICTYPETRAITS LOGGER TYPECONSTRAINTS )
#target_link_libraries( TypelistTest ${ALL_LIBRARIES} )
