# The name of our project is "VVV". CMakeLists files in this project can
# refer to the root source directory of the project as ${VVV_SOURCE_DIR} and
# to the root binary directory of the project as ${VVV_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (VVV)

add_subdirectory( src ) 

set( CPACK_PACKAGE_VERSION_MAJOR 1 )
set( CPACK_PACKAGE_VERSION_MINOR 1 )
set( CPACK_PACKAGE_VERSION_PATCH 0 )
set( CPACK_STRIP_FILES TRUE )
include( CPack )
