VVV (virtual volumes view)

This program is free software; you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation; either version 2 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful, but WITHOUT 
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
details.

You should have received a copy of the GNU General Public License along with 
this program; if not, write to the Free Software Foundation, Inc., 675 Mass 
Ave, Cambridge, MA 02139, USA.

-----------------------------------------------------------------------------

Welcome to VVV, VVV is an application that catalogs the content of removable
volumes like CD and DVD disks for off-line searching.
Folders and files can also be arranged in a single, virtual file system.
Each folder of this virtual file system can contain files from many disks
so you can arrange your data in a simple and logical way.

visit us at
http://vvvapp.sourceforge.net/


Installation:
-------------

VVV does not need to be installed. Everything it needs is contained in is folder.
Just expand the program in a suitable folder and execute "vvv-start.sh".
NOTE: do not start directly the vvv executable file because it would not work.

The help file contains some instructions.

How to start VVV from a menu entry:
-----------------------------------

It is possible to start VVV from a menu entry or from a launcher: just set the entry
to start the "vvv-start.sh" file, but you need to edit the script file to make it work.

You must add a new line at the top of the file, setting the current directory to the
directory that contains the script. This directory changes from computer to
computer so this line cannot be set in the distribution archive.
For example the script file could look like:


#!/bin/sh
cd ~/vvv
export LD_LIBRARY_PATH=./firebird
export FIREBIRD=.
./vvv


Fulvio Senore (fsenore@ica-net.it)
