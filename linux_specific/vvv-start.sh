#!/bin/sh

# change the current directory to the one that contains this script
# this is needed to run the script from a launcher, a menu entry or similar
cd "$(dirname "$0")"
export LD_LIBRARY_PATH=./firebird
export FIREBIRD=.
./vvv

