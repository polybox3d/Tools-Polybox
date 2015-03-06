#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install Linux CNC\n
# \n
# This script will install some part of LinuxCNC for you \n
# To use LinuxCNC, a real-time kernel is needed \n
# For this reaason, your Linux kernel will be patched by Xenomai \n
# A reboot is needed at the end \n
# Then, after the reboot, you need to start the 2nd CNC script \n
# If you use the installer, just restart it, and watch. \n
#\n
##########################################\n"
resetC

sudo apt-get -y install python-gtk2 libglade2-dev python-glade2 python-gnome2 python-pip python-dev build-essential
print_check_error
sudo apt-get -y install libpth-dev tcl8.5-dev tk8.5-dev bwidget libxaw7-dev libncurses-dev python-support libgnomeprintui2.2-dev texlive-lang-cyrillic libudev-dev zlib1g-dev libtk-img libmodbus-dev
print_check_error
sudo apt-get -y install libboost-python-dev tk-dev tcl-dev 
print_check_error
sudo pip install ino
print_check_error

