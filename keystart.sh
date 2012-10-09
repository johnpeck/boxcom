#!/bin/bash
# Name: keystart.sh
#
# Starts a keychain for the current shell
#
# Usage: keystart.sh
set -e # bash should exit the script if any statement returns a non-true 
       #return value
EXPECTED_ARGS=0
E_BADARGS=65
       
# Check to see that we got the right number of arguments
if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: keystart.sh"
  exit $E_BADARGS
fi

keychain ~/.ssh/id_rsa
source ~/.keychain/$HOSTNAME-sh