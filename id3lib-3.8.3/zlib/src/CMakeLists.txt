# folder: id3lib-3.8.3\zlib\src
#         ---------------------

include_directories( ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/zlib/include )

file( GLOB SRC *.c )

add_library( zlib ${SRC} )
