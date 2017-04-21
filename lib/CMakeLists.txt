include_directories( "${PROJECT_SOURCE_DIR}/lib/asserts" )
include_directories( "${PROJECT_SOURCE_DIR}/lib/containers" )
include_directories( "${PROJECT_SOURCE_DIR}/lib/logger" )
include_directories( "${PROJECT_SOURCE_DIR}/lib/types" )

add_subdirectory( asserts )
add_subdirectory( containers )
add_subdirectory( logger )
add_subdirectory( types )
