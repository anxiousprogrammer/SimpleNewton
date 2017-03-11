cmake_minimum_required (VERSION 2.6)
project( simpleNewton )

# The version number.
set( simpleNewton_VERSION_MAJOR 1 )
set( simpleNewton_VERSION_MINOR 0 )

# Compiler
add_definitions( -std=c++11 )

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
set( ALL_LIBRARIES ASSERTS TYPES )

# add the executable
add_executable( Test ${PROJECT_SOURCE_DIR}/prog/Test.cpp )
target_link_libraries( Test ${ALL_LIBRARIES} )
