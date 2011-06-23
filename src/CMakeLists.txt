# folder: src
#         ---

FIND_PACKAGE(wxWidgets REQUIRED html adv core base net aui xrc qa richtext )
INCLUDE(${wxWidgets_USE_FILE})

include_directories( ${PROJECT_SOURCE_DIR}/src/ibpp/core
                     ${PROJECT_SOURCE_DIR}/src/data_interface
) 

# look for TagLib
find_path( TAGLIB_INCLUDE_PATH tag.h DOC "Path to TagLib header files" )
message( STATUS "TagLib header files path: " ${TAGLIB_INCLUDE_PATH} )
if(WIN32)
  find_file( TAGLIB_LIB_PATH_DEBUG tagd.lib DOC "Path to the DEBUG TagLib library" )
  find_file( TAGLIB_LIB_PATH_RELEASE tag.lib DOC "Path to the RELEASE TagLib library" )
else(WIN32)
  find_library( TAGLIB_LIB libtag.a PATHS /usr/lib /usr/local/lib )
  if( NOT TAGLIB_LIB )
    message( FATAL_ERROR "Unable to find TagLib" )
  else( NOT TAGLIB_LIB )
    message( STATUS "TagLib: " ${TAGLIB_LIB} )
  endif( NOT TAGLIB_LIB )
endif(WIN32)

include_directories( ${TAGLIB_INCLUDE_PATH} )
add_definitions( -DTAGLIB_STATIC )

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
  chooselang.cpp
  chooselang.h
  convert_db_unicode.cpp
  decode_search_string.cpp
  decode_search_string.h
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
  set( SRCS ${SRCS} windows_specific.cpp windows_specific.h vvv.rc vvv.rc2 )
endif(WIN32)

#--------------------------------------------------------------------------------
# For Apple set the icns file containing icons
if(APPLE)
  # icon files to copy in the bundle
  set( OSX_ICON_FILES ${CMAKE_CURRENT_SOURCE_DIR}/graphics/vvv.icns ${CMAKE_CURRENT_SOURCE_DIR}/graphics/vvv-document.icns ) 
  # set where in the bundle to put the icns files
  set_source_files_properties( ${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  # include the icns files in the target
  set( SRCS ${SRCS} ${OSX_ICON_FILES} )
ENDIF(APPLE)

add_executable( vvv WIN32 MACOSX_BUNDLE ${SRCS} )

if(APPLE)
  # configure CMake to use a custom Info.plist
  set_target_properties( vvv PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/vvv-Info.plist )
ENDIF(APPLE)

if(WIN32)
  target_link_libraries( vvv debug ${TAGLIB_LIB_PATH_DEBUG} optimized ${TAGLIB_LIB_PATH_RELEASE} )
else(WIN32)
  target_link_libraries( vvv ${TAGLIB_LIB} )
endif(WIN32)
target_link_libraries(vvv data_interface ibpp ${wxWidgets_LIBRARIES})
if( UNIX )
  # link to the Firebird client library
  # the last path is used for OS X where I have a local copy (not installed)
  find_library( FB_LIB fbembed PATHS /usr/lib /usr/local/lib /opt/firebird/lib ${PROJECT_SOURCE_DIR}/firebird_runtime/firebird )
  if( NOT FB_LIB )
    message( FATAL_ERROR "Unable to find firebird interface" )
  else( NOT FB_LIB )
    message( STATUS "Firebird interface: " ${FB_LIB} )
  endif( NOT FB_LIB )

  # look for the folder containing the firebird embedded files to ship with the program
  find_path( FB_EMBEDDED_PATH firebird.conf ${PROJECT_SOURCE_DIR}/firebird_runtime ${PROJECT_SOURCE_DIR}/../../firebird_embedded_2.0.4_runtime )
  message( STATUS "Embedded firebird files path: " ${FB_EMBEDDED_PATH} )

#  target_link_libraries( vvv -lfbembed )
  target_link_libraries( vvv ${FB_LIB} )
endif( UNIX )


# installation stuff

install( TARGETS vvv DESTINATION . )

if( APPLE )
  # copy the Firebird runtime
  install( DIRECTORY ${FB_EMBEDDED_PATH}/ DESTINATION vvv.app/Contents/MacOS USE_SOURCE_PERMISSIONS )
  install( FILES ${FB_EMBEDDED_PATH}/firebird/firebird.msg DESTINATION vvv.app/Contents/MacOS/firebird/bin/firebird )
  # fix filename references in the runtime
  set( FIXUP_COMMAND ${PROJECT_SOURCE_DIR}/MACOSX_fixup_bundle.sh " " ${CMAKE_INSTALL_PREFIX}/vvv.app )
  install( CODE "execute_process( COMMAND ${FIXUP_COMMAND} )" )
endif( APPLE )

if( UNIX AND NOT APPLE )
  # copy the Firebird runtime
  install( DIRECTORY ${FB_EMBEDDED_PATH}/ DESTINATION . USE_SOURCE_PERMISSIONS )
  # copy other files used only for the Linux version
  install( FILES ${PROJECT_SOURCE_DIR}/linux_specific/readme.txt 
                 ${PROJECT_SOURCE_DIR}/linux_specific/License.txt 
                 DESTINATION . )
  install( FILES ${PROJECT_SOURCE_DIR}/linux_specific/vvv-start.sh 
                 DESTINATION . PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE
                                           GROUP_READ WORLD_READ WORLD_EXECUTE )
endif( UNIX AND NOT APPLE )

if( UNIX )
  # set the installation path of the executable file and the resources (in OS X they are inside the bundle )
  if( APPLE )
    set( EXECUTABLE_INTALL_PATH vvv.app/Contents/MacOS )
    set( RESOURCES_INTALL_PATH vvv.app/Contents/Resources )
  else( APPLE )
    set( EXECUTABLE_INTALL_PATH . )
    set( RESOURCES_INTALL_PATH . )
  endif( APPLE )

  # copy localization files -- vvv files...
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-cs.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/cs RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-de.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/de RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-es.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/es RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-fr.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/fr RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-hr.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/hr RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-it.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/it RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-nl.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/nl RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-pl.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/pl RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-pt.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/pt RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-ro.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/ro RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-ru.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/ru RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-sr.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/sr RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-sr@latin.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/sr@latin RENAME vvv.mo )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/vvv-uk.mo 
           DESTINATION ${RESOURCES_INTALL_PATH}/languages/uk RENAME vvv.mo )
# ... wxWidgets files
  install( FILES ${PROJECT_SOURCE_DIR}/translations/cs/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/cs )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/de/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/de )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/es/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/es )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/fr/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/fr )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/it/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/it )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/nl/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/nl )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/pl/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/pl )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/pt/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/pt )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/ru/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/ru )
  install( FILES ${PROJECT_SOURCE_DIR}/translations/uk/wxstd.mo DESTINATION ${RESOURCES_INTALL_PATH}/languages/uk )

#  install( DIRECTORY ${PROJECT_SOURCE_DIR}/translations/ DESTINATION ${RESOURCES_INTALL_PATH}/languages 
#           FILES_MATCHING PATTERN "*.mo"
#           PATTERN ".svn" EXCLUDE )

  # copy other files to the installation path
  install( FILES ${PROJECT_SOURCE_DIR}/vvv-struct-update.fdb 
                 ${PROJECT_SOURCE_DIR}/VVV.fbk
                 ${PROJECT_SOURCE_DIR}/help/en/vvv.htb
                 DESTINATION ${EXECUTABLE_INTALL_PATH} )

endif( UNIX )


