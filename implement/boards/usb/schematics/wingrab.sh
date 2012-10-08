#!/bin/bash
# Name: wingrab.sh
#
# Grabs a window and creates an image file.
# Uses the "import" tool provided by Imagemagick
#
# Usage: wingrab.sh
# ...then click in the window you want to grab with the crosshairs.
set -e # bash should exit the script if any statement returns a non-true 
       #return value
echo "Use the crosshair to select the window to grab."
# Options for import:
# -frame -- Include the window frame with the window grab.
# -density -- Image density in pixels per inch (default)
# ...and import will handle the same image formats handled by Imagemagick
import -frame -density 300x300 grab.png
echo "Window image saved to grab.png."
