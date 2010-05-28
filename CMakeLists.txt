# The name of our project is "VVV". CMakeLists files in this project can
# refer to the root source directory of the project as ${VVV_SOURCE_DIR} and
# to the root binary directory of the project as ${VVV_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (VVV)

if( WIN32 )
  add_subdirectory( id3lib-3.8.3 ) 
endif( WIN32 )

add_subdirectory( src ) 

