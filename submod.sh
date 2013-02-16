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

# The howto doctools
HOWTO_DOCTOOLS=./implement/howto/doctools

# --------------------- Done with configuration -------------------------
SCRIPTDIR=$(pwd -P)


# Check out a version of jpeda for the USB board
cd $SCRIPTDIR
if [ -d "$USB_JPEDA" ]; then
    # The directory already exists
    cd $USB_JPEDA;git pull
else
    git clone git@github.com:johnpeck/jpeda.git $USB_JPEDA  
fi


# Check out a version of jpeda for the butterfly board
cd $SCRIPTDIR
if [ -d "$BFLY_JPEDA" ]; then
    # The directory already exists
    cd $BFLY_JPEDA;git pull
else
    git clone git@github.com:johnpeck/jpeda.git $BFLY_JPEDA  
fi

# Check out a version of doctools for the howto
cd $SCRIPTDIR
if [ -d "$HOWTO_DOCTOOLS" ]; then
    # The directory already exists
    cd $HOWTO_DOCTOOLS;git pull
else
    git clone git@github.com:johnpeck/doctools.git $HOWTO_DOCTOOLS 
fi
