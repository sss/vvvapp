# folder: src
#         ---

FIND_PACKAGE(wxWidgets REQUIRED html adv core base net aui xrc qa richtext )
INCLUDE(${wxWidgets_USE_FILE})

include_directories( ${PROJECT_SOURCE_DIR}/src/ibpp/core
                     ${PROJECT_SOURCE_DIR}/src/data_interface
) 

if(WIN32)
  # under Windows we compile id3lib together with VVV
  include_directories( ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/include
                       ${PROJECT_SOURCE_DIR}/id3lib-3.8.3/include/id3
  )
endif(WIN32)

if( WIN32 )
  add_definitions( -DIBPP_WINDOWS )
elseif( APPLE )
  add_definitions( -DIBPP_DARWIN )
else( WIN32 )
  add_definitions( -DIBPP_LINUX )
endif( WIN32 )

add_subdirectory( ibpp )
add_subdirectory( data_interface )

link_directories (${PROJECT_BINARY_DIR}/src/ibpp/core
                  ${PROJECT_BINARY_DIR}/src/data_interface
) 

if(WIN32)
  link_directories (${PROJECT_BINARY_DIR}/id3lib-3.8.3/src
                    ${PROJECT_BINARY_DIR}/id3lib-3.8.3/src/zlib/src
  )
endif(WIN32)


# For convenience we define the sources as a variable. You can add 
# header files and cpp/c files and CMake will sort them out
set( SRCS
  audio_metadata.cpp
  audio_metadata.h
  catalog_volume.cpp
  catalog_volume.h
  catalog_volume_functions.cpp
  catalog_volume_functions.h
  choose_virtual_folder.cpp
  choose_virtual_folder.h
  convert_db_unicode.cpp
  exportdata.cpp
  exportdata.h
  long_task_beep.cpp
  long_task_beep.h
  mainframe.cpp
  mainframe.h
  mylistitemdata.h
  mytreeitemdata.h
  object_description.cpp
  object_description.h
  opencatalog.cpp
  opencatalog.h
  resource.h
  restore.cpp
  restore.h
  settings.cpp
  settings.h
  update_volume.cpp
  update_volume.h
  utils.cpp
  utils.h
  vvv.cpp
  vvv.h
  window_position.cpp
  window_position.h
)
  

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} windows_specific.cpp windows_specific.h vvv.rc vvv.rc2)
endif(WIN32)

add_executable( vvv WIN32 MACOSX_BUNDLE ${SRCS} )

add_definitions( -DID3LIB_LINKOPTION=1 )

target_link_libraries(vvv data_interface ibpp ${wxWidgets_LIBRARIES})
if(WIN32)
  target_link_libraries( vvv id3lib zlib )
endif(WIN32)
if( UNIX )
  # link to the Firebird client library and to id3lib
  find_library( FB_LIB fbembed PATHS /usr/lib /usr/local/lib /opt/firebird/lib )
  if( NOT FB_LIB )
    message( FATAL_ERROR "Unable to find firebird interface" )
  else( NOT FB_LIB )
    message( STATUS "Firebird interface: " ${FB_LIB} )
  endif( NOT FB_LIB )

  # first look for a static id3lib library
  find_library( ID3_LIB libid3.a PATHS /usr/lib /usr/local/lib )
  if( NOT ID3_LIB )
    # if not found accept a shared one
    find_library( ID3_LIB id3 PATHS /usr/lib /usr/local/lib )
  endif( NOT ID3_LIB )
  if( NOT ID3_LIB )
    message( FATAL_ERROR "Unable to find id3lib" )
  else( NOT ID3_LIB )
    message( STATUS "Id3lib: " ${ID3_LIB} )
  endif( NOT ID3_LIB )

#  target_link_libraries( vvv -lfbembed )
  target_link_libraries( vvv ${FB_LIB} ${ID3_LIB} )
endif( UNIX )
