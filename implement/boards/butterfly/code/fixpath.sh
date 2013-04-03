#!/bin/bash
#
# fixpath.sh
#
# Make the correct symbolic links to avr5.x and ctrm169p.o
# (has to be run as root)
set -e # bash should exit the script if any statement returns a
       # non-true return value
USER=$(whoami)
if [ $USER != root ]
then
    echo 'fixpath.sh must be run as root'
else
    updatedb # Update the database for locate
    AVR5XPATH=$(locate -b '\avr5.x')
    LDPATH=$(dirname $AVR5XPATH)
    ln -sf $LDPATH /usr/avr/lib/ldscripts
    echo 'Created symbolic link from '$LDPATH' to /usr/avr/lib/ldscripts' 
    # If the link already exists, a second symbolic link
    # will be created in the original ldscripts directory.  Get rid of
    # that one.
    rm -f $LDPATH/ldscripts
fi
