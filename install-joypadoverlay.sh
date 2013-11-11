#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install JoypadOverlay Software\n
# \n
##########################################\n"
resetC


#===Start Joypad software===
cd ~/
git clone https://github.com/skapin/JoypadOverlay.git joypadoverlay
cd joypadoverlay/src/
/usr/lib/i386-linux-gnu/qt5/bin/qmake
make



cd $MY_DIR
echo "git pull ~/joypadoverlay/" >> git-update.sh

print_bye
resetC

