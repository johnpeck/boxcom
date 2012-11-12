#!/bin/bash
# Name: submod.sh
#
# Checks out the correct versions of submodules
#
# Usage: submod.sh
set -e # bash should exit the script if any statement returns a non-true 
       # return value
# The path to the USB board's jpeda module
USB_JPEDA=./implement/boards/usb/reva/schematics/jpeda
# The path to the Butterfly board's jpeda module
BFLY_JPEDA=./implement/boards/butterfly/reva/schematics/jpeda

if [ -d "$USB_JPEDA" ]; then
    # The directory already exists
    cd $USB_JPEDA;git pull
else
    git clone git@github.com:johnpeck/jpeda.git $USB_JPEDA  
fi

if [ -d "$BFLY_JPEDA" ]; then
    # The directory already exists
    cd $BFLY_JPEDA;git pull
else
    git clone git@github.com:johnpeck/jpeda.git $BFLY_JPEDA  
fi
