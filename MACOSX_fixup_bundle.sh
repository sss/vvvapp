#!/bin/bash

# this script will fix the components of the Firebird runtime to make it run from any location

# the script receives the path of the bundle to fix
BUNDLEPATH=$*

# the following line contains the name of the executable file that will be patched
# it is the only line that should be changed when copying this file to another project
EXECFILE=${BUNDLEPATH}/Contents/MacOS/vvv

LIBPATH=${BUNDLEPATH}/Contents/MacOS/firebird
LIBBINPATH=${BUNDLEPATH}/Contents/MacOS/firebird/bin
# path of library files relative to the main executable
NEWLIBPATH="@executable_path/firebird"
# path of library files relative to other library files
NEWLIBPATH_FOR_LIBS="@loader_path"
# path of library files relative to executables in the "firebird/bin" folder
NEWLIBPATH_FROM_BIN="@loader_path/.."
OLDLIBPATH="/Library/Frameworks/Firebird.framework/Versions/A/Libraries"
OLDLIBFBEMBEDFILENAME="/Library/Frameworks/Firebird.framework/Versions/A/Firebird"

# change the references in the files contained in the "firebird" folder
for TARGET in libfbembed.dylib libicudata.dylib libicui18n.dylib libicuuc.dylib ; do
  LIBFILE=${LIBPATH}/${TARGET}
  OLDTARGETID=${OLDLIBPATH}/${TARGET}
  NEWTARGETID=${NEWLIBPATH}/${TARGET}
  NEWTARGETID_FOR_LIBS=${NEWLIBPATH_FOR_LIBS}/${TARGET}
  install_name_tool -id ${NEWTARGETID_FOR_LIBS} ${LIBFILE}
  install_name_tool -change ${OLDTARGETID} ${NEWTARGETID} ${EXECFILE}
  for POSSIBLECALLERNAME in libfbembed.dylib libicudata.dylib libicui18n.dylib libicuuc.dylib ; do
    POSSIBLECALLERFILE=${LIBPATH}/${POSSIBLECALLERNAME}
    install_name_tool -change ${OLDTARGETID} ${NEWTARGETID_FOR_LIBS} ${POSSIBLECALLERFILE}
  done
done

# change the references in the files contained in the "firebird/bin" folder
for TARGET in gbak isql ; do
  FILE=${LIBBINPATH}/${TARGET}
  for POSSIBLECALLEDNAME in libfbembed.dylib libicudata.dylib libicui18n.dylib libicuuc.dylib ; do
    OLDTARGETID=${OLDLIBPATH}/${POSSIBLECALLEDNAME}
    NEWTARGETID=${NEWLIBPATH_FROM_BIN}/${POSSIBLECALLEDNAME}
    install_name_tool -change ${OLDTARGETID} ${NEWTARGETID} ${FILE}
  done
  # change the reference to libfbembed into the program, that contains a reference to a different name (the framework name)
  NEWTARGETID=${NEWLIBPATH_FROM_BIN}/libfbembed.dylib
  install_name_tool -change ${OLDLIBFBEMBEDFILENAME} ${NEWTARGETID} ${FILE}
done


# change the reference to libfbembed into the caller program, that contains a reference to a different name (the framework name)
NEWTARGETID=${NEWLIBPATH}/libfbembed.dylib
install_name_tool -change ${OLDLIBFBEMBEDFILENAME} ${NEWTARGETID} ${EXECFILE}
