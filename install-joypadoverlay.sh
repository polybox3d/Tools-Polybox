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
git clone https://github.com/skapin/JoypadOverlay.git
cd JoypadOverlay
qmake
make



cd ~/

print_bye
resetC

