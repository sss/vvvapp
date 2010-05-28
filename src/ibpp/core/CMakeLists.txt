# folder: ibpp/core
#         ---------

remove_definitions( -DUNICODE -D_UNICODE )

file( GLOB SRCS all_in_one.cpp *.h )

add_library( ibpp ${SRCS} )
