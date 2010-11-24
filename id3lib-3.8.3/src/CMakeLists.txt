# folder: id3lib-3.8.3\src
#         ----------------

add_definitions( -D_MBCS -DID3LIB_LINKOPTION=1 -D_LIB -DHAVE_CONFIG_H )

include_directories (${PROJECT_SOURCE_DIR}/id3lib-3.8.3 
                     ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/include
                     ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/include/id3
                     ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/zlib/include
) 

file( GLOB SRC *.cpp )

add_library( id3lib ${SRC} )

